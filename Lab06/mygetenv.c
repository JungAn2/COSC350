#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char **envp)
{
  if(argc != 2)
  {
    perror("Need one argument\n");
    exit(1);
  }

  //Environ
  char **en = envp;
  char *env = *en;
  //Length of the Env name
  int len;
  //Boolean to check when to end the while loop
  int boolean = 0;
  while(*en != NULL && boolean == 0)
  {
    boolean = 1;
    int i;
    //Easier to use env
    //Check the name of the env and the length
    for(i = 0; env[i] != '='; i++)
    {
      len = i+1;
    }
    //Check if argv has same length as environment variable name
    if(len != strlen(argv[1]))
    {
      boolean = 0;
      *en++;
    }
    else
    {
      //Check for each letter to see if they are equal
      for(i = 0; i < len; i++)
      {
        if(env[i] != argv[1][i])
        {
          boolean = 0;
          *en++;
        }
      }
    }
    env = *en;
  }
  //Environment variable not found
  if(en == NULL)
    printf("No environment variable found\n"); 
  else
  {
    //Print the Environment variable without the name and = sign
    int size = strlen(env) - (len + 1);
    char *final = malloc(size*sizeof(char));
    int i;
    for(i = 0; i < size; i++)
      final[i] = env[i+len+1];
    printf("%s\n", final);
    free(final);
  }

  return 0;//Successful run
}
