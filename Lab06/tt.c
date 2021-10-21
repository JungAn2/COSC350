#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
int main (int argc, const char*argv[])
{
pid_t pid;
int mult = 1, i;
if(argc == 1){
    printf("argument error \n");
exit(1);}
if( (pid = fork()) < 0)
  /* create child */
{printf("fork error\n");
exit(1);}
else if(pid == 0){
   /* a child execute different program */if(execv ("/mnt/linuxlab/home/ja67671/COSC350/Lab06/test", argv) <0)    
     {                    
 printf ("execl ERROR");
exit(1);}}
for(i = 1; i <argc; i++)
       mult *= atoi(argv[i]);
printf ("The multiplication of arguments is %d \n", mult);
exit (0);}
