#!/bin/bash

printf "\nTEST1\n"
cat ./tests/ok/test1 | ./compiler

printf "\n\nTEST2\n"
cat ./tests/ok/test2 | ./compiler

printf "\n\nTEST3\n"
cat ./tests/ok/test3 | ./compiler

printf "\n\nTEST4\n"
cat ./tests/ok/test4 | ./compiler

printf "\n\nTEST5\n"
cat ./tests/ok/test5 | ./compiler
