#!/bin/bash

# handle directories
exit_script() { popd &> /dev/null; exit; }
pushd . &> /dev/null

# allow exit code to persist piping
set -o pipefail

# clear output
output_dir=$PWD/output
clear_output=$3
[ $clear_output -eq 1 ] && { echo "Clearing Output..."; rm -r $output_dir; mkdir $output_dir; }

# check if source is valid
src_dir="$1"
src_file="$2"
src_ext="${src_file##*.}"
[ "$src_ext" == "cpp" ] || { echo "Not a valid cpp file" && exit_script; }

# compile source
src_base="${src_file%.*}"
src_exe="$src_base.exe"
cd $src_dir && g++ -std=c++17 "$src_file" -o "$src_exe" 2>&1 | tee "$output_dir/build.err" || { echo "Source did not compile..."; exit_script; }

# copy test files
if [ $clear_output -eq 1 ]; then
    source copy_tests.sh $output_dir
    echo "Running: $(basename $test_dir) test cases..."
fi

# run test cases
cd $output_dir
for file in *.in; do
    stdout_output="$output_dir/${file%.*}.stdout"
    stderr_output="$output_dir/${file%.*}.stderr"
    real_output="$output_dir/${file%.*}.ans"
    touch $real_output

    $src_dir/$src_exe < "$output_dir/$file" > "$stdout_output" 2> "$stderr_output"

    echo ${file%.*}: $(diff "$stdout_output" "$real_output" &> /dev/null && echo PASS || echo FAIL)
done

exit_script