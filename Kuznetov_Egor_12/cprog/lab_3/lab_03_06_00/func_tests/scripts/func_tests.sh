#!/bin/bash
if [ ! -d "../data" ]; then
    echo "No func tests"
    exit 0
fi

if [ ! -f "../../app.exe" ]; then
    echo "Program not exist" >&2
    exit 1
fi

count_failed=0
for i in "../data"/*_in.txt; do
    num=$(echo "$i" | grep -oE "[0-9]*")
    if [[ $i =~ pos_.._in\.txt ]]; then
        args=("../data/$i" "../data/pos_""$num""_out.txt")

	if [ ! -f "../data/pos_""$num""_out.txt" ]; then
            echo "File pos_""$num""_out.txt not exist"
	    count_failed=$((count_failed + 1))
            continue
        fi

	if [ -f "../data/pos_""$num""_args.txt" ]; then
            args+=("../data/pos_""$num""_args.txt")
        fi
        ./pos_case.sh "${args[@]}"
        test_result="$?"
        if [ "$test_result" -ne 0 ]; then
            count_failed=$((count_failed + 1))
        fi
        
        if [ "$test_result" -ge 4 ]; then
            continue
        fi

        if [ "$((test_result % 2))" -eq 0 ]; then
            usage_result="PASSED"
        else
            usage_result="FAILED"
        fi

        if [ "$(((test_result >> 1) % 2))" -eq 0 ]; then
            memory_result="PASSED"
        else
            memory_result="FAILED"
        fi
        
        if [ -z "$USE_VALGRIND" ]; then
            echo "Pos test $num $usage_result"
        else
            echo "Pos test $num $usage_result, memory $memory_result"
        fi
    elif [[ $i =~ neg_.._in\.txt ]]; then
        args=("../data/$i") 

        if [ ! -f "../data/neg_""$num""_out.txt" ]; then
            echo "File neg_""$num""_out.txt not exist"
	    count_failed=$((count_failed + 1))
            continue
        fi

        if [ -f "../data/neg_""$num""_args.txt" ]; then
            args+=("../data/neg_""$num""_args.txt")
        fi

        ./neg_case.sh "${args[@]}"
        test_result="$?"
        if [ "$test_result" -ne 0 ]; then
            count_failed=$((count_failed + 1))
        fi

        if [ "$test_result" -ge 4 ]; then
            continue
        fi

        if [ "$((test_result % 2))" -eq 0 ]; then
            usage_result="PASSED"
        else
            usage_result="FAILED"
        fi

        if [ "$(((test_result / 2) % 2))" -eq 0 ]; then
            memory_result="PASSED"
        else
            memory_result="FAILED"
        fi

        if [ -z "$USE_VALGRIND" ]; then
            echo "Neg test $num $usage_result"
        else
            echo "Neg test $num $usage_result, memory $memory_result"
        fi
    fi
done

if [ $count_failed -gt 0 ]; then
    echo "Failed $count_failed tests"
    exit $count_failed
else
    echo "All tests passed"
    exit 0
fi
