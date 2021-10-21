#!/bin/sh

#Variable for while loop condition
bool="true"

#Number validation. runs until user gives a valid value
while [ "$bool" == "true" ]; do
echo "Enter a positive integer for factorial."
read number

case $number in
*[0-9]* | '')
if [ "$number" -ge 0 ]; then
	bool="false"
fi ;;
esac
done

factorial=1

#Factorial using while loop
while [ "$number" -ge 0 ]; do
if [ "$number" -eq 0 ]; then
let "factorial=factorial*1"
else
let "factorial=factorial*number"
fi
let number--
done

echo $factorial

exit 0
