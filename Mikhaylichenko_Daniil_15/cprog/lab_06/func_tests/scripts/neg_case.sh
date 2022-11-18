#!/bin/bash

test_in=$1
test_args=$2

test_in="./func_tests/""${test_in#*/}"

if [ -n "$test_args" ]; then
    programm_command="./app.exe $(cat "$test_args")"
else
    programm_command="./app.exe"
fi

cd ../../

exit_code=0

if [ "$USE_VALGRIND" -eq 1 ]; then
    valgrind -q --log-file=val.txt $programm_command < "$test_in" > out.txt
    programm_code=$?
    if [ "$programm_code" -eq 0 ]; then
        exit_code=$((exit_code+2))
    fi
    if [ "$(du val.txt | cut -c1)" -ne 0 ]; then
        exit_code=$((exit_code+1))
    fi
else
    $programm_command < "$test_in"
    programm_code=$?
    if [ "$programm_code" -ne 0 ]; then
        exit_code=$((exit_code+2))
    fi
fi

exit $exit_code
