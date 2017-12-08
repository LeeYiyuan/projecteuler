#!/bin/bash

make clean > /dev/null
make utils > /dev/null

tts=$(date +%s%N)
err=0
for i in {001..161}
do
    ts=$(date +%s%N)
    make $i > /dev/null
    result=$(./run)
    tt=$((($(date +%s%N) - $ts)/1000000))
    answer=$(sed "${i}q;d" answers.txt)

    if [[ "$result" == "$answer" ]]
    then
        printf '  '
    else
        err=1
        printf ' x'
    fi

    printf " | %4s | %6s ms | ${result}\n" $i $tt
done
ttt=$((($(date +%s%N) - $tts)/1000000000))

if [[ $err == 1 ]]
then
    printf ' x'
else
    printf '  '
fi
printf ' |  ALL | %6s  s | \n' $ttt


make clean > /dev/null
