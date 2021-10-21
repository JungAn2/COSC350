// child.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  char *message = argv[1];
  int Nc = atoi(argv[2]);
  int Tc = atoi(argv[3]);

  int i = 0;
  for(; i < Nc; i++)
  {
    puts(message);
    sleep(Tc);
  }
  exit(0);
}
