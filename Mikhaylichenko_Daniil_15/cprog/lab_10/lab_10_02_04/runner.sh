#!/bin/bash

make release
cd func_tests/scripts/ || return
./func_test.sh
cd ../../
make unit
make clean
