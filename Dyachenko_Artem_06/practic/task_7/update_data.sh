#!/bin/bash

echo "Starting to update data..."

for file in ./*; do

    if [[ "$file" =~ app[0-9]_O[0-9s]\.exe ]]; then

        opt=$(echo "$file" | cut -c9)
        num=$(echo "$file" | grep -o '[0-9]' | head -1)
        file_data="data""$num""_O""$opt"".txt"

        echo "updating ""'$file_data'""..."

        ./"$file" >> "$file_data"
    fi
done

echo "Data updating complete!"
echo
