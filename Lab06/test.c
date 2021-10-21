#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
  puts(getenv("HOME"));
  return 0;
}
