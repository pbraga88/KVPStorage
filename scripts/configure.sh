#!/usr/bin/env bash

echo "Checking system dependencies..."

MISSING=()

# Check for executables
for bin in cmake g++ pkg-config; do
    if ! command -v "$bin" &>/dev/null; then
        MISSING+=("$bin")
    fi
done

# Check for libsodium development files
if ! pkg-config --exists libsodium; then
    MISSING+=("libsodium-dev")
fi

if [ ${#MISSING[@]} -ne 0 ]; then
    echo "Missing dependencies:"
    for dep in "${MISSING[@]}"; do
        echo "  - $dep"
    done
    echo ""
    echo "On Debian/Ubuntu, you can install them with:"
    echo "    sudo apt update && sudo apt install ${MISSING[*]}"
    exit 1
fi

echo "All dependencies are installed."

# Resolve project root directory (one level up from this script)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Environment variables for keys and storage
export KVP_STORAGE_PATH="${ROOT_DIR}/kvpstorage.secure"
export KVP_KEYS_PATH="${ROOT_DIR}/keys/"

echo ""
echo "Environment variables set:"
echo "  KVP_STORAGE_PATH=$KVP_STORAGE_PATH"
echo "  KVP_KEYS_PATH=$KVP_KEYS_PATH"

echo ""
echo "To apply these variables in your shell session, run:"
echo "    source script/configure.sh"
