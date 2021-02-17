#/bin/sh
read -p 'How many iterations: ' it
j=0
i=0
while [ $i -lt $it ]
do
	test0=`./run_linux.sh /usr/bin/time -v ./test0 2>&1 | grep "Minor" | cut -d " " -f7`
	test1=`./run_linux.sh /usr/bin/time -v ./test1 2>&1 | grep "Minor" | cut -d " " -f7`
	ret=`echo "$test1 - $test0" | bc`
	if [ $ret -gt 254 -a $ret -lt 254 ]
	then
		j=$(($j + 1))
	fi
	echo -n "Value:\t$ret\tValid : $j/$it"\\r
	i=$(($i + 1))
done
echo "$j/$it passed the condition"
