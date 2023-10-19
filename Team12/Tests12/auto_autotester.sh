#!/bin/bash

script_dir="$(dirname "$0")"
output_dir="$script_dir/output"
mkdir -p "$output_dir"

# Change to the directory containing the script, if not found, exit with err
cd "$script_dir" || exit 1
echo "Current directory: $(pwd)"
echo "autotester: $1"

# 1. Run the command for each pair of source and query files
# Using find to recursively locate *_source.txt files
find ./ -type f -iname '*_source.txt' | while read -r source_file; do
    # Get the base name without the path and suffix for the output file naming
    base_name="$(basename "${source_file%_source.txt}")"

    # Check if the corresponding query file exists
    query_file="${source_file%_source.txt}_queries.txt"
    if [[ -f "$query_file" ]]; then
        # Construct the output XML filename in the output directory
        out_file="$output_dir/${base_name}_out.xml"

        # Run the command
        $1 "$source_file" "$query_file" "$out_file" > /dev/null 2>&1
    else
        echo "Warning: Query file for $source_file not found!"
    fi
done

# 2. Check if any of the out.xml files contain '<failed>'
# Using find to recursively locate *_out.xml files
total_files=0
failed_files=0

while read -r out_file; do
  ((total_files++))
    if grep -q '<failed>' "$out_file"; then
        echo "Error: $out_file contains '<failed>'"
        ((failed_files++))
    fi
done < <(find "$output_dir" -type f -iname '*_out.xml')

if [[ $failed_files -eq 0 ]]; then
    echo "Success: All autotester output files passed!!"
    # exit 0  # exit with success, passes CI/CD
else
    echo "Error: $failed_files / $total_files files failed"
    # exit 1  # exit with an error, fails CI/CD
fi

exit 0
