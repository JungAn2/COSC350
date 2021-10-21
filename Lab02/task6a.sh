#!/bin/sh

echo "Enter a value that is great than or equal to 3"
read number

let "compare = $number % 2"

#Validation
if [ $compare -eq 0 ]; then
  echo "You have entered even number"
  exit 1
elif [ $number -lt 3 ]; then
  echo "You have entered number less than 3"
  exit 1
fi

let "empty = -$number / 2"
star=1

for i in $(seq 1 $number); do
  #Drawing empty spaces
  for j in $(seq 1 ${empty#-}); do
    echo -n " "
  done
  #Drawing stars
  for k in $(seq 1 $star); do
    echo -n "*"
  done
  echo ""
  let "empty = $empty + 1"
  #Increase star by 2 until half of the number. Decrease by 2 afterwards
  if [ $i -le `expr $number / 2` ]; then
    let "star = $star + 2"
  else
    let "star = $star - 2"
  fi
done

exit 0
  
