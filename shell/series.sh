factorial(){
	a=$1
	f=1
	for i in $(seq 1 $a)
	do
		f=$((f*i))
	done
	echo $f
}

echo "Enter the value of x"
read x
echo "Enter the value of n"
read n

a=$(factorial $n)
echo $a
