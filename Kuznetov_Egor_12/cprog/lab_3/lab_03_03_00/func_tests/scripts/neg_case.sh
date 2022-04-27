#!/bin/bash
file_with_args="../../app.exe $(cat "$2" 2> /dev/null)"
if [ -z "$USE_VALGRIND" ]; then
    $file_with_args < "$1" > "out.txt"
else
    file_with_args="valgrind -q --leak-check=full $file_with_args"
    $file_with_args < "$1" > "out.txt" 2> "valgrind_log.txt" 
fi

ret_code=$?
memory_adding=0
if [ -n "$USE_VALGRIND" ]; then
    if [ ! -s "valgrind_log.txt" ]; then
        memory_adding=2
    fi
fi

if [ $ret_code -ne 0 ]; then
    exit $((0 + memory_adding))
else
    exit $((1 + memory_adding))
fi
