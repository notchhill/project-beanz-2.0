#!/bin/bash

input="resource/screenIDs.txt"
prog="./bin/beanz2.exe"

while read line; do 
    #echo "$line" | $prog
    $prog $input
    #echo "$line"
done < $input