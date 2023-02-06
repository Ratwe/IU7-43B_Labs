#!/bin/bash

app="./../../app.exe"
file_input=$1
file_args=$2
file_report="report.txt"
file_output=".output.txt"

args=""
if [[ -f "$file_args" ]]; then
    args=$(cat "$file_args")
fi

if [[ -n "$USE_VALGRIND" ]]; then
    if [[ "$#" -ne 2 ]]; then
		exit 5
	fi

    valgrind --leak-check=yes --leak-resolution=med --quiet --log-file="report.txt" "$app" "$args" < "$file_input"
    report=$(cat "$file_report")

    "$app" "$args" < "$file_input" > "$file_output"
    compared=$?

	if [ "$compared" -ne 0 ]; then
		if [[ -n $report ]]; then
			compared=3
		else
			compared=4
		fi
	else
		if [[ -n $report ]]; then
			compared=5
		else
			compared=6
		fi
	fi

else
    if [[ "$#" -ne 2 ]]; then
		exit 1
	fi

    "$app" "$args" < "$file_input" > "$file_output"
    if [[ "$?" -lt 1 ]]; then
	    compared=1
	else
        compared=0
	fi
fi

exit "$compared"

# exit 0 if passed- (BAD)
# exit 1 if passed+ (OK)

# exit 3 if passed-, memory- (BAD)
# exit 4 if passed-, memory+ (OK)
# exit 5 if passed+, memory- (BAD)
# exit 6 if passed+, memory+ (BAD)

#echo real $(cat $file_real)
#echo expected $(cat $file_expected)
