#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{
	//Get the total size of arguments
	//Could have made a char with BUFSIZ
	//but there might be crazy person who write command
	//that is greater than 1024 char
	char *cmd;
	int i, argSize =0;
	for(i = 1; i<argc; i++)
		argSize += strlen(argv[i]);

	cmd = malloc(argSize*sizeof(char));
	//Concatenate all the arguments
	for(i = 1; i<argc; i++)
		sprintf(cmd, "%s %s", cmd, argv[i]);	

	//Popen pointer
	FILE *ptr;
	//Max buffersize
	char buf[BUFSIZ];
	//Open popen with read only
	if((ptr=popen(cmd, "r"))!=NULL)
	{
		//Gets the buf From the pipe
		while(fgets(buf, BUFSIZ, ptr) != NULL)
			//Write the command
			(void) printf("%s", buf);
	}
	//Close the pipe
	pclose(ptr);
	exit(0);
}
