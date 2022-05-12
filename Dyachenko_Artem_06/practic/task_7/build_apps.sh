#!/bin/bash

echo "Starting building..."

opts="Os O0 O1 O2 O3"

if [ ! -d "./apps" ]; then
    mkdir "apps"
    echo "Folder ./apps created"
fi

for file in ./mains/*; do
    path=$file
    file=$(echo "$file" | cut -c9-)

    if [[ "$file" =~ main[0-9]\.c ]]; then
        num=$(echo "$file" | grep -o "[0-9]")
        app=$(echo "app""$num")

        for opt in $opts; do
            gcc "$path" -"$opt" -o "./apps/""$app""_$opt"".exe"
        done
    fi
done

echo "Building complete!"
echo
