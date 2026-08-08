#!/usr/bin/env bash
# Clear out all solution output binaries.
#
# Usage: bash clear.sh
set -euo pipefail

PROJECT_ROOT="$(git rev-parse --show-toplevel)"  # amp/
BINARY_DIR="$PROJECT_ROOT/debug"  # amp/debug/
cd "$PROJECT_ROOT"

find "$BINARY_DIR" -type f -name "*.out" -delete
