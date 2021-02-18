#!/bin/bash
make re -s > /dev/null 2>&1
read -p 'How many iterations: ' it
j=0
i=0
while [ $i -lt $it ]
do
	test0=`./run_mac.sh /usr/bin/time -l ./test0 2>&1 | grep "page reclaims" | cut -d " " -f18`
	test1=`./run_mac.sh /usr/bin/time -l ./test1 2>&1 | grep "page reclaims" | cut -d " " -f18`
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