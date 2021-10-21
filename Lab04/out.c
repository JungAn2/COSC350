#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1
int main(int argc, char** argv)
{
  //Check to see if there is less than two argument
  if(argc<3)
  {
    printf("Need to pass in two file names.\n");
    return 1; //Error input file number
  }
  //Check to see if there are more than two argument
  else if(argc > 3)
  {
    printf("You have pass in more than two files.\n");
    return 1; //Error input file number
  }

  int f_in, f_out; //Holds value for input and output file
  char buffer[BUFFER_SIZE]; // buffer for read function
  int nread; //Hold read function value

  //Open input file from first argument
  if((f_in = open(argv[1], O_RDONLY)) == -1)
  {
    printf("Open error for %s \n", argv[1]);
    return 2; //File open error
  }

  umask(0000);//Reset mode
  //Open output file from second argument
  if((f_out = open(argv[2], O_WRONLY | O_CREAT, 0666)) == -1)
  {
    printf("Open error for %s \n", argv[2]);
    return 2; //File open error
  }

  //Holds converted ascii number
  int ascii;
  //ASCII number has 4 character
  char buffer2[4];
  //Read in the file
  while ((nread = read(f_in, buffer, BUFFER_SIZE)) > 0)
  {
    //Converts character into number
    //Uses '\0' since it is 0 in ascii
    //compared to '0' which is 48
    ascii = *buffer - '\0';

    //for loop iterator
    int i;
    //Need to create character array to use write system function
    //The for loop is fliped to get the smallest value to the end
    for (i = 3; i > 0; i--)
    {
      buffer2[i] = (ascii%10) + '0';
      ascii = ascii /10;
    }
    //Add a space in the beginning of the buffer to make the ascii code to look nice
    buffer2[0] = ' ';
    //Check for write error
    if((write(f_out, buffer2, 4)) == -1)
    {
      write(2, "Write error!", 12);
      close(f_in);
      close(f_out);
      return 3; //Write error
    }
  }
  
  //Check for read error
  if (nread == -1)
  {
    write(2, "Read error!", 11);
    close(f_in);
    close(f_out);
    return 4; //Read error
  }
  
  //Close the files
  close (f_in);
  close (f_out);
  return 0;
}
