#!/bin/bash

count=0

for file in ../data/*_in.txt; do
	if [[ "$file" =~ pos_[0-9][0-9]_in\.txt ]]; then
			
		num=$(echo "$file" | grep -o "[0-9]*")
		file_output=$(echo | find ../data/ -name "pos_$num\_out\.txt")
	     	checker=$(./pos_case.sh "$file" "$file_output")
		
		if [[ $checker -eq 0 ]]; then
			echo "$file passed"
		elif [[ $checker -eq 1 ]]; then
			echo "$file failed"
			count=$((count+1))
		fi	
		
	elif [[ "$file" =~ neg_[0-9][0-9]_in\.txt ]]; then

		num=$(echo "$file" | grep -o "[0-9]*")
		file_output=$(echo | find ../data/ -name "neg_$num\_out\.txt")
		checker=$(./neg_case.sh "$file")

  		if [[ $checker -eq 0 ]]; then
                        echo "$file passed"
                elif [[ $checker -eq 1 ]]; then
                        echo "$file failed"
			count=$((count+1))
                fi

	fi
done

echo failed tests: $count
exit $count
