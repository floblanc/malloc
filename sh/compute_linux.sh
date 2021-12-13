#!/bin/sh

malloc()
{
	echo "Malloc test:\n"
	read -p 'How many iterations: ' it
	j=0
	i=0
	while [ $i -lt $it ]
	do
		test0=`./run.sh /usr/bin/time -v ./test0 2>&1 | grep "Minor" | cut -d " " -f7`
		test1=`./run.sh /usr/bin/time -v ./test1 2>&1 | grep "Minor" | cut -d " " -f7`
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
}

free()
{
	echo "\nFree test:\n"
	read -p 'How many iterations: ' it
	j=0
	i=0
	while [ $i -lt $it ]
	do

		test1=`./run.sh /usr/bin/time -v ./test1 2>&1 | grep "Minor" | cut -d " " -f7`
		test2=`./run.sh /usr/bin/time -v ./test2 2>&1 | grep "Minor" | cut -d " " -f7`
		ret=`echo "$test1 - $test2" | bc`
		if [ $ret -ge 0 ]
		then
			j=$(($j + 1))
		else
			echo "\n$ret"
		fi
		printf "\rValue:\tTest1:\t$test1\tTest2:\t$test2\tValid : $j/$it"
		i=$(($i + 1))
	done
	echo "\n$j/$it passed the condition"
}

free_quality()
{
	echo "\nQuality of the free:\n"
	read -p 'How many iterations: ' it
	j=0
	i=0
	while [ $i -lt $it ]
	do
		# real_test0=`/usr/bin/time -v ./test0 2>&1 | grep "Minor" | cut -d " " -f7`
		# real_test2=`/usr/bin/time -v ./test2 2>&1 | grep "Minor" | cut -d " " -f7`
		test0=`./run.sh /usr/bin/time -v ./test0 2>&1 | grep "Minor" | cut -d " " -f7`
		test2=`./run.sh /usr/bin/time -v ./test2 2>&1 | grep "Minor" | cut -d " " -f7`
		# real_ret=`echo "$real_test2 - $real_test0"| bc`
		ret=`echo "$test2 - $test0" | bc`
		if [ $ret -ge $ret ]
		then
			j=$(($j + 1))
		else
			# echo "\nReal: $real_ret\nMine: $ret"
			echo "\n$ret"
		fi
		printf "\rValid : $j/$it"
		i=$(($i + 1))
	done
	echo "\n$j/$it passed the condition"
}

realloc()
{
	echo "\nRealloc test:\n"
	./run.sh ./test3 > realloc_test
	test3=`cat -e realloc_test`
	printf "Bonjour\nBonjour\n" > real_realloc_test
	result=`cat -e real_realloc_test`
	if [ "$test3" = "$result" ]
	then
		echo "Valid"
	else
		echo "Not Valid"
	fi
	rm realloc_test real_realloc_test
}

realloc_more()
{
	echo "\nRealloc++ test:\n"
	./run.sh ./test4 > realloc_more_test
	test4=`cat -e realloc_more_test`
	printf "Bonjour\nBonjour\n" > real_realloc_more_test
	result=`cat -e real_realloc_more_test`
	if [ "$test4" = "$result" ]
	then
		echo "Valid"
	else
		echo "Not Valid"
	fi
	rm realloc_more_test real_realloc_more_test
}

error()
{
	echo "\nError Management++ test:\n"
	./run.sh ./test5 > error_management_test
	test5=`cat -e error_management_test`
	printf "Bonjour\n" > real_error_management_test
	result=`cat -e real_error_management_test`
	if [ "$test5" = "$result" ]
	then
		echo "Valid"
	else
		echo "Not Valid"
	fi
	rm error_management_test real_error_management_test
}

show_alloc_mem()
{
	echo "\nShow_alloc_mem test:\n"
	./run.sh ./test6
	echo "\nWith Tiny displayed\n"
	./run.sh ./test6_bis
}

calloc()
{
	echo "\nCalloc test:\n"
	test7=`./run.sh ./test7`
	result=`./test7`
	echo "Real: $result\nMine: $test7"
	if [ "$test7" = "$result" ]
	then
		echo "Valid"
	else
		echo "Not Valid"
	fi
}

# make re -s > /dev/null 2>&1
while :
do :
	clear
	echo "all, malloc, free, free_quality, realloc, realloc_more, error, show_alloc_mem, calloc:"
	read INPUT_STRING
	clear
	case $INPUT_STRING in
		"all")
			malloc
			free
			free_quality
			realloc
			sleep 1
			realloc_more
			sleep 1
			error
			sleep 1
			show_alloc_mem
			calloc
			read -p "Press space to continue" CONTINUE
			;;
		"malloc")
			malloc
			read -p "Press space to continue" CONTINUE
			;;
		"free")
			free
			;;
		"free_quality")
			free_quality
			read -p "Press space to continue" CONTINUE
			;;
		"realloc")
			realloc
			read -p "Press space to continue" CONTINUE
			;;
		"realloc_more")
			realloc_more
			read -p "Press space to continue" CONTINUE
			;;
		"error")
			error
			read -p "Press space to continue" CONTINUE
			;;
		"show_alloc_mem")
			show_alloc_mem
			read -p "Press space to continue" CONTINUE
			;;
		"calloc")
			calloc
			read -p "Press space to continue" CONTINUE
			;;
	esac
done
echo 
echo "That's all folks!"