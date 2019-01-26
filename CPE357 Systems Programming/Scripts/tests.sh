#!/bin/bash

testnum=0
temp=" "

for testInput in *.c; do   
	temp="$temp $testInput"	
done

printf "\nEvaluating complexity : $temp \n"
   complexity -t0 -s1 $temp
   
printf "\nEvaluating style : $temp  \n"
   ~kmammen-grader/bin/styleCheckC $temp


for testInput in `ls $PWD/input/*.in | sort -V`; do
    input=$(basename $testInput)
    name=${input%.in}
    echo Test number $testnum : $input
   
	./a.out < $testInput > $PWD/output/my_$name.out   
   ~kmammen/357/Project1/mastermind <$testInput > $PWD/output/his_$name.out

   let "testnum += 1"
   diff -q $PWD/output/my_$name.out $PWD/output/his_$name.out
done
