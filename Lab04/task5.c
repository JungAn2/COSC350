#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/*//Checks the last file name for the rename
int nameCheck(char *from, char *des)
{
  int rtn = 0;
  //Gets the size of the strings
  int from_i = strlen(from) -1;
  int des_i = strlen(des) -1;
  //Gets only the name of the file from each path
  while(from[from_i] != '/')
    from_i--;
  while(des[des_i] != '/')
    des_i--;
  if(strlen(from) - from_i == strlen(des) - des_i)
  {
    //Check if they are the same
    while(from_i != strlen(from)-1 || des_i != strlen(des)-1)
    {
      if(from[from_i] != des[des_i])
        rtn = 1;
      from_i++;
      des_i++;
    }
    //If one of the string does not end return false
    if(from_i != strlen(from) && des_i != strlen(des))
      rtn = 1;
    }
    else
      rtn = 1;
    return rtn; 
}
*/

//Uses directory name to add *from* file name
char *dirFile(char *from, char *des)
{
  //Return pointer
  char *final;
  int i, j;
  //Initialize i to be used in while loop
  i = strlen(from) - 1;
  //Gets the index where the first / is shown from end of the string
  while(from[i] != '/' && i != 0)
    i--;
  //The size of character array for final and create a memory of that size
  int size = strlen(des) + strlen(from) - i;
  final = (char*) malloc(size*sizeof(char));
  //Copy directory from *destination file*
  for(j = 0; j < strlen(des); j++)
    final[j] = des[j];
  //Copy the file name from *from file* name
  for(i; i<strlen(from); i++)
  {
    final[j] = from[i];
    j++;
  }
  //Return final pointer 
  return final;
}

/* Converts file name to directory
*/
char *fileDir(char *str)
{
  int i;
  int dirIndex;
  //Gets the index where first / is at fromt he end
  //Removes the / along with it.
  for(i = strlen(str) -1; str[i] != '/'; i--)
    dirIndex = i-1;
  //Create memory with dirIndex size
  char *final= (char*)malloc(dirIndex*sizeof(char));
  //Copy the character from string to final pointer
  for(i=0; i < dirIndex; i++)
    final[i] = str[i];
  //Return final pointer
  return final;
}



int main(int argc, char **argv)
{
  //Required variable to use stat functions
  struct stat buf;

  //Check for argument number
  if(argc != 3)
  {
    printf("Need two arguments!");
    return 1; //Argument error
  }
 
  //Assign the argument from the console
  char *from = argv[1];
  char *destination = argv[2];
  
  //Checks if the file exist for moving from
  if(stat(from, &buf) == -1)
  {
    printf("Input file not found\n");
    return 2;//Input file not found error
  }

  //Checks if the destination exists
  if(stat(destination,&buf) == -1)
  {
    //Checks if the file name is the same
    //if(nameCheck(from, destination) == 0)
    //{
      if((rename(argv[1], argv[2])) == -1)
      {
        printf("Destination not found\n");
        return 3;//Destination location not found error
      }
    //}
    //printf("Destination not found\n");
    //return 3;//Destination not found
  }
 
  else
  {
  //Check if fileDir was ran(requires to free up memory)
  int dirCheck = 0;
  //Uses destination file to check if is not directory and change to directory if it is
  if(!(S_ISDIR(buf.st_mode)))
  {
    destination = fileDir(destination); 
    dirCheck = 1;   
  }
  //Changes the destination name to have file name from *from file*
  char *final;
  final = dirFile(from, destination);
  //Links the files and check for link error
  if(link(from, final) == -1)
  {
    printf("Link error\n");
    return 4;//Link error
  }
  //Unlink the from *from file*
  if(unlink(from) == -1)
  {
    printf("Unlink error\n");
    return 5;//unlink error
  }
  
  //Free up memories used in the program
  if(dirCheck == 1)
    free(destination);
  free(final); 
  } 
  return 0;
}
