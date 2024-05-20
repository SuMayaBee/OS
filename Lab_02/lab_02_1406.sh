#!/usr/bin/env bash
search_dir="/home/yasin/CSE-301"
#search_dir=$1
files=$(find "$search_dir" -type f -name "*.cpp" -o -name "*.c")
printf "%-40s %-10s %-10s\n\n" "File Name"	"File Size" "Lines of Code"
for entry in $files; do
	curr_file=$(basename $entry)
	file_size=$(wc -c < $entry)
	loc=$(wc -l < $entry)
	printf "%-40s %-10s %-10s\n" "$curr_file"	"$file_size" "$loc"
done

