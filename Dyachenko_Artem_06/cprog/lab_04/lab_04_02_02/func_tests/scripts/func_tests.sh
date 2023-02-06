#!/bin/bash

count=0

for file in ./../data/*_in.txt; do
	if [[ "$file" =~ pos_[0-9][0-9]_in\.txt ]]; then

		num=$(echo "$file" | grep -o "[0-9]*")
		file_output=$(echo | find ./../data/ -name "pos_$num\_out\.txt")
		file_args=$(echo | find ./../data/ -name "pos_$num\_args\.txt")

		# echo "[DB] file:" "$file"
		# echo "[DB] file_output:" "$file_output"
		# echo "[DB] file_args:" "$file_args"

		./pos_case.sh "$file" "$file_output" "$file_args"
		checker=$?

		if [[ $checker -eq 0 ]]; then
			echo "$file passed"
		elif [[ $checker -eq 1 ]]; then
			echo "$file failed"
			count=$((count+1))
		elif [[ $checker -eq 3 ]]; then
			echo "$file passed, memory error"
			count=$((count+1))
		elif [[ $checker -eq 4 ]]; then
			echo "$file passed, memory OK"
		elif [[ $checker -eq 5 ]]; then
			echo "$file failed, memory error"
			count=$((count+1))
		elif [[ $checker -eq 6 ]]; then
			echo "$file failed, memory OK"
			count=$((count+1))
		fi

	elif [[ "$file" =~ neg_[0-9][0-9]_in\.txt ]]; then

		num=$(echo "$file" | grep -o "[0-9]*")
		file_output=$(echo | find ./../data/ -name "neg_$num\_out\.txt")
		file_args=$(echo | find ./../data/ -name "neg_$num\_args\.txt")

		# echo "[DB] file:" "$file"
		# echo "[DB] file_output:" "$file_output"
		# echo "[DB] file_args:" "$file_args"

		./neg_case.sh "$file" "$file_args"
		checker=$?

		if [[ $checker -eq 0 ]]; then
			echo "$file passed"
		elif [[ $checker -eq 1 ]]; then
			echo "$file failed"
			count=$((count+1))
		elif [[ $checker -eq 3 ]]; then
			echo "$file passed, memory error"
			count=$((count+1))
		elif [[ $checker -eq 4 ]]; then
			echo "$file passed, memory OK"
		elif [[ $checker -eq 5 ]]; then
			echo "$file failed, memory error"
			count=$((count+1))
		elif [[ $checker -eq 6 ]]; then
			echo "$file failed, memory OK"
			count=$((count+1))
		fi

	fi
done

echo Failed tests: $count
exit $count
