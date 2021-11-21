#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sigPrint(int sig)
{
	if(sig == SIGUSR1)
		printf("Hi Honey! Anything wrong?\n");
	else if(sig == SIGUSR2)
		printf("Do you make trouble again?\n");
}

int main()
{
	//Process id variable
	pid_t pid;

	pid = fork();
	//Fork fail
	if(pid == -1)
	{
		perror("Fork error");
		exit(1);
	}
	//Child process
	else if(pid == 0)
	{	
		kill(getppid(), SIGUSR1);
	}
	//Parent process
	else
	{
		pid_t pid2;
		pid2 = fork();
		//Fork fail
		if(pid2 == -1)
		{
			perror("Fork error");
			exit(1);
		}
		//Child 2
		else if(pid2 == 0)
		{
			//wait until first child dies
			//waitpid(pid, NULL,  0);	
			kill(getppid(), SIGUSR2);
		}
		//Parent
		else
		{
			signal(SIGUSR1, sigPrint);
			pause();		
			signal(SIGUSR2, sigPrint);
			pause();		
		}
	}

  exit(0);
}
