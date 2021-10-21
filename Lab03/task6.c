#include <unistd.h> //Library for read and write system function
#include <fcntl.h> // Library for flags

#define BUFFER_SIZE 1 //Buffer size
int main(int argc, char **argv)
{
  //Holds file name
  char *f_iName;
  char *f_oName;
  //Checks if there is two argument and assign them to variable
  if(argc == 3)
  {
    f_iName = argv[1];
    f_oName = argv[2];
  }
  //Checks to see if there is one argument and assign input name
  else if(argc ==2)
  {
    f_iName = argv[1];
    f_oName = "foorev";
  }
  //If there is not a argument assign foo and clone1 to the files
  else if (argc == 1)
  {
    f_iName = "foo";
    f_oName = "foorev";
  }
  //Check for invalid number of argument
  else
  {
    write(2, "Invalid argument!\n", 18);
    return 1; //Invalid argument exit
  }
                                                                    
  int f_in, f_out; //Holds input and output file
  char buffer[BUFFER_SIZE]; //Buffer of characters
  int nread; 
  int offset=0, end=0; //Offset for read and end of the file

  // Open file foo and check for error opening
  if((f_in = open(f_iName, O_RDONLY)) < 0)
  {
    write(2, "Input file open error!", 22);
    return 1; //File open error
  }

  umask(0000); // Reset mode of file
  // Open and create file foorev and check for error opening
  if((f_out = open(f_oName, O_WRONLY | O_CREAT, 0760)) < 0)
  {
    write(2, "Output file open error!", 23);
    return 1; //File open error
  }
  
  
  //Find the end of the file
  while((nread = pread(f_in, &buffer, BUFFER_SIZE, end)) > 0)
  {
    end++;
  }
  
  //reduce one end size since end is one character after the last character 
  end--;

  //Checks for read error
  if (nread == -1)
  {
    write(2, "Read error!", 11);
    return 2; //Read error
  }

  //Read the input file again and write in reverse
  while((nread = pread(f_in, &buffer, BUFFER_SIZE, offset)) >0)
  {
    if((pwrite(f_out, &buffer, BUFFER_SIZE, end-offset)) == -1)
    {
      write(2, "Write error!", 12);
      return 3; //Write error
    }
    offset++;
  } 

  //Close both input and output file
  close(f_in);
  close(f_out);
  return 0;
}
