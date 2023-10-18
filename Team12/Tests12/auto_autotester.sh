#!/bin/bash

# Change to the directory containing the script
script_dir="$(dirname "$0")"
output_dir="$script_dir/output"
mkdir -p "$output_dir"

cd "$script_dir" || exit 1
echo "Current directory: $(pwd)"

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

        # Run the command, might need ${BUILD_TYPE}
        ls /Team12/Code12/build/src/autotester
        ../Code12/build/src/autotester/autotester.exe "$source_file" "$query_file" "$out_file"
    else
        echo "Warning: Query file for $source_file not found!"
    fi
done

# 2. Check if any of the out.xml files contain '<failed>'
# Using find to recursively locate *_out.xml files
find ./output -type f -iname '*_out.xml' | while read -r out_file; do
    if grep -q '<failed>' "$out_file"; then
        echo "Error: $out_file contains '<failed>'"
        exit 1  # This will cause the script to exit with an error
    fi
done
