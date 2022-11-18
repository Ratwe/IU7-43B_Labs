#!/bin/bash

test_in=$1
test_out=$2
test_args=$3

test_in="./func_tests/""${test_in#*/}"
test_out="./func_tests/""${test_out#*/}"

if [ -n "$test_args" ]; then
    programm_command="./app.exe $(cat "$test_args")"
else
    programm_command="./app.exe"
fi

cd ../../

exit_code=0

if [ "$USE_VALGRIND" -eq 1 ]; then
    valgrind -q --log-file=val.txt $programm_command < "$test_in" > out.txt
    if [ "$(du val.txt | cut -c1)" -ne 0 ]; then
        exit_code=$((exit_code+1))
    fi
else
    $programm_command < "$test_in" > out.txt
fi

./func_tests/scripts/comparator.sh "$test_out" out.txt
if [ $? -eq 2 ]; then
    exit_code=$((exit_code+2))
fi

exit $exit_code
