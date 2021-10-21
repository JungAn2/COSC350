#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1
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

  int f_in; //stores file input data
  int f_out; //store file output data
  char buffer[BUFFER_SIZE]; //buffer
  int nread; //stores output from read system call function
  int offset; //Offset for char location from end


  if((f_in = open(f_iName, O_RDONLY)) < 0) //Open input file
  {
    write(2, "Input file Open Error!", 22);
    return 1; //File open error
  }
  umask(0000); //Reset permission
  if((f_out = open(f_oName, O_WRONLY | O_CREAT , 0760)) < 0)//Create and open file foorev with write only and rwxrw----
  {
    write(2, "Output file Open Error!", 23);
    return 1; //File open error
  }

  //Get the end of the file
  offset = lseek(f_in, 0, SEEK_END);

  //While the current location is not at the beginning  
  while(offset >= 0)
  {
    //Read in from foo and check for read error
    if((nread = read(f_in, buffer, BUFFER_SIZE)) == -1)
    {
      write(2, "Read Error!", 11);
      return 2; // Read Error
    }
    
    //Write to foorev and check for write error
    if((write(f_out, buffer, nread)) != nread)
    {
      write(2, "Read Error!", 11);
      return 2; //Read Error
    }
    //Go back two space before the current.
    //Since the program read a buffer, it moved one
    //and to go back to previous character
    //you have to move twice back
    offset = lseek(f_in, -2, SEEK_CUR);
  }
  //Close the files
  close(f_in);
  close(f_out);
  
  return 0;
}
