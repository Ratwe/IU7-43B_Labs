#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -O3 ./*.c
gcc -o app.exe ./*.o -lm
