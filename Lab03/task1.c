#include <unistd.h>

#define BUFFER_SIZE 1
int main()
{
  int buffer[BUFFER_SIZE];//Buffer
  int nread;//Value from read function
  
  //Read in to the buffer
  while((nread = read(0, buffer, BUFFER_SIZE) > 0))
  {
    //Write as well as check for write error
    if(write(1, buffer, nread) != nread)
    {
      write(2, "Write Error!", 12);
      return 1; // Write error
    }
  }
  
  //Checks for read error
  if(nread == -1)
  {
    write(2, "Read Error!", 11);
    return 2; //Read error
  } 
  return 0;
}
