#!/bin/bash

echo "Starting to update data..."

if [ ! -d "./data" ]; then
    mkdir "data"
    echo "Folder ./data created"
fi

times=$1

for file in ./apps/*; do
    path=$file
    file=$(echo "$file" | cut -c8-)

    if [[ "$file" =~ app[0-9]_O[0-9s]\.exe ]]; then
        opt=$(echo "$file" | cut -c7)
        num=$(echo "$file" | grep -o '[0-9]' | head -1)
        file_data="data""$num""_O""$opt"".txt"

        echo "updating ""'$file_data'""..."

        for i in $(seq 1 $times); do
            "$path" >> ./data/"$file_data"
        done
    fi
done

echo "Data updating complete!"
echo
