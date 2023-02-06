#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -O0 ./*.c
gcc -o app.exe ./*.o -lm
