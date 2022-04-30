#!/bin/bash
gcc -c -Wall -Werror -Wpedantic -Wextra -O2 main.c
gcc -o app.exe main.o -lm
