#include <unistd.h>//Library function for system call function
#include <fcntl.h>//Library for flags
#include <ctype.h>
#include <stdio.h>//Standard library for input and output
#include <string.h>//Standard library for string

#define BUFFER_SIZE 1 //Buffer read size

/********************************
 Convert string to integer
 Params: str is string(character array) to be converted
 Returns: integer value of the string
********************************/
int stoi(char *str)
{
  //Holds integer value of the str
  int number = 0;
  //for loop iterator
  int i;
  //Run the for loop until end of string
  for (i = 0; str[i] != '\0'; i++)
  {
    //convert string to integer
    number = (number*10) + str[i] - '0';
  }
  //return integer value of string
  return number;
}

/********************************
 Convert integer to string
 Params: x is the int to be converted,
	 str is the string into which to write
 Returns: length of the string
********************************/
int convIntToStr(char * str, int x)
{
  sprintf(str, "%d", x);
  return (strlen(str));
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Need only one argument!\n");
    return 1; //Argument error
  }

  //Assign argument to f_iName
  char *f_iName = argv[1];
  //Holds value from input file
  int f_in;
  //Buffer for read
  char buffer[BUFFER_SIZE];
  //Holds value from read
  int nread;
  //Holds only the number from the input read
  char number[81];
  int charCounter = 0;
  //Holds the number from the string
  int sum = 0;
  
  //Open read file and check for error
  if((f_in = open(f_iName, O_RDONLY)) == -1)
  {
    write(2, "Open error!\n", 12);
    return 2; //Open error
  }
  
  //Holds current offset
  int i; 
  //Max number of character in single line
  const int MAX_CHAR = 80;
  //Find the offset to end of the file
  int end = lseek(f_in, 0, SEEK_END);
  //Set the current to the beginning of the file
  lseek(f_in, 0, SEEK_SET);
  
  //Checks for three conditions
  //1) within 80 characters
  //2) in a single line
  //3) not end of the file
  //End when one of those condition fails
  int boolean = 0;
  for(i = 0; i < MAX_CHAR && i < end && boolean == 0; i++)
  {
    if((nread = read(f_in, buffer, BUFFER_SIZE)) == -1)
    {
      write(2, "Read error!\n", 12);
      return 3; //Read error
    }
    //Check to see if the read buffer is a number character
    if(buffer[0] >= '0' && buffer[0] <= '9')
    {
      number[charCounter]= buffer[0];
      charCounter++;
    }
    if(buffer[0] == '\n')
      boolean = 1;
  }
  
  //Check if the string is empty
  //Meaning there is no number in the file
  if(number[0] == '\0')
  {
    printf("No number in the line\n");
    return 0;//No Number successful run end
  }
  
  //End the string after inputting the number
  number[charCounter++] = '\0';
  
  //Turn the string into number  
  sum = stoi(number);
  sum += 10; 
  //Convert integer to string
  int strLength = convIntToStr(number, sum);
  
  //Write to the screen
  write(1, "Sum: ", 4);
  write(1, number, strLength);
  write(1, "\n", 1); 
  //Successful program run exit
  return 0;
}
