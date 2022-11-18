#!/bin/bash

args=$@

gcc --coverage *.c -o app.exe
cd func_tests/scripts/
./func_test.sh
cd ../../
lcov -t "app" -o app.info -c -d .
genhtml -o report app.info

if [ "$args" == "-html" ]; then
    open "report/index.html"
fi
