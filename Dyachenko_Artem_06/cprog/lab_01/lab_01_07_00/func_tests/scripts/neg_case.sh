#!/bin/bash

app="../../app.exe"
file_input=$1
file_args=$2
file_report="report.txt"

args=""
if [[ -f "$file_args" ]]; then
        args=$(cat "$file_args")
fi

#echo got $file_input and $file_expected


if [[ -n "$USE_VALGRIND" ]]; then
        valgrind --leak-check=yes --leak-resolution=med --quiet --log-file="report.txt" "$app" "$args" < "$file_input"
        report=$(cat "$file_report")

        if [[ -n $report ]]; then
                echo 1
		exit 1
        else
                if [[ $? -eq 0 ]]; then
		        echo 1
			exit 1
		else
        		echo 0
			exit 0
		fi
        fi
else
        "$app" "$args" < "$file_input"
        if [[ $? -eq 0 ]]; then
        	echo 1
		exit 1
	else
        	echo 0
		exit 0
	fi

fi

#echo real $(cat $file_real)
#echo expected $(cat $file_expected)
