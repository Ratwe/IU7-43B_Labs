#!/bin/bash
./build_debug.sh
./build_release.sh

work_directory=`pwd`
script="/func_tests/scripts/func_test.sh"
testing="$work_directory$script"
eval $testing

./clean.sh
