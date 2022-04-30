#!/bin/bash
./build_debug.sh
./func_tests/scripts/func_tests.sh
gcov main.c
