#!/bin/bash

app="../../app.exe"
file_input=$1
file_expected=$2
file_args=$3
file_real="real.txt"
file_report="report.txt"
#USE_VALGRIND="1"

args=""
if [[ -f $file_args ]]; then
	args=$(cat "$file_args")
fi

if [[ -n "$USE_VALGRIND" ]]; then
        valgrind --leak-check=yes --leak-resolution=med --quiet --log-file="report.txt" "$app" "$args" < "$file_input" > "$file_real"
	report=$(cat "$file_report")

	./comparator_num.sh "$file_expected" "$file_real"
	compared=$?

	./comparator_string.sh "$file_expected" "$file_real"
	if [ "$compared" -gt "$?" ]; then
		compared=$?
	fi

	if [ "$compared" -eq 0 ]; then
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
	"$app" "$args" < "$file_input" > "$file_real"

	./comparator_num.sh "$file_expected" "$file_real"
	compared=$?

	./comparator_string.sh "$file_expected" "$file_real"
	if [ "$compared" -gt "$?" ]; then
		compared=$?
	fi
fi

exit "$compared"

# exit 0 if passed+
# exit 1 if passed-

# exit 3 if passed+, memory-
# exit 4 if passed+, memory+
# exit 5 if passed-, memory-
# exit 6 if passed-, memory+

# echo "[DB] compared =" "$compared"
