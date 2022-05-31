#!/bin/bash

COMPILER_PATH=./compiler
passed=0
total=0

run_tests() {
	tests_path=$1
	isKO=$2
	command=""
	command_passed_icon=""
	command_failed_icon=""
	
	for filename in $tests_path; do
		if [ $isKO -eq 0 ]; then
			command="$COMPILER_PATH $filename > /dev/null"
			command_passed_icon="✔️  "
			command_failed_icon="❌  "
		else
			command="$COMPILER_PATH $filename &> /dev/null"
			command_passed_icon="❌  "
			command_failed_icon="✔️  "
		fi
			
		if eval $command; then
			((passed += $isKO ^ 1))
			printf "$command_passed_icon"
		else
			((passed += $isKO ^ 0))
			printf "$command_failed_icon"
		fi
		n=$(echo $filename | grep -o -E '[0-9]+')
		printf "TEST $n\n"
		
		((total++))
	done
	
	return 0
}

printf "____ OK TESTS ______\n"
run_tests "./tests/ok/test*" 0
printf "\n____ KO TESTS ____\n"
run_tests "./tests/ko/test*" 1

printf "\n$passed/$total passed\n"
