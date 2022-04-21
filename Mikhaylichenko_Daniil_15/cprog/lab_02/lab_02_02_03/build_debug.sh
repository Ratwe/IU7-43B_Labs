#!/bin/bash

gcc -g3 -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wfloat-equal -Wvla -o app.exe main.c -lm
