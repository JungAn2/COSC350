#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define READ_END 0
#define WRITE_END 1

int main()
{
	int data_processed;
	int file_pipes[2], file_pipes2[2];
	char some_data[] = "Hi there, Kiddo";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));	

	//start Pipe for both pipe1 and 2
	if(pipe(file_pipes)<0){
		printf("Error pipe\n");
		exit (1);
	}
	if(pipe(file_pipes2)<0){
		printf("Error pipe2\n");
		exit (1);
	}
	//Start the fork
	fork_result = fork();
	if (fork_result == (pid_t)-1) {
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}

	if (fork_result == 0) {
		//Get all the pipes information and send it to the child
		//The char size does not need to be BUFSIZ but 
		char fp0[BUFSIZ+1], fp1[BUFSIZ+1], fp20[BUFSIZ+1], fp21[BUFSIZ+1];	
		
		//Set the last of the variables to be '\0'
		memset(fp0, '\0', sizeof(fp0));	
		memset(fp1, '\0', sizeof(fp1));	
		memset(fp20, '\0', sizeof(fp20));	
		memset(fp21, '\0', sizeof(fp21));		

		//Assign variable to corresponding pipe
		sprintf(fp0, "%d", file_pipes[READ_END]);
		sprintf(fp1, "%d", file_pipes[WRITE_END]);
		sprintf(fp20, "%d", file_pipes2[READ_END]);
		sprintf(fp21, "%d", file_pipes2[WRITE_END]);
		
		//Execute child file
		(void)execl("twoPipesChild", "twoPipesChild", fp0, fp1, fp20, fp21, (char *)0);

		exit(EXIT_FAILURE);
	}
	else {
		//Close read end for pipe 1 and close write for pipe2
		close(file_pipes[READ_END]);
		close(file_pipes2[WRITE_END]);
		data_processed = write(file_pipes[WRITE_END], some_data,
				strlen(some_data));
		printf("%d - wrote %d bytes\n", getpid(), data_processed);
		//Wait until child finishes process
		wait(&fork_result);			
		data_processed = read(file_pipes2[READ_END], buffer, BUFSIZ);
		printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
		//		}
}
exit(EXIT_SUCCESS);
}
