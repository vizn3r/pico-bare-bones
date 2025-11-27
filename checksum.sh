#!/bin/bash
# Calculate checksum from final binary
dd if=build/firmware.bin bs=1 count=252 2>/dev/null | gzip -c | tail -c8 | head -c4 | od -An -tx4
