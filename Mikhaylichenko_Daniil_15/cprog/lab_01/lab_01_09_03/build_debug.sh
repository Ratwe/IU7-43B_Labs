#!/bin/bash

first="cpp -o main.i main.c"
second="c99 -S -fverbose-asm -masm=intel main.i"
third="as main.s -o main.o"
for_valgrind="gcc -std=c99 -Wall -g -O0 main.c -lm"

eval "$first"
eval "$second"
eval "$third"
eval "$for_valgrind"
