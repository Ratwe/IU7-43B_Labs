#!/bin/bash
gcc -O3 -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c main.c
gcc main.o -o app.exe -lm
