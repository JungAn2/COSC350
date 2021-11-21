#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1
int main(int argc, char ** argv)
{
	//Check for number of argument
	if(argc != 2)
	{
		perror("Need 1 argument");
		exit(1);
	}
	//Get the file name
	char *f_Name = argv[1];
	//File descriptor
	int f_in, f_out;
	//Buffer to read
	char buffer[BUFFER_SIZE];
	int nread;
	//pid value(parent child)
	pid_t pid;

	//Open the file
	f_in = open(f_Name, O_RDONLY);
	//Get the end
	int end = lseek(f_in, 0, SEEK_END);
	int offset = 0;
	int curr = 0;
	//Reset permission
	umask(0000);

	//Fork
	pid = fork();
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}

	//child
	else if(pid == 0)
	{
		remove("child.txt");
		//Open up child file
		f_out = open("child.txt", O_WRONLY | O_CREAT, 0755);
		//read and write until end of the file
		while(end > offset){ 
			lseek(f_in, offset, SEEK_SET);
			if((nread = read(f_in, buffer, BUFFER_SIZE))<0)
			{
				perror("Read error");
				exit(1);
			}
			if(buffer[0] < '0' || buffer[0] > '9')
			{
				if((write(f_out, buffer, nread))==-1)
				{
					perror("Write error");
					exit(1);

				}
			}
			offset++;

		}
	}
	//parent
	else
	{
		remove("parent.txt");
		//Open up parent file
		f_out = open("parent.txt", O_WRONLY | O_CREAT, 0755); 
		//Read and write until end of the file
		while(end > offset){
			lseek(f_in, offset, SEEK_SET);
			if((nread = read(f_in, buffer, BUFFER_SIZE))<0)
			{
				perror("Read error");
				exit(0);
			}
			if(buffer[0] >= '0' && buffer[0] <= '9' || buffer[0] == '\n')
			{
				if((write(f_out, buffer, nread))==-1)
				{
					perror("Write error");
					exit(0);
				} 
			}
			offset++;
		}
	} 
	if(pid != 0) {
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if (WIFEXITED (stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}
	exit(0);
}
