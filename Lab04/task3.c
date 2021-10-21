#include <unistd.h> //Library for system call function
#include <fcntl.h> //Library for flags
#include <stdio.h>

#define BUFFER_SIZE 1 //Buffer size
int palind(int fd1, int fd2)
{
  //buffer for file 1
  char bufferfd1[BUFFER_SIZE];
  //buffer for file 2
  char bufferfd2[BUFFER_SIZE];
  //Value from reading file 1 and 2
  int fd1nread, fd2nread;
  //Finding the end of the file, it is -2 since the last value is \0
  int end = lseek(fd2, -2, SEEK_END);
  //Holds the middle place of the pelindrome
  int middle = (end/2)+1;
  //The offset position to 0
  int offset = lseek(fd1, 0, SEEK_SET);
  
  //while the offset is not in the middle
  while(offset != middle)
  {
    //Read the buffer from file 1
    if((fd1nread = read(fd1, bufferfd1, BUFFER_SIZE)) == -1)
    {
      write(2, "Read error!\n", 12);
      return -1; //Read error
    }
    
    //Read the buffer from file 2
    if((fd2nread = read(fd2, bufferfd2, BUFFER_SIZE)) == -1)
    {
      write(2, "Read error!\n", 12);
      return -1; //Read error
    }
    
    //Check the buffer read from file 1 and 2 and return if they do not match
    if(bufferfd1[0] != bufferfd2[0])
      return 0; //Not a palindrome

    //Move the position for file 2 back by 2 to read previous
    lseek(fd2, -2, SEEK_CUR);
    //Increase offset by 1
    offset++;
  }
  return 1;
}

int main(int argc, char ** argv)
{
  //Check to see if it is exactly one argument
  if(argc != 2)
  {
    write(2, "Only one argument!\n", 19);
    return 1; //Argument error
  }

  //Gets the name from argument
  char *f_iName = argv[1];
  //Value from opening input file
  int f_in, f_in2;
  //Open the file and check for errors
  if((f_in = open(f_iName, O_RDONLY)) == -1)
  {
    write(2, "Open error!\n", 12);
    return 2; //Open error
  }
  //Open exact same file with another variable
  //and check for error
  if((f_in2 = open(f_iName, O_RDONLY)) == -1)
  {
    write(2, "Open error!\n", 12);
    return 2; //Open error
  }
  //Holds value from palind function
  int palindValue = palind(f_in, f_in2);
  
  //Check to see if it received any read error
  if(palindValue == -1)
    return 3; //Read error
  //Not a palindrome
  else if(palindValue == 0)
    write(1, "Not a palindrome.\n", 18);
  //Palindrome
  else
    write(1, "It is a palindrome.\n", 20);
  //Close the file
  close(f_in);
  close(f_in2);
  return 0;
}
