#include <unistd.h>//library for read and write system call function
#include <fcntl.h>//library for flags

#define BUFFER_SIZE 1 //Buffer size for read function
int main(int argc, char **argv)
{
  //Check for if there is more than 2 argument
  if(argc >3)
  {
    write(2, "Too many argument!\n",21);
    return 1; // argument error
  }
  //Check for if there is less than 2 argument
  if(argc < 3)
  {
    write(2, "Need two argument!\n", 21);
    return 1; // argument error
  }

  //Holds name of the file for input and output file
  char *f_iName = argv[1];
  char *f_oName = argv[2];
  //Holds the value of open file for input and output
  int f_in, f_out;
  //Buffer for the reading the file
  char buffer[BUFFER_SIZE];
  //Holds read value
  int nread;
  //counts for number of character read
  int counter = 0;
  //Holds 3 size char to store the ascii number
  char buffer2[3];

  //Open input file and check for error
  if((f_in = open(f_iName, O_RDONLY)) == -1)
  {
    write(2, "Open input error!\n", 18);
    return 2; //open file error 
  }
  //Reset file mode
  umask(0000);
  //Open output file and check for error
  if((f_out = open(f_oName, O_WRONLY | O_CREAT, 0666)) == -1)
  {
    write(2, "Open output error!\n", 19);
    return 2; //open file error
  }  
  
  //Read the file from input
  while((nread = read(f_in, buffer, BUFFER_SIZE)) > 0)
  {
    //skip empty character
    if(buffer[0] != ' ')
    {
      //Add buffer character to buffer2
      buffer2[counter] = buffer[0];
      //increment counter
      counter++;
    }
    //If counter reaches max buffer2 size
    if(counter > 2)
    {
      //final ascii character
      char ascii[1];
      //holds asciiNumber
      int asciiNum=0;
      //for loop iterator
      int i;

      //string to int
      //Does not need to check if it's a number since
      //the file that is being open only contains
      //ascii numbers
      for(i = 0; i < 3; i++)
      {
        asciiNum = (asciiNum * 10) + buffer2[i] - '0';
      }
      //convert int to ascii code
      ascii[0] = asciiNum + '\0';    
     
      //Write the ascii code to output file and check for write error
      if((write(f_out, ascii, 1)) == -1)
      {
	write(2, "Write error!\n", 13);
        return 3;
      }
      //Reset counter
      counter = 0;
    }
  }

  //Close both input and output file
  close(f_in);
  close(f_out);
  //Successful program run exit
  return 0;
}
