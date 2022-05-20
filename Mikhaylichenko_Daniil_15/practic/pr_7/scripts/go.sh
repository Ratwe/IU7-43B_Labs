#!/bin/bash

rm -rf ../apps
mkdir -p ../apps
rm -rf ../data
mkdir -p ../data
rm -rf ../prepdata
mkdir -p ../prepdata
rm -rf ../graphs
mkdir -p ../graphs

echo "START"
./build_apps.sh
./update_data.sh 20
python3 make_preproc.py
./make_postproc.sh
echo "END"
