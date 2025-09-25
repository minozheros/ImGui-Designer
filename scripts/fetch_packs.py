#!/usr/bin/env python3
"""
Fetch remote packs (featuresets/packages/tutorials) hosted on GitHub and install them locally.

Usage:
    python3 scripts/fetch_packs.py --index registry/packs.example.json [--dest-root .] [--force] [--dry-run] [--only id1,id2]

Notes:
  - No external dependencies required (uses urllib + zipfile)
  - Supports owner/repo or full https GitHub URLs
  - Writes registry/packs.lock.json with resolved metadata and sha256
"""
from __future__ import annotations

import argparse
import hashlib
import io
import json
import os
import re
import shutil
import sys
import tempfile
import time
import zipfile
from dataclasses import dataclass
from typing import Optional, Dict, Any

try:
    from urllib.request import urlopen
except Exception as e:  # pragma: no cover
    print(f"Error importing urllib: {e}", file=sys.stderr)
    sys.exit(1)


GITHUB_ARCHIVE_URL = "https://github.com/{owner}/{repo}/archive/{ref}.zip"


@dataclass
class PackEntry:
    id: str
    kind: str  # featureset|package|tutorial
    repo: str
    ref: str
    path: str
    dest: Optional[str]
    trust: str = "community"
    license: Optional[str] = None
    description: Optional[str] = None
    enabled: bool = True
    sha256: Optional[str] = None

    @staticmethod
    def from_dict(d: Dict[str, Any]) -> "PackEntry":
        return PackEntry(
            id=d["id"],
            kind=d["kind"],
            repo=d["repo"],
            ref=d["ref"],
            path=d["path"],
            dest=d.get("dest"),
            trust=d.get("trust", "community"),
            license=d.get("license"),
            description=d.get("description"),
            enabled=d.get("enabled", True),
            sha256=d.get("sha256"),
        )


def parse_repo(repo: str) -> tuple[str, str]:
    if repo.startswith("http://") or repo.startswith("https://"):
        m = re.search(r"github\.com/([^/]+)/([^/]+)(?:\.git)?", repo)
        if not m:
            raise ValueError(f"Unsupported GitHub URL: {repo}")
        return m.group(1), m.group(2)
    # owner/repo
    parts = repo.split("/")
    if len(parts) != 2:
        raise ValueError(f"Invalid repo format (expected owner/repo): {repo}")
    return parts[0], parts[1]


def download_archive(owner: str, repo: str, ref: str) -> bytes:
    url = GITHUB_ARCHIVE_URL.format(owner=owner, repo=repo, ref=ref)
    with urlopen(url) as resp:
        return resp.read()


def ensure_dir(p: str) -> None:
    os.makedirs(p, exist_ok=True)


def compute_sha256(data: bytes) -> str:
    h = hashlib.sha256()
    h.update(data)
    return h.hexdigest()


def copy_tree(src: str, dst: str, force: bool) -> None:
    if os.path.exists(dst) and force:
        shutil.rmtree(dst)
    if not os.path.exists(dst):
        shutil.copytree(src, dst)
    else:
        # merge copy (shallow overwrite)
        for root, dirs, files in os.walk(src):
            rel = os.path.relpath(root, src)
            target_root = os.path.join(dst, rel) if rel != "." else dst
            os.makedirs(target_root, exist_ok=True)
            for d in dirs:
                os.makedirs(os.path.join(target_root, d), exist_ok=True)
            for f in files:
                shutil.copy2(os.path.join(root, f), os.path.join(target_root, f))


def install_pack(entry: PackEntry, dest_root: str, archive_bytes: bytes, force: bool, dry_run: bool) -> Dict[str, Any]:
    sha256 = compute_sha256(archive_bytes)
    if entry.sha256 and entry.sha256 != sha256:
        raise ValueError(f"Checksum mismatch for {entry.id}: expected {entry.sha256} got {sha256}")

    with zipfile.ZipFile(io.BytesIO(archive_bytes)) as zf:
        # archive root usually 'repo-ref/'
        root_names = [n.split("/")[0] for n in zf.namelist() if "/" in n]
        root = root_names[0] if root_names else ""
        extract_dir = tempfile.mkdtemp(prefix="packs_")
        try:
            zf.extractall(extract_dir)
            pack_src = os.path.join(extract_dir, root, entry.path)
            if not os.path.isdir(pack_src):
                raise FileNotFoundError(f"Path not found in archive: {entry.path}")
            kind_dir = {
                "featureset": "featuresets",
                "package": "packages",
                "tutorial": "tutorials",
            }[entry.kind]
            dest_name = entry.dest or os.path.basename(entry.path.rstrip("/"))
            dest_dir = os.path.join(dest_root, kind_dir, dest_name)
            if dry_run:
                print(f"[dry-run] Would install {entry.id} -> {dest_dir}")
            else:
                ensure_dir(os.path.join(dest_root, kind_dir))
                copy_tree(pack_src, dest_dir, force=force)
            return {
                "id": entry.id,
                "kind": entry.kind,
                "repo": entry.repo,
                "ref": entry.ref,
                "dest": dest_name,
                "sha256": sha256,
                "installedAt": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
            }
        finally:
            shutil.rmtree(extract_dir, ignore_errors=True)


def main(argv: Optional[list[str]] = None) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--index", default="registry/packs.example.json")
    ap.add_argument("--dest-root", default=".")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--only", default="", help="Comma-separated list of pack ids to install from index")
    args = ap.parse_args(argv)

    with open(args.index, "r", encoding="utf-8") as f:
        index = json.load(f)

    only_ids = set([s.strip() for s in args.only.split(",") if s.strip()])
    entries = [PackEntry.from_dict(e) for e in index.get("entries", [])]
    if only_ids:
        entries = [e for e in entries if e.id in only_ids]
    results = []
    for e in entries:
        if not e.enabled:
            print(f"[skip] {e.id} (disabled)")
            continue
        try:
            owner, repo = parse_repo(e.repo)
            print(f"[fetch] {e.id} from {owner}/{repo}@{e.ref} path={e.path}")
            data = b""
            if not args.dry_run:
                data = download_archive(owner, repo, e.ref)
            res = install_pack(e, args.dest_root, data, force=args.force, dry_run=args.dry_run)
            results.append(res)
        except Exception as ex:
            print(f"[error] {e.id}: {ex}", file=sys.stderr)

    lock = {
        "version": index.get("version", "1"),
        "generatedAt": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "entries": results,
    }
    lock_path = os.path.join(os.path.dirname(args.index), "packs.lock.json")
    if args.dry_run:
        print(f"[dry-run] Would write lockfile to {lock_path}")
    else:
        with open(lock_path, "w", encoding="utf-8") as f:
            json.dump(lock, f, indent=2)
        print(f"[ok] Wrote lockfile {lock_path}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
