#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wextra -Wpedantic -Wvla -O0 -g --coverage ./*.c
gcc --coverage ./*.o -o app.exe -lm
