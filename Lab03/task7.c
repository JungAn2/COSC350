#include <fcntl.h> // flag library
#include <unistd.h> // read and write library
#include <stdio.h> //Input and output standard library

#define BUFFER_SIZE 1

// Function to convert string to integer
int stoi(char *str)
{
  int negative = 0; //acts as a boolean for negative number
  int integer = 0;//Return value
  int i=0;//for loop iterator

  //check for negative
  if(str[i] == '-')
  {
    negative = 1;
    i++;
  }

  //For loop for checks the string at the end of the string
  for(i; str[i] != '\0' ; i++)
  {
    //Checks the character is between 0 and 9
    if(str[i] >= '0' && str[i] <= '9')
    {
      //Add the character value * power to integer
      //-'0' converts string to number
      integer = (integer*10) + str[i]-'0';
    }
    //If it is not a number
    else
    {
      write(2, "Invalid number!\n", 16);
      return -1;//Number error
    }
  }
  // If negative return negative number
  if(negative==1)
    return -1*integer;
  //return non negative number
  return integer;  
}


int main(int argc, char** argv)
{
  //Check to see if there is a argument input
  if(argc == 1)
  {
    write(2, "Need an integer\n", 16);
    return 1; // argument error
  }

  int i; //for loop iterator
  int sum = 0; //Sum of the arguments
  
  //Go through each arguement and convert them to string and add them up
  for(i = 1; i <argc; i++)
  {
    //check if stoi failed to convert
    if(stoi(argv[i]) == -1)
      return 1;//string to integer error
    else
      //Add the values of the converted argument
      sum+=stoi(argv[i]);
  }

  //Print the message on console
  //Used a printf statement since write function cannot show variables
  printf("Sum: %d \n", sum);  

  return 0;
}
