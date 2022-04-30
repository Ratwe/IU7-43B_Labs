#!/bin/bash

gcc -std=c99 -c -Wall -Werror -Wextra -Wpedantic -O0 -g --coverage main.c
gcc --coverage main.o -o app.exe -lm
