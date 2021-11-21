#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1
int main()
{
	//Process id variable
	pid_t pid;
	//Status from the child
	int status;
	//Opening the file. Need only one since the parent wait until child finishes
	int file;
	//Read buffer
	char buffer[BUFFER_SIZE];
	//Message to print from child and parent
	char *message;
	//Return value from read
	int nread;
	//Fork
	pid = fork();
	//Fork failed
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	//Child process
	else if(pid == 0)
	{
		//Reset permission
		umask(0000);
		//Open the file
		file = open("foo", O_WRONLY | O_CREAT, 0755);
		//Message
		message = "Hi, Mom\n";
		//Write the message
		write(file, message, strlen(message));
		//Close the file
		close(file);
	}
	//Parent process
	else
	{
		//Wait until child finishes
		wait(&status);
		//Puts the first message
		message = "My son said ";
		write(1, message, strlen(message));
		//Open up the file
		file = open("foo", O_RDONLY);
		//Read and write
		while((nread = read(file, buffer, BUFFER_SIZE))>0)
		{
			write(1, buffer, nread);
		}
		//Close the file
		close(file);
	}
	//Exit
	exit(0);
}
