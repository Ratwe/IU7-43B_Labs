#!/bin/bash

gcc -c -std=c99 -I ./inc -Wall -Werror -Wpedantic -Wextra -Wvla -O0 ./src/*.c
gcc -o app.exe ./*.o -lm
