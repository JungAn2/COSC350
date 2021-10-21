#include <unistd.h> //read and write
#include <fcntl.h> //For flags for open
#include <stdio.h> //standard input and output
#include <stdlib.h>//Requires for the exit function
#include <utmp.h>

//Open the file utmp
int openUtmpFile()
{
  //Open the file
  int openFile;
  if((openFile = open("/var/run/utmp", O_RDONLY)) == -1)
  {
    perror("File open error!\n");
    exit(0);
  }
  return openFile;
}

int main()
{
  //Open the file
  int file;
  file = openUtmpFile();
  
  return 0;
}
