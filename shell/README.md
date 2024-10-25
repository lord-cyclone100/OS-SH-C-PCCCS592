#### Write a shell script to check whether a year is leap year or not

```shell
#!bin/bash
echo "Enter a year:"
read year
if [ $((year%400)) -eq 0 -o $((year%100)) -ne 0 -a $((year%4)) -eq 0 ]
then
	echo "$year is a leap year"
else
	echo "$year is not a leap year"
fi
```

#### Write a shell script to find gcd and lcm of two numbers

```shell
 #!bin/bash

a=$1
b=$2

calculateGCD(){
	a=$1
	b=$2
	i=1
	gcd=0
	while [ $i -le $a -a $i -le $b ]
	do
		if [ $((a % i)) -eq 0 -a $((b % i)) -eq 0 ]
		then
			gcd=$i
		fi
		i=$((i+1))
	done
	echo $gcd
}

calculateLCM(){
	a=$1
	b=$2
	gcd=$3
	lcm=$(( (a*b)/gcd ))
	echo $lcm
}

findGCD=$(calculateGCD $a $b)
echo "GCD is $findGCD"

findLCM=$(calculateLCM $a $b $findGCD)
echo "LCM is $findLCM"
```

#### Write a shell script to check whether a number is an armstrong number or not

```shell
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
```