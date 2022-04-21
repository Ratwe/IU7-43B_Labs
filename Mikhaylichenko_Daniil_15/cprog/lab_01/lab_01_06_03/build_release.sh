#!/bin/bash

command="gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o app.exe main.o -lm"

eval "$command"
