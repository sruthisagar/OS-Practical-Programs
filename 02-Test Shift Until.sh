#!/bin/bash

#Test command
echo "Test command"
[ 32 -lt 67 ]
echo $?
echo

#Shift command
echo "Shift command"
echo "Total number of arguments passed: $#"
echo "The arguments are $*"
echo "The first argument is $1"
shift 2
echo "After shift 2, the first argument is $1"
echo

#Until command
echo "Until command"
i=0
until [ $i -gt 5 ]
do
    echo -n "$i "
    i=$((i+1))
done
echo