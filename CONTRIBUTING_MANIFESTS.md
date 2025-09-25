# Contributing Manifests (FeatureSets, Packages, Tutorials)

- Validate JSON files against schemas in `schemas/`.
- Prefer referencing curated libraries from `registry/libraries.example.json` via `id+version`.
- Keep manifests deterministic: pin tags/commits; include checksums when using `repo+commit`.
- Use `$schema` field in your JSON for editor validation.

## Hosting packs on GitHub

- Structure your repository like this so consumers can copy a folder directly:
  - `featuresets/<your_featureset_name>/FeatureSet.json`
  - `packages/<your_package_name>/Package.json`
  - `tutorials/<your_tutorial_name>/Tutorial.json`
- Create an index file (see `registry/packs.example.json`) listing entries with:
  - `repo` (owner/repo), `ref` (tag/branch/commit), `path` (folder in repo), `kind`, and optional `dest`.
- Consumers can fetch with:
  - `python3 scripts/fetch_packs.py --index registry/packs.example.json --dest-root . [--force]`
- The fetch script writes `registry/packs.lock.json` with checksums for reproducibility.


