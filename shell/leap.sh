#!bin/bash
echo "Enter a year:"
read year
if [ $((year%400)) -eq 0 -o $((year%100)) -ne 0 -a $((year%4)) -eq 0 ]
then
	echo "$year is a leap year"
else
	echo "$year is not a leap year"
fi
