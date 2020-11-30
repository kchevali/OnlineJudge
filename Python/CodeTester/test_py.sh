#! /bin/bash
cd CodeTester
printf "..Running..\n"
javac Main.java
TIMEFORMAT=%R
for i in /Users/kevin/Documents/ACMSolutions/2017/OddPalindrome/data/secret/*.in; do
# for i in /Users/kevin/Documents/Code/Java/CodeTester/IO/*.in; do
    [ -f "$i" ] || break
    t=$( time (python3 Main.py < "$i" > "temp.ans")2>&1 1>/dev/null)
    if [[ $? == "0" ]]
    then
        diff -w temp.ans "${i%%.*}.ans" > /dev/null
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
