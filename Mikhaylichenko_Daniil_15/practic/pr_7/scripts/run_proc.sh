#!/bin/bash

rm -rf ../prepdata
mkdir -p ../prepdata
rm -rf ../graphics
mkdir -p ../graphics

python3 make_preproc.py
./make_postproc.sh
