#!/bin/bash
gcc -Wall -Werror -Wextra -Wpedantic --coverage -o app.exe main.c -lm
./func_tests/scripts/func_tests.sh
gcov main.c
