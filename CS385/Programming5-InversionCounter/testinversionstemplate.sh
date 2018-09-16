#!/bin/bash

file=inversioncounter.cpp
MAXTIME="8.000"

if [ ! -f "$file" ]; then
    echo -e "Error: File '$file' not found.\nTest failed."
    exit 1
fi

num_right=0
total=0
line="________________________________________________________________________"
compiler=
interpreter=
language=
extension=${file##*.}
if [ "$extension" = "py" ]; then
    if [ ! -z "$PYTHON_PATH" ]; then
        interpreter=$(which python.exe)
    else
        interpreter=$(which python3.2)
    fi
    command="$interpreter $file"
    echo -e "Testing $file\n"
elif [ "$extension" = "java" ]; then
    language="java"
    command="java ${file%.java}"
    echo -n "Compiling $file..."
    javac $file
    echo -e "done\n"
elif [ "$extension" = "c" ] || [ "$extension" = "cpp" ]; then
    language="c"
    command="./${file%.*}"
    echo -n "Compiling $file..."
    results=$(make 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "\n$results"
        exit 1
    fi
    echo -e "done\n"
fi

run_test_args() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$3
    local ismac=0
    date --version >/dev/null 2>&1
    if [ $? -ne 0 ]; then
       ismac=1
    fi
    local start=0
    if (( ismac )); then
        start=$(python -c 'import time; print time.time()')
    else
        start=$(date +%s.%N)
    fi
    received=$(echo -e $2 | $command $1 2>&1 | tr -d '\r')
    local end=$(date +%s.%N)
    if (( ismac )); then
        end=$(python -c 'import time; print time.time()')
    else
        end=$(date +%s.%N)
    fi
    local elapsed=$(echo "scale=3; $end - $start" | bc | awk '{printf "%.3f", $0}') 
    if [ "$expected" != "$received" ]; then
        echo -e "failure\n\nExpected$line\n$expected\n"
        echo -e "Received$line\n$received\n"
    else
        result=$(echo $elapsed $MAXTIME | awk '{if ($1 > $2) print 1; else print 0}')
        if [ "$result" -eq 1 ]; then
            echo -e "failure\nTest timed out at $elapsed seconds. Maximum time allowed is $MAXTIME seconds.\n"
        else
            echo "success [$elapsed seconds]"
            (( ++num_right ))
        fi
    fi
}

# TODO - Make sure your code can handle these cases.
run_test_args "" "x 1 2 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 0."
run_test_args "" "1 2 x 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 2."
run_test_args "lots of args" "" "Usage: ./inversioncounter [slow]"
run_test_args "average" "" "Error: Unrecognized option 'average'."
run_test_args "" "" "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."
run_test_args "" "  " "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."

# TODO - write some tests that use the 'slow' approach. Here is one example.
# You are allowed up to 8 seconds to count inversions on up to 100,000 values.
run_test_args "slow" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 1"
run_test_args "slow" "5 3 4 2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 9"
run_test_args "slow" "81 2 5 8 10 1 18 15" "Enter sequence of integers, each followed by a space: Number of inversions: 12"
run_test_args "slow" "8 23 16 4 42 15" "Enter sequence of integers, each followed by a space: Number of inversions: 5"
run_test_args "slow" "100 5 30 61 1111 15 21 20" "Enter sequence of integers, each followed by a space: Number of inversions: 16"
run_test_args "slow" "901 20 2016 7 13 11 92 57 1" "Enter sequence of integers, each followed by a space: Number of inversions: 24"
run_test_args "slow" "22" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "slow" "400 361 324 289 256 225 196 169 144 121 100 81 64 49 36 25 16 9 4 1 0" "Enter sequence of integers, each followed by a space: Number of inversions: 210"
run_test_args "slow" "15 23 37 41 59 67 73 89 91 107 111 125 132 148 150" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "slow" "1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361 400" "Enter sequence of integers, each followed by a space: Number of inversions: 0"

# END slow tests

MAXTIME="1.250"

# TODO - write some tests that use the 'fast' approach. Here is one example.
# You are allowed up to 1.25 seconds to count inversions on up to 100,000 values.
run_test_args "" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 1"
run_test_args "" "5 3 4 2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 9"
run_test_args "" "81 2 5 8 10 1 18 15" "Enter sequence of integers, each followed by a space: Number of inversions: 12"
run_test_args "" "8 23 16 4 42 15" "Enter sequence of integers, each followed by a space: Number of inversions: 5"
run_test_args "" "100 5 30 61 1111 15 21 20" "Enter sequence of integers, each followed by a space: Number of inversions: 16"
run_test_args "" "901 20 2016 7 13 11 92 57 1" "Enter sequence of integers, each followed by a space: Number of inversions: 24"
run_test_args "" "22" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "" "400 361 324 289 256 225 196 169 144 121 100 81 64 49 36 25 16 9 4 1 0" "Enter sequence of integers, each followed by a space: Number of inversions: 210"
run_test_args "" "15 23 37 41 59 67 73 89 91 107 111 125 132 148 150" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "" "1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361 400" "Enter sequence of integers, each followed by a space: Number of inversions: 0"

# END fast tests

echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ "$language" = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
