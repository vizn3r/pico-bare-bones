#!/bin/bash
rm -rf build
mkdir build

cd build

cmake ..
make

echo "Uploading firmware.uf2..."
picotool load firmware.uf2
echo "Rebooting..."
picotool reboot
