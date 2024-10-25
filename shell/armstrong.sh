#!bin/bash

echo "Enter a number:"
read num
saved_num=$num
temp_num=$num
s=0
count=0
while [ $num -ne 0 ]
do
	count=$((count + 1))
	num=$((num / 10))
done
while [ $temp_num -ne 0 ]
do
	rem=$((temp_num%10))
	pow=$(echo "$rem ^ $count" | bc)
	s=$((s + pow))
	temp_num=$((temp_num / 10))
done
if [ $s -eq $saved_num ]
then
	echo "$saved_num is an Armstrong number"
else
	echo "$saved_num is not an Armstrong number"
fi

