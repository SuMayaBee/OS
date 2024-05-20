#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Directory not found."
    exit 1
fi

dir=$1

if [ ! -d "$dir" ]; then
    echo "Not Directory"
    exit 1
fi

echo "File_Name         LOC            Size"
echo "---------------------------------------"

list=($(find "$dir" -type f -name "*.c" -or -name "*.cpp"))
for file in "${list[@]}"; do
    loc=$(wc -l < "$file")
    size=$(stat -c%s "$file")
    echo "$(basename "$file")      $loc    $size bytes"
done
