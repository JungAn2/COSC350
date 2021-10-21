#!/bin/bash

#Argument validation
if [ $# -lt 1 ]; then
  echo "You need to pass one numberical argument"
  exit 1
elif [ $# -gt 1 ]; then
  echo "Too many argument was passed"
  exit 1
fi

arg=$1
sum=0

#Diving by 10 removes the ones place thus allowing to get the next place value
while [ $arg -gt 0 ]; do
  let "add = $arg % 10"
  let "sum = $sum + $add"
  let "arg = $arg / 10"
done
echo "Sum of digit for number is $sum"
exit 0
