#! /bin/bash
cd CodeTester
printf "..Running..\n"
TIMEFORMAT=%R
for i in /Users/kevin/Documents/ACMSolutions/2016/Alphabet/data/*.in; do
    [ -f "$i" ] || break
    t=$( time (python3 Main.py < "$i" > "temp.out")2>&1 1>/dev/null)
    if [[ $? == "0" ]]
    then
        diff -w temp.out "${i%%.*}.out" > /dev/null
        if [[ $? == "0" ]]
        then
            if (( $(awk 'BEGIN {print ("'$t'" <= "'1'")}') ))
            then
            x=$((x+1))
            echo "YES: $t s"
            else
            echo "TLE: $t s - $(basename "$i" .in)"
            fi
        else
        echo " NO: $t s - $(basename "$i" .in)"
        fi
    else
    echo "Crash: $(basename "$i" .in)"
    fi
    y=$((y+1))
done
echo "Accuracy: $((100*x/y))%"
