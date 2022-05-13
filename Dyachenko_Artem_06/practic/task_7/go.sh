#!/bin/bash

./build_apps.sh
./update_data.sh 10
./make_preproc.sh
./make_postproc.sh
