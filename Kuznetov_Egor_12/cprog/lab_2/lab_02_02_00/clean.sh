#!/bin/bash
for i in *.out *.o *.exe func_tests/scripts/*.txt *.gc*; do
    rm "$i" 2> /dev/null
done
exit 0
