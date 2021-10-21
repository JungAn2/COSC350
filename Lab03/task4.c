#include <unistd.h> //library for file open read write
#include <fcntl.h> //library for the tags for open 

#define BUFFER_SIZE 1 //Buffer read size
int main(int argc, char **argv)
{
  int f_foo; // Store input foo file
  int f_foo1; // Store input foo2 file
  int f_foo12; // Store output foo12 file
  char buffer[BUFFER_SIZE]; // Buffer for char
  int nread; // Stores output from read system function
  
  if((f_foo = open("foo", O_RDONLY)) < 0)  // Opens foo file with read only
  {
    write(2, "Input file 'foo' Error!", 23);
    return 1; //Input 'foo' error
  }
  if((f_foo1 = open("foo1", O_RDONLY)) < 0) // Opens foo2 file with read only
  {
    write(2, "Input file 'foo1' Error!", 24);
    return 1; //Input 'foo1' error
  }
  umask(0000); // Resets permission
  if((f_foo12 = open("foo12", O_WRONLY | O_CREAT , 0760)) < 0) // Creates and open foo12 with write only and rwxrw----
  {
    write(2, "Output file 'foo12' Error!", 26);
    return 1; //Output 'foo12' Error) 
  }
  
  //End of the file
  int end = lseek(f_foo, 0, SEEK_END);
  //Current offset from the beginning of the file
  int offset = lseek(f_foo, 0, SEEK_SET);
  //Run until end of the file
  while( offset < end)
  {
    //Read in from the foo file and check for read error
    if((nread = read(f_foo, buffer, BUFFER_SIZE)) == -1)
    {
      write(2, "Read error!", 11);
      return 2; //Read Error
    }
    //Write to foo12 and check for write error
    if ((write(f_foo12, buffer, nread)) == -1)
    {
      write(2, "Write error!", 12);
      return 3; // Write error
    }
    //Increment offset
    offset++;
  }
  //Since foo file is done close the file
  close(f_foo);

  //End location for foo1 file
  end = lseek(f_foo1, 0, SEEK_END);
  //Current offset from beginning of the foo1 file
  offset = lseek(f_foo1, 0, SEEK_SET);  
  //Run until end of foo1 file
  while( offset < end)
  {
    //Read in file from foo1 and check for read error
    if((nread = read(f_foo1, buffer, BUFFER_SIZE)) == -1)
    {
      write(2, "Read error!", 11);
      return 2; //Read error
    }
    //Write too foo12 and check for read error
    if ((write(f_foo12, buffer, nread)) == -1)
    {
      write(2, "Write error!", 12);
      return 3; //write error
    }
    offset++;
  }
  //Close all files
  close(f_foo1);
  close(f_foo12);
                                                 
  return 0;
}
