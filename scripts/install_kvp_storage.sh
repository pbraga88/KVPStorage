#!/bin/bash

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <path-to-buildroot>"
    exit 1
fi

BUILDROOT_PATH="$1"
PKG_DIR="$BUILDROOT_PATH/package"
CONFIGS_DIR="$BUILDROOT_PATH/configs"
TARGET_CONFIG_IN="$PKG_DIR/Config.in"
KVP_SOURCE_DIR="./buildroot/package/kvpstorage"
KVP_DEFCONFIG="./buildroot/kvp_defconfig"

# Check paths
if [ ! -d "$BUILDROOT_PATH" ]; then
    echo "Error: Path '$BUILDROOT_PATH' does not exist."
    exit 1
fi

echo "Copying kvpstorage package..."
cp -r "$KVP_SOURCE_DIR" "$PKG_DIR/"

echo "Copying kvp_defconfig..."
cp "$KVP_DEFCONFIG" "$CONFIGS_DIR/"

echo "Updating package/Config.in..."
# Only insert if it doesn't already exist
if ! grep -q 'package/kvpstorage/Config.in' "$TARGET_CONFIG_IN"; then
    awk '
        BEGIN { inserted = 0 }
        /menu "Miscellaneous"/ {
            print
            print "        source \"package/kvpstorage/Config.in\""
            inserted = 1
            next
        }
        { print }
        END {
            if (!inserted) {
                print "WARNING: Could not insert source line under menu \"Miscellaneous\""
            }
        }
    ' "$TARGET_CONFIG_IN" > "$TARGET_CONFIG_IN.tmp" && mv "$TARGET_CONFIG_IN.tmp" "$TARGET_CONFIG_IN"
else
    echo "Entry already exists in Config.in. Skipping insertion."
fi

echo "Done. You can now run: make kvp_defconfig"
