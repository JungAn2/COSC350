#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  int check;
  struct stat buf;
  
  //character pointer to each assigned string
  char *Dir1 = "/mnt/linuxlab/home/ja67671/Dir1";
  char *Dir2 = "/mnt/linuxlab/home/ja67671/Dir2";
  char *Dir21 = "/mnt/linuxlab/home/ja67671/Dir2/Dir21";
  char *hello = "/mnt/linuxlab/home/ja67671/Dir2/Dir21/hello";
  char *symLinkDir = "/mnt/linuxlab/home/ja67671/Dir1/toDir21";
  char *symLinkHello = "/mnt/linuxlab/home/ja67671/Dir1/toHello";
  //Check to see if there is directory called Dir1
  if(stat(Dir1, &buf) == -1)
  {
    //Reset permission
    umask(0000);
    //Make Dir1 and check for error
    if((check = mkdir(Dir1, 0755)) == -1)
    {
      printf("Make Dir1 error\n");
      return 1;//Make dir error
    }
  }
  //If the directory does not exist create the directory Dir2
  if(stat(Dir2, &buf) == -1)
  {
    //Reset permission
    umask(0000);
    //Make Dir2 and check for error
    if((check = mkdir(Dir2, 0755)) == -1)
    {
      printf("Make Dir2 error\n");
      return 1;//Make dir error
    }
  }
  //If directory does not exist create directory Dir21
  if(stat(Dir21, &buf) == -1)
  {
    //Reset permission
    umask(0000);
    //Make Dir21 and check for error
    if((check = mkdir(Dir21, 0755)) == -1)
    {
      printf("Make dir21 error\n");
      return 1;//Make dir error
    }
  }
  //check to see if there is a file already exist called hello
  if(stat(hello, &buf) == -1)
  {
    //Link hello file from current directory to assigned hello directory
    //and check for link error
    if(link("hello", hello) == -1)
    {
      printf("Link error\n");
      return 2;//Link error
    }
  }
  //Check to see if symLinkDir already exist
  if(stat(symLinkDir, &buf) == -1)
  {
    //Link a symbolic link with name symLinkDir to Dir21
    //and check for symbolic link error
    if(symlink(Dir21, symLinkDir) == -1)
    {
      printf("Symbolic link error\n");
      return 3;//Symbolic link error
    }
  }
  //Check to see if symLinkHello already exist
  if(stat(symLinkHello, &buf) == -1)
  {
    //Link a symbolic link with name symLinkHello to hello in Dir21
    //and check for symbolic link error
    if(symlink(hello, symLinkHello) == -1)
    {
      printf("Symbolic link error\n");
      return 3;//Symbolic link error
    }
  }


  return 0;
}
