#!/bin/bash

# fetch tests and results
input_dir="./asserts/in_greedy_assert"
output_dir="./asserts/out_greedy_assert"
refs_dir="./asserts/ref_greedy_assert"

mkdir $output_dir

# compile and make jar
ant compile &>/dev/null
ant jar &>/dev/null

scor=0
tests=10
pointsPerTest=$((100/$tests))

for i in $(seq 1 $tests); do
    timeout 10 java -jar tema.jar $input_dir/test$i.in $output_dir/test$i.out &> /dev/null
    diff -B $output_dir/test$i.out $refs_dir/test$i.ref &> /dev/null
    if test $? -eq 0; then
        echo "Test $i correct"
        scor=$(($scor+10))
    else
        echo "Test $i failed"
    fi
done

echo "Total [$scor/100] points"

rm $output_dir -r
ant clean &> /dev/null
