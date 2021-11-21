// child.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  char *message = argv[0];
  int Nc = atoi(argv[1]);
  int Tc = atoi(argv[2]);

  int i = 0;
  for(; i < Nc; i++)
  {
    puts(message);
    sleep(Tc);
  }
  exit(37);
}
