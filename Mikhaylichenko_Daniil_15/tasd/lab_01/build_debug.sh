#!/bin/bash

gcc -g3 -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wfloat-equal -Wvla -DDEBUG -o app.exe *.c -lm
