//alarm.c
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

// signal handler for SIGALRM
void ding(int sig){
	alarm_fired = 1;
}

int main()
{
	//Variable to hold process ID
	pid_t pid;
	//Struct for sigaction
	struct sigaction act;
	//Set the structure handler to ding function 
	act.sa_handler = ding;
	printf("alarm applicaction starting\n");

	//Fork
	pid = fork();
	switch (pid){
		case -1: /*failure*/
			perror("fork failed");
			exit(1);
		case 0: /*child*/
			sleep(5);
			kill(getppid(), SIGALRM);
			_exit(0);
	}

	/* if we get here we are the parent process */
	printf("waiting for alarm to go off\n");
	sigaction(SIGALRM, &act, 0);
	pause();
	if(alarm_fired)
		printf("Ding!\n");

	printf("done\n");
	exit(0); 
}
