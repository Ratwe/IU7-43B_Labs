#!/bin/bash

export USE_VALGRIND=1
failed_tests=0

print_test()
{
    case $2 in
    0 ) echo -e "       \033[33m$1_TEST_$number: \033[32mpass\033[0m, \033[33mMEMORY: \033[32mpass\033[0m";;
    1 ) echo -e "       \033[33m$1_TEST_$number: \033[32mpass\033[0m, \033[33mMEMORY: \033[31mfailed\033[0m";;
    2 ) echo -e "       \033[33m$1_TEST_$number: \033[31mfailed\033[0m, \033[33mMEMORY: \033[32mpass\033[0m";;
    3 ) echo -e "       \033[33m$1_TEST_$number: \033[31mfailed\033[0m, \033[33mMEMORY: \033[31mfailed\033[0m";;
    esac
}

pos_in=()
neg_in=()

for file in $(find ../data -type f -name "pos_*_in.txt" | sort); do
    #file="./func_tests/""${file#*/}"
    pos_in+=("$file")
done

for file in $(find ../data -type f -name "neg_*_in.txt" | sort); do
    #file="./func_tests/""${file#*/}"
    neg_in+=("$file")
done
 

echo "START TESTING"

echo "  Running positive tests..."
if [ ${#pos_in[@]} -eq 0 ]; then
    echo "      No positive tests"
else
    for test_in in "${pos_in[@]}"; do
        number=$(echo "$test_in" | cut -c13-14)
        test_out=$(find ../data -type f -name "pos_""$number""_out.txt")
        if [ -z "$test_out" ]; then
            continue
        fi
        test_args=$(find ../data -type f -name "pos_""$number""_args.txt")
        ./pos_case.sh "$test_in" "$test_out" "$test_args"
        exit_code=$?
        print_test "POS" $exit_code
        if [ $exit_code -ne 0 ]; then
            failed_tests=$((failed_tests+1))
        fi
    done
fi

echo "  Running negetive tests..."
if [ ${#neg_in[@]} -eq 0 ]; then
    echo "      No negetive tests"
else
    for test_in in "${neg_in[@]}"; do
        number=$(echo "$test_in" | cut -c13-14)
        test_args=$(find ../data -type f -name "neg_""$number""_args.txt")
        ./neg_case.sh "$test_in" "$test_args"
        exit_code=$?
        print_test "NEG" $exit_code
        if [ $exit_code -ne 0 ]; then
            failed_tests=$((failed_tests+1))
        fi
    done
fi

echo "END TESTING"

exit $failed_tests
