#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
 struct stat buf;
 char *g = argv[1];
 if(stat(g, &buf) == -1)
   printf("file not found");
 if(stat("/mnt/linuxlab/home/ja67671/Dir1", &buf) == -1)
   printf("file not found");
 else
   printf("file found");
 return 0;
}
