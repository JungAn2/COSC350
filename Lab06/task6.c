#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1
int main(int argc, char ** argv)
{
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
  lseek(f_in, 0, SEEK_SET);

  //Fork
  pid = fork();
  //parent
  if(pid == 1)
    {
      umask(0000);
      f_out = open("parent.txt", O_WRONLY || O_CREAT, 0755); 
      while(end > lseek(f_in, 0, SEEK_CUR)){
      nread = read(f_in, buffer, BUFFER_SIZE);
      if(buffer[0] >= '0' && buffer[0] <= '9')
        write(f_out, buffer, nread); 
      }
    }
  //child
  else
    {
      umask(0000);
      f_out = open("child.txt", O_WRONLY || O_CREAT, 0755);
      while(end > lseek(f_in, 0, SEEK_CUR)){      
      nread = read(f_in, buffer, BUFFER_SIZE);
      if(buffer[0] < '0' && buffer[0] > 9)
        write(f_out, buffer, nread);
      }
    }
  
  exit(0);
}
