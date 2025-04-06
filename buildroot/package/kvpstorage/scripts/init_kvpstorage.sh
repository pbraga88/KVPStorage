#!/bin/sh

# Set environment variables
export KVP_STORAGE_PATH="/var/lib/kvpstorage/kvpstorage.secure"
export KVP_KEYS_PATH="/etc/kvpstorage/keys"

# Start the application
exec /usr/bin/kvpstorage