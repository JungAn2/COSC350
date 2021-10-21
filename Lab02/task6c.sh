#!/bin/sh

echo "Enter a value that is great than or equal to 3 for the arrow"
read number

let "compare = $number % 2"

#Validation check
if [ $compare -eq 0 ]; then
  echo "You have entered even number"
  exit 1
elif [ $number -lt 3 ]; then
  echo "You have entered number less than 3"
  exit 1
fi

echo "Enter a value for a tail"
read tail

star=1

for i in $(seq 1 $number); do
  #Drawing tail space or star
  if [ $i -eq `expr $number / 2 + 1` ]; then
    for j in $(seq 1 $tail); do
      echo -n "*"
    done
  else
    for k in $(seq 1 $tail); do
      echo -n " "
    done
  fi
  #Drawing arrow
  for l in $(seq 1 $star); do
    echo -n "*"
  done
  echo ""
  #The star number increase until half of the number and decrease afterwards
  if [ $i -le `expr $number / 2` ]; then
    let "star = $star + 2"
  else
    let "star = $star - 2"
  fi
done

exit 0

