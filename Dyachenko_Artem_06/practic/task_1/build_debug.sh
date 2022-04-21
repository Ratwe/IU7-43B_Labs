#!/bin/bash
gcc -std=c99 -c -Wall -Werror -Wextra -Wpedantic -O0 -g --coverage main.c
gcc -o app.exe --coverage main.o -lm
