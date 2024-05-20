#!/bin/bash

# Define the directory containing the log files
log_directory="user_logs"

# Check if the directory exists
if [ ! -d "$log_directory" ]; then
  echo "Directory '$log_directory' does not exist."
  exit 1
fi

# Initialize variables to track max and min logins
max_logins=0
min_logins=0
max_date=""
min_date=""

# Header for the output
echo "Date | Unique Logins"

# Loop through each log file in the directory
for file in "$log_directory"/log_*.txt; do
  if [ -f "$file" ]; then
    # Extract the date from the filename
    date=$(basename "$file" .txt | cut -d '_' -f 2)

    # Count unique usernames (unique logins)
    unique_logins=$(sort "$file" | uniq | wc -l)

    # Print the date and number of unique logins
    echo "$date | $unique_logins"

    # Update max and min logins and corresponding dates
    if [[ $unique_logins -gt $max_logins ]]; then
      max_logins=$unique_logins
      max_date=$date
    fi

    if [[ $min_logins -eq 0 || $unique_logins -lt $min_logins ]]; then
      min_logins=$unique_logins
      min_date=$date
    fi
  fi
done

# Display the date with the highest and lowest number of unique logins
echo "Maximum Unique Logins: $max_logins on $max_date"
echo "Minimum Unique Logins: $min_logins on $min_date"