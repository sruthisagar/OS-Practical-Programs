#!/bin/bash

factorial()
{
    fact=1
    for (( i=1; i <= $n; i++ ))
    do
        fact=$((fact*i))
    done
    echo "Factorial of $n is $fact"
}

read -p "Enter a number " n
factorial $n