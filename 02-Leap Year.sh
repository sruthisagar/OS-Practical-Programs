#!/bin/bash

read -p "Enter the year " year   

if [[ ($((year % 4)) -eq 0) && ($((year % 100)) -ne 0) || ($((year % 400)) -eq 0) ]]
then
    echo "Leap year"
else
    echo "Not leap year"
fi 