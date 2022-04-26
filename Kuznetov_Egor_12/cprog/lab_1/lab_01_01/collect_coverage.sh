#!/bin/bash
rm ./*.gc* 2> /dev/null
gcc -fprofile-arcs -ftest-coverage main.c -o app.exe
for i in func_tests/data/*_in.txt; do
    args=$(cat "$(echo "$i" | awk 'BEGIN { FS="_"; } { OFS="_"; print $1, $2, $3, "args.txt"; }')" 2> /dev/null)
    file_with_args="./app.exe $args"
    $file_with_args < "$i" > /dev/null
done
gcov -kj main.c
exit 0
