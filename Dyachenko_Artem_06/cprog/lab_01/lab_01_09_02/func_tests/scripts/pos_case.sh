#!/bin/bash

app="../../app.exe"
file_input=$1
file_expected=$2
file_args=$3
file_real="real.txt"
file_report="report.txt"

args=""
if [[ -f $file_args ]]; then
	args=$(cat "$file_args")
fi

#echo got $file_input and $file_expected

if [[ -n "$USE_VALGRIND" ]]; then
        valgrind --leak-check=yes --leak-resolution=med --quiet --log-file="report.txt" "$app" "$args" < "$file_input" > "$file_real"
	report=$(cat "$file_report")
	
	if [[ -n $report ]]; then
		compared=1
	else
		compared=$(./comparator_num.sh "$file_expected" "$file_real")
	fi
else
	"$app" "$args" < "$file_input" > "$file_real"
	compared=$(./comparator_num.sh "$file_expected" "$file_real")
fi


#echo ------------------------------------
#echo real $(cat $file_real)
#echo expected $(cat $file_expected)
#echo ------------------------------------

echo "$compared"
exit "$compared"
