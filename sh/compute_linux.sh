#!/bin/sh
make re -s > /dev/null 2>&1
read -p 'How many iterations: ' it
j=0
i=0
while [ $i -lt $it ]
do
	test0=`./run_linux.sh /usr/bin/time -v ./test0 2>&1 | grep "Minor" | cut -d " " -f7`
	test1=`./run_linux.sh /usr/bin/time -v ./test1 2>&1 | grep "Minor" | cut -d " " -f7`
	ret=`echo "$test1 - $test0" | bc`
	if [ $ret -gt 254 -a $ret -lt 273 ]
	then
		j=$(($j + 1))
	else
		echo "\n$ret"
	fi
	printf "\rValue:\t$ret\tValid : $j/$it"
	i=$(($i + 1))
done
echo "\n$j/$it passed the condition"
