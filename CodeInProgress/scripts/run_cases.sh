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

# compile source
src_base="${src_file%.*}"
cd $src_dir || { echo "Directory does not exist $src_dir"; exit_script; }

if [ "$src_ext" == "cpp" ]; then
    src_exe="$src_dir/$src_base.exe"
    g++ -std=c++17 "$src_file" -o "$src_exe" 2>&1 | tee "$output_dir/build.err" || { echo "C++ did not compile..."; exit_script; }
elif [ "$src_ext" == "c" ]; then
    src_exe="$src_dir/$src_base.exe"
    gcc "$src_file" -o "$src_exe" 2>&1 | tee "$output_dir/build.err" || { echo "C did not compile..."; exit_script; }
elif [ "$src_ext" == "java" ]; then
    javac "$src_file" 2>&1 | tee "$output_dir/build.err" || { echo "Java did not compile..."; exit_script; }
    src_exe="java $src_base"
elif [ "$src_ext" == "py" ]; then
    src_exe="python3 $src_dir/$src_file"
else
    echo "Not a valid source file (cpp, c, java, py)..."
    exit_script
fi

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

    cd $src_dir
    $src_exe < "$output_dir/$file" > "$stdout_output" 2> "$stderr_output"
    cd - > /dev/null

    echo ${file%.*}: $(diff "$stdout_output" "$real_output" &> /dev/null && echo PASS || echo FAIL)
done

exit_script