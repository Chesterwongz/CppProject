#!/bin/bash

script_dir="$(dirname "$0")"
input_dir="$script_dir"
output_dir="$script_dir/output"
rm -r "$output_dir"
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
while IFS= read -r -d $'\0' source_file; do
    # Get the base name with the path, without the "_source.txt" suffix
    base_name="${source_file%_source.txt}"

    # Replace '/' with '_' to use in filename
    filename_safe_base_name="${base_name//\//_}"

    # Check if the corresponding query file exists
    query_file="${source_file%_source.txt}_queries.txt"
    if [[ -f "$query_file" ]]; then
        # Construct the output XML filename in the output directory
        out_file="$output_dir/${filename_safe_base_name}_out.xml"
        # Run the command
        echo "[INFO] Executing $query_file"
        "$1" "$source_file" "$query_file" "$out_file" > /dev/null 2>&1
    else
        echo "[WARN] Query file for $source_file not found!"
    fi
done < <(find "$input_dir" -type f -iname '*_source.txt' -print0)

# 2. Check if any of the out.xml files contain '<failed>'
# Using find to recursively locate *_out.xml files
while read -r out_file; do
    ((total_files++))
    if grep -q '<failed>' "$out_file"; then
        echo "Error: $out_file contains '<failed>'"
        ((failed_files++))
    fi
done < <(find "$output_dir" -type f -iname '*_out.xml')

if [[ $failed_files -eq 0 ]]; then
    echo "Success: All $total_files autotester output files passed!!"
    exit 0  # exit with success, passes CI/CD
else
    echo "Summary: $failed_files / $total_files files failed"
    exit 1  # exit with an error, fails CI/CD
fi
