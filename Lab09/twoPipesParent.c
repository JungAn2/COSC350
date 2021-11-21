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

	if((pipe(file_pipes) == 0) && (pipe(file_pipes2) == 0)){

		fork_result = fork();
		if (fork_result == (pid_t)-1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}

		if (fork_result == 0) {
			char fp0[BUFSIZ+1], fp1[BUFSIZ+1], fp20[BUFSIZ+1], fp21[BUFSIZ+1];
			memset(fp0, '\0', sizeof(buffer));
			memset(fp1, '\0', sizeof(buffer));
			memset(fp20, '\0', sizeof(buffer));
			memset(fp21, '\0', sizeof(buffer));	
			sprintf(fp0, "%d", file_pipes[READ_END]);
			sprintf(fp1, "%d", file_pipes[WRITE_END]);
			sprintf(fp20, "%d", file_pipes[READ_END]);
			sprintf(fp21, "%d", file_pipes[WRITE_END]);
			(void)execl("twoPipesChild", "twoPipesChild", fp0, fp1, fp20, fp21, (char *)0);
			
			exit(EXIT_FAILURE);
		}
		else {
			close(file_pipes[READ_END]);
			close(file_pipes2[WRITE_END]);
			data_processed = write(file_pipes[WRITE_END], some_data,
						strlen(some_data));
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
			wait(NULL);			
			data_processed = read(file_pipes2[READ_END], buffer, BUFSIZ);
			printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
		}
}
	exit(EXIT_SUCCESS);
}
