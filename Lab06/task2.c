#include <unistd.h> //read and write
#include <fcntl.h> //For flags for open
#include <stdio.h> //standard input and output
#include <stdlib.h>//Requires for the exit function
#include <utmp.h>

//Open the file utmp
int openUtmpFile()
{
	//Open the file
	int openFile;
	if((openFile = open("/var/run/utmp", O_RDONLY)) == -1)
	{
		perror("File open error!\n");
		exit(0);
	}
	return openFile;
}

int main()
{
	//Create struct
	struct utmp log[1];
	//Open the file
	int file;
	file = openUtmpFile();
	int nread;
	//Number of looged user
	int count = 0;

	//read the file
	while((nread = read(file, &log, sizeof(log))) > 0)
	{
		//print the user
		printf("User name = %s\n", log->ut_user);
		//count the number of looged user
		if(log->ut_type == 7)
			count++; 
	}
	printf("The number of logged in user = %d\n", count);


	return 0;
}
