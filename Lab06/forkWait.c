// fork1.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  //Need 4 argument
  if(argc != 5) {
    perror("Need 4 arguements!\n");
    exit(1);
  }
  //Arguments
  int Nc = atoi(argv[1]);
  int Np = atoi(argv[2]);
  int Tc = atoi(argv[3]);
  int Tp = atoi(argv[4]);

  pid_t pid;
  char *message;
  int n, s;
  int exit_code;

  printf("fork program starting\n");
  pid = fork();
  switch(pid) {
  case -1:
    perror("fork failed");
    exit(1);
  case 0:
    message = "This is the child";
    n = Nc;
    s = Tc;
    exit_code = 37;
    break;
  default:
    message = "This is the parent";
    n = Np;
    s = Tp;
    exit_code = 0;
    break;
  }
  for(; n > 0; n--){
    puts(message);
    sleep(s);
  }
  if(pid != 0) {
    int stat_val;
    pid_t child_pid;

    child_pid = wait(&stat_val);

    printf("Child has finished: PID = %d\n", child_pid);
    if (WIFEXITED (stat_val))
      printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
    else
      printf("Child terminated abnormally\n");
  }
  exit(exit_code);
}
