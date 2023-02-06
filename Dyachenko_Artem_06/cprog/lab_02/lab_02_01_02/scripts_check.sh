#!/bin/bash

for file in ./*.sh; do
    shellcheck "$file"
done

for file in ./func_tests/scripts/*.sh; do
    shellcheck "$file"
done
