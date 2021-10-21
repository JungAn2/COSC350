#!/bin/sh

echo "Enter a directory. Add / at the end"
read directory

#Directory validation
if ! [ -d "$directory" ]; then
  echo "not a directory"
  exit 1 #no such directory
fi

#While loop condition variable
loop="true"
fail=3

while [ $loop = "true" ]; do
  echo "Enter name of readable file"
  read file

  file=$directory$file

  #File validation
  if [ -f $file ]; then
    loop="false"
  else
    echo "Invalid file"
    #Check for number of tries
    if [ $fail -le 1 ]; then
      echo "You have entered wrong file name 3 times. The program will now terminate"
      exit 2 #no such file
    fi
    echo "try again"
    let "fail=$fail-1"
   fi
done

#readable validation
if ! [ -r $file ]; then
  echo "File not readable"
  exit 3 #file is not readable
fi

echo "Enter a word to find in the file"
read word

#silent grep of $word
if grep -q $word $file; then
  echo "$word FOUND!"
else
  echo "$word NOT FOUND"
  exit 4   
fi

exit 0
