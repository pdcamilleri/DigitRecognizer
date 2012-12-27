#!/bin/bash

for line in `cat output.txt`; do 
   echo $line | tr ',' '\n' | sort | uniq -c | sort -nr | sed -e "s/[ ].*[ ]//g" | head -1
done
