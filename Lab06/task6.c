#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1
int main(int argc, char ** argv)
{
  //Check for number of argument
  if(argc != 2)
  {
    perror("Need 1 argument");
    exit(1);
  }
  //Get the file name
  char *f_Name = argv[1];
  //File descriptor
  int f_in, f_out;
  //Buffer to read
  char buffer[BUFFER_SIZE];
  int nread;
  //pid value(parent child)
  pid_t pid;
  
  //Open the file
  f_in = open(f_Name, O_RDONLY);
  //Get the end
  int end = lseek(f_in, 0, SEEK_END);
  int offset = lseek(f_in, 0, SEEK_SET);
  //Reset permission
  umask(0000);

  //Fork
  pid = fork();
  if(pid == -1)
  {
    perror("fork error");
    exit(1);
  }

  //child
  else if(pid == 0)
    {
      //Open up child file
      f_out = open("child.txt", O_WRONLY | O_CREAT, 0755);
      //read and write until end of the file
      while(end > offset){      
      nread = read(f_in, buffer, BUFFER_SIZE);
      if(buffer[0] < '0' || buffer[0] > '9')
        write(f_out, buffer, nread);
      offset++;
      }
    }

   //parent
  else
    {
      //Open up parent file
      f_out = open("parent.txt", O_WRONLY | O_CREAT, 0755); 
      //Read and write until end of the file
      while(end > offset){
      nread = read(f_in, buffer, BUFFER_SIZE);
      if(buffer[0] >= '0' && buffer[0] <= '9' || buffer[0] == '\n')
        write(f_out, buffer, nread); 
      offset++;
      }
    } 

  exit(0);
}
