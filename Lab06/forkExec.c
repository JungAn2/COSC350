// fork1.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	//Need 4 argument
	if(argc != 5) {
		perror("Need 4 arguements!\n");
		exit(1);
	}
	//Arguments
	int Np = atoi(argv[2]);
	int Tp = atoi(argv[4]);

	pid_t pid, pidc, pidp;
	char message[50];
	int n, s;
	int exit_code;

	printf("fork program starting\n");
	//Start fork
	pid = vfork();
	switch(pid) {
		//Fail case
		case -1:
			perror("fork failed");
			exit(1);
		//Child case
		case 0:
			//gets child pid
			pidc = getpid();
			//Copy the message to message
			sprintf(message, "This is the child with pid = %d", pidc);
			//Execute the file
			if(execl("/mnt/linuxlab/home/ja67671/COSC350/Lab06/child", message, argv[1], argv[3], (char *)0) < 0)
			{
				perror("exec error\n");
				exit(1);
			}
			break;
		//Parent case
		default:
			pidp = getpid();
			//Copy the message
			sprintf(message, "This is the parent with pid = %d", pidp);
			n = Np;
			s = Tp;
			exit_code = 0;
			//Puts the message on the screen and sleep
			for(; n > 0; n--){
				puts(message);
				sleep(s);
			}
			break;
	}
	//if parent
	if(pid != 0) {
		int stat_val;
		pid_t child_pid;
		//Get child status
		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if (WIFEXITED (stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}
	exit(exit_code);
}
