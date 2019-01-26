#!/bin/bash


#complexity -t0 -s1 mySourceFile1.c mySourceFile2.c
#~kmammen-grader/evaluations/S18/357/
#~kmammen-grader/evaluations/S18/357/
#read -p "Enter Assignment: " assignment
#cp ~kmammen-grader/evaluations/S18/357/$assignment/Makefile $PWD/$assignment/Makefile
#cp ~kmammen-grader/evaluations/S18/357/$assignment/requirements $PWD/$assignment/requirements

for testInput in ~kmammen-grader/evaluations/S18/357/Exercise11/tests/core/*; do
   # Strip off the file extension, i.e., the ".in"
   
   
   name=${testInput%.in}
   echo $name
done