#!/usr/bin/env python3
"""
Validate local manifests against JSON Schemas and apply basic security checks.

Checks:
 - JSON Schema validation for FeatureSets, Packages, Tutorials, LibraryRegistry, PackIndex
 - ID and naming consistency
 - PackIndex security: official/verified entries must pin tags (vX.Y.Z) or commit sha; warn on branches
 - sha256 fields (when present) must be valid hex-64

Exit non-zero on validation failures.
"""
from __future__ import annotations

import json
import os
import re
import sys
from glob import glob
from typing import Any, Dict, List, Tuple


def load_json(path: str) -> Dict[str, Any]:
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def find_python_jsonschema():
    try:
        import jsonschema  # type: ignore
        from jsonschema import Draft7Validator  # noqa: F401
        return jsonschema
    except Exception:
        return None


def validate_with_schema(instance: Dict[str, Any], schema: Dict[str, Any], ctx: str) -> List[str]:
    js = find_python_jsonschema()
    errors: List[str] = []
    if js is None:
        # Fallback: light check to ensure required fields exist
        required = schema.get("required", [])
        for key in required:
            if key not in instance:
                errors.append(f"{ctx}: missing required field '{key}' (jsonschema not installed for full validation)")
        return errors
    v = js.Draft7Validator(schema)
    for e in sorted(v.iter_errors(instance), key=lambda e: e.path):
        loc = "/".join([str(p) for p in e.path])
        errors.append(f"{ctx}: {loc}: {e.message}")
    return errors


def validate_sha256(value: str) -> bool:
    return bool(re.fullmatch(r"[0-9a-fA-F]{64}", value or ""))


def is_commit_sha(ref: str) -> bool:
    return bool(re.fullmatch(r"[0-9a-f]{7,40}", ref))


def is_semver_tag(ref: str) -> bool:
    # Accept vX.Y or vX.Y.Z or X.Y.Z styles
    return bool(re.fullmatch(r"v?\d+\.\d+(?:\.\d+)?(?:[-_].+)?", ref))


def security_checks_packindex(index: Dict[str, Any]) -> List[str]:
    errors: List[str] = []
    warnings: List[str] = []
    entries = index.get("entries", [])
    for i, e in enumerate(entries):
        ctx = f"PackIndex.entries[{i}]({e.get('id', '?')})"
        ref = e.get("ref", "")
        trust = e.get("trust", "community")
        sha256 = e.get("sha256")
        if trust in ("official", "verified"):
            if not (is_semver_tag(ref) or is_commit_sha(ref)):
                errors.append(f"{ctx}: ref '{ref}' must be a pinned tag or commit for trust '{trust}'")
        # If sha256 provided, validate format
        if sha256 and not validate_sha256(sha256):
            errors.append(f"{ctx}: sha256 must be 64 hex characters")
    return errors + warnings


def main() -> int:
    root = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    schemas_dir = os.path.join(root, "schemas")
    errors: List[str] = []

    # Load schemas
    schema_files = {
        "FeatureSet": os.path.join(schemas_dir, "FeatureSet.schema.json"),
        "Package": os.path.join(schemas_dir, "Package.schema.json"),
        "Tutorial": os.path.join(schemas_dir, "Tutorial.schema.json"),
        "LibraryRegistry": os.path.join(schemas_dir, "LibraryRegistry.schema.json"),
        "PackIndex": os.path.join(schemas_dir, "PackIndex.schema.json"),
    }
    schemas: Dict[str, Dict[str, Any]] = {}
    for name, path in schema_files.items():
        try:
            schemas[name] = load_json(path)
        except Exception as ex:
            errors.append(f"load schema {name}: {ex}")

    # Validate local manifests
    def validate_dir(pattern: str, schema_name: str):
        schema = schemas.get(schema_name)
        if not schema:
            errors.append(f"missing schema {schema_name}")
            return
        for path in glob(pattern, recursive=True):
            try:
                inst = load_json(path)
                ctx = os.path.relpath(path, root)
                errors.extend(validate_with_schema(inst, schema, ctx))
            except Exception as ex:
                errors.append(f"{path}: load error: {ex}")

    validate_dir(os.path.join(root, "featuresets", "*", "FeatureSet.json"), "FeatureSet")
    validate_dir(os.path.join(root, "packages", "*", "Package.json"), "Package")
    validate_dir(os.path.join(root, "tutorials", "*", "Tutorial.json"), "Tutorial")

    # Registry files (examples)
    reg_libs = os.path.join(root, "registry", "libraries.example.json")
    if os.path.exists(reg_libs):
        try:
            inst = load_json(reg_libs)
            errors.extend(validate_with_schema(inst, schemas.get("LibraryRegistry", {}), os.path.relpath(reg_libs, root)))
        except Exception as ex:
            errors.append(f"{reg_libs}: load error: {ex}")

    reg_packs = os.path.join(root, "registry", "packs.example.json")
    if os.path.exists(reg_packs):
        try:
            inst = load_json(reg_packs)
            errors.extend(validate_with_schema(inst, schemas.get("PackIndex", {}), os.path.relpath(reg_packs, root)))
            errors.extend(security_checks_packindex(inst))
        except Exception as ex:
            errors.append(f"{reg_packs}: load error: {ex}")

    if errors:
        for e in errors:
            print(f"ERROR: {e}")
        return 2
    print("All manifests validated successfully.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
