#!/bin/bash

script_dir="$(dirname "$0")"
output_dir="$script_dir/output"
mkdir -p "$output_dir"

# Change to the directory containing the script, if not found, exit with err
cd "$script_dir" || exit 1
echo "Current directory: $(pwd)"
echo "autotester: $1"

# if autotester argument not provided, exit with err
if [ -z "$1" ]; then
    echo "File path for autotester not provided."
    exit 1
fi

total_files=0
failed_files=0

# 1. Run the command for each pair of source and query files
# Using find to recursively locate *_source.txt files
while read -r source_file; do
    # Get the base name without the path and suffix for the output file naming
    base_name="$(basename "${source_file%_source.txt}")"

    # Check if the corresponding query file exists
    query_file="${source_file%_source.txt}_queries.txt"
    if [[ -f "$query_file" ]]; then
        # Construct the output XML filename in the output directory
        out_file="$output_dir/${base_name}_out.xml"
        ((total_files++))
        # Run the command
        echo "[INFO] Executing :wq!
        $query_file"
        $1 "$source_file" "$query_file" "$out_file" > /dev/null 2>&1
    else
        echo "[WARN] Query file for $source_file not found!"
    fi
done < <(find ./ -type f -iname '*_source.txt')

# 2. Check if any of the out.xml files contain '<failed>'
# Using find to recursively locate *_out.xml files
while read -r out_file; do
    if grep -q '<failed>' "$out_file"; then
        echo "Error: $out_file contains '<failed>'"
        ((failed_files++))
    fi
done < <(find "$output_dir" -type f -iname '*_out.xml')

if [ "$failed_files" -eq "$total_files" ]; then
    echo "Success: All $total_files autotester output files passed!!"
    exit 0  # exit with success, passes CI/CD
else
    echo "Summary: $failed_files / $total_files files failed"
    exit 1  # exit with an error, fails CI/CD
fi
