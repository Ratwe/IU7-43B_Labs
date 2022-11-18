#!/bin/bash

gcc -c -std=c99 -I ./inc -DDEBUG -Wall -Werror -Wextra -Wpedantic -Wvla -O0 -g --coverage ./src/*.c
gcc --coverage *.o -o app.exe -lm
