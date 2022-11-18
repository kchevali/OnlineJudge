#!/bin/bash

# handle directories
exit_script() { popd &> /dev/null; exit; }
root_dir=$PWD
pushd . &> /dev/null

# allow exit code to persist piping
set -o pipefail

# clear output
output_dir=$root_dir/output
clear_output=$3
[ $clear_output -eq 1 ] && { echo "Clearing Output..."; rm -r $output_dir; mkdir $output_dir; }

# check if source is valid
src_dir="$1"
src_file="$2"
src_ext="${src_file##*.}"
[ "$src_ext" == "py" ] || { echo "Not a valid py file" && exit_script; }

# copy test files
if [ $clear_output -eq 1 ]; then
    source $root_dir/scripts/copy_tests.sh $output_dir
    echo "Running: $(basename $test_dir) test cases..."
fi

# run test cases
cd $output_dir
for file in *.in; do
    stdout_output="$output_dir/${file%.*}.stdout"
    stderr_output="$output_dir/${file%.*}.stderr"
    real_output="$output_dir/${file%.*}.ans"
    touch $real_output

    /usr/local/bin/python3.8 $src_dir/$src_file < "$output_dir/$file" > "$stdout_output" 2> "$stderr_output"

    echo ${file%.*}: $(diff "$stdout_output" "$real_output" &> /dev/null && echo PASS || echo FAIL)
done

exit_script