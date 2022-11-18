#!/bin/bash

./build_debug.sh
cd func_tests/scripts/ || return
./func_test.sh
cd ../../
./clean.sh
