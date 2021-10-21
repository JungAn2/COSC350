#include <unistd.h> //library for file open read write
#include <fcntl.h> //library for the tags for open 

#define BUFFER_SIZE 32 //Buffer read size

int main(int argc, char **argv)
{
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
    f_oName = "clone2";
  }
  //If there is not a argument assign foo and clone1 to the files
  else if (argc == 1)
  {
    f_iName = "foo";
    f_oName = "clone2";
  }
  //Check for invalid number of argument
  else
  {
    write(2, "Invalid argument!\n", 18);
    return 1; //Invalid argument exit
  }
  int f_in; // stores for files in
  int f_out; // stores for files out
  char buffer[BUFFER_SIZE]; // character array
  int nread; // stores output of read system call function

  if((f_in = open(f_iName, O_RDONLY)) < 0){ //Opens the file called "foo" and store in to f_in
    write(2, "Input file error!", 17);
    return 1;//File in error exit
  }
  umask(0000); // resets file mode
  if((f_out = open(f_oName, O_WRONLY | O_CREAT ,0760)) < 0){ //Creates and open the file clones1 for write only with permission rwxrwx---
    write(2, "Output file error!", 18);
    return 2;//File out error exit
  } 
  // Read the file until there is not a character to read
  while ((nread = read(f_in, buffer, BUFFER_SIZE)) > 0)
  {
    //Error occurence during write
    if(((write(f_out, buffer, nread)) != nread)){
      write(2, "Write Error!", 12);
      return 3; //Write Error
    }
  }
  //Error occurence during read
  if (nread == -1){
    write(2, "Read Error!", 11);
    return 4; //Read Error
  } 

  //Closes both in file and out file
  close(f_in);
  close(f_out);
  
  return 0;
}
  
