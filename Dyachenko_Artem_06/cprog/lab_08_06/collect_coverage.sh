#!/bin/bash

./build_debug.sh
cd func_tests/scripts/ || exit
./func_tests.sh
echo
gcov ./../../main.c
