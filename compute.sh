test0=`./run_mac.sh /usr/bin/time -l ./test0 2>&1 | grep " maximum resident set size" | cut -d " " -f-5`
test1=`./run_mac.sh /usr/bin/time -l ./test1 2>&1 | grep " maximum resident set size" | cut -d " " -f-5`
div=$(getconf PAGESIZE)

echo "($test1 - $test0) / $div" | bc