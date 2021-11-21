#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void sigPress(int sig)
{}

int main()
{
	//Two signal mask for SIGINT and SIGQUIT
	sigset_t iMask, qMask;
	sigset_t orig_iMask, orig_qMask;
	//Clear signal sets
	sigemptyset(&iMask);
	sigemptyset(&qMask);
	//Assign SIGINT to iMask
	sigaddset(&iMask, SIGINT);
	//Assign SIGQUIT to qMask
	sigaddset(&qMask, SIGQUIT);

	//Block the signals
	if(sigprocmask(SIG_BLOCK, &iMask, &orig_iMask) < 0){
		perror("sigprocmask");
		exit(1);
	}
	if(sigprocmask(SIG_BLOCK, &qMask, &orig_qMask) < 0){
		perror("sigprocmask");
		exit(1);
	}
	int i;
	//Print and wait for a 1 second for 5 seconds
	for(i = 1; i <= 5; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	//Catch all the SIGQUIT that was pressed during the duration
	signal(SIGQUIT, &sigPress); 
	//unblock interrupt signal
	if(sigprocmask(SIG_SETMASK, &orig_qMask, NULL) < 0){
		perror("sigprocmask");
		exit(1);
	}
	//Set the signal back to default
	signal(SIGQUIT, SIG_DFL);
	//Wait 5 secons
	for(i = 1; i <= 5; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	printf("Program end");

exit(0);
}
