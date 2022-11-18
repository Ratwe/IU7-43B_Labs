#!/bin/bash

rm -rf ../apps
mkdir -p ../apps
rm -rf ../data
mkdir -p ../data

./build_apps.sh
./update_data.sh 25
