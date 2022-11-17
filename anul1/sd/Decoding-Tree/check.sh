#!/bin/bash

#
# Tema3 Test Suite
#
# 2016, SD
#

# ----------------- General declarations and util functions ------------------ #

INPUT_DIR=input/
REF_DIR=refs/
OUT_DIR=output/
EXEC_NAME=./tema3
VALGRIND="valgrind --leak-check=full -q --log-file=a.out"
max_points=85
result_points=0

print_header()
{
	header="${1}"
	header_len=${#header}
	printf "\n"
	if [ $header_len -lt 71 ]; then
		padding=$(((71 - $header_len) / 2))
		for ((i = 0; i < $padding; i++)); do
			printf " "
		done
	fi
	printf "= %s =\n\n" "${header}"
}

test_do_fail()
{
	printf "failed  [ 0/%02d]\n" "$max_points"
	if test "x$EXIT_IF_FAIL" = "x1"; then
		exit 1
	fi
}

test_do_pass()
{
	printf "passed  [%02d/%02d]\n" "${1}" "$max_points"
	((result_points+=${1}))
}

test_function()
{
	inputTextFile="$INPUT_DIR${2}"
	inputCodeFile="$INPUT_DIR${1}"

	outTreeFile="$OUT_DIR${3}"
	outTextFile="$OUT_DIR${4}"

	refTreeFile="$REF_DIR${5}"
	refTextFile="$REF_DIR${6}"

	points_per_test="${7}"
	points_per_test_vg="${8}"
	
	$EXEC_NAME $inputCodeFile $inputTextFile $outTreeFile $outTextFile 

	diff $outTreeFile $refTreeFile > /dev/null
	ret_diff1=$?
	diff $outTextFile $refTextFile > /dev/null
	ret_diff2=$?

	if test $ret_diff1 -eq 0 && test $ret_diff2 -eq 0; then
		printf "[%s]..........................................." ${2}
		test_do_pass $points_per_test
		#valgrind test

		$VALGRIND $EXEC_NAME $inputCodeFile $inputTextFile $outTreeFile $outTextFile > /dev/null
		if [[ -z $(cat a.out) ]]; then
			printf "[VALGRIND: %s]................................." ${2}
			test_do_pass $points_per_test_vg
		else
			printf "[VALGRIND: %s]................................." ${2}
			test_do_fail
		fi

		#rm -rf a.out;
	else
		printf "[%s]..........................................." ${2}
		test_do_fail
		printf "[VALGRIND: %s]................................." ${2}
		test_do_fail
	fi
}

bonus_function()
{
	echo ""
}

init_function()
{
    make build
	mkdir $OUT_DIR &> /dev/null
}

clean_out_function()
{
    rm output/*.*
    rmdir output
}

init_function

print_header "Tema 3 SD Decodificare"

#Testing

#array for input values
#declare -a input_values=(19 19 19 15 20 20 20 4 7 5 4 2)
#array for test weights
declare -a tests_weights=(0 6 8 9 8 8 8 8 10 10 10)
#array for valgrind test weights
declare -a valgrind_tests_weights=(0 2 2 2 2 2 2 2 2 2 2)


for i in {1..10}
do
	test_function "cod$i.in" "text$i.in" "arbore$i.out" "text$i.out" "arbore$i.out" "text$i.out" "${tests_weights[$i]}" "${valgrind_tests_weights[$i]}" 
	echo ""
done

#end Testing

printf "\n%49s [%02d/85]\n" "Total:" $result_points;

clean_out_function

echo
