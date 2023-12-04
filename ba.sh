#!/bin/bash

input="resource/screenIDs.txt"
prog="./bin/beanz2.exe"

while read line; do 
    $prog $input
done < $input