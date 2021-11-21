/** This program (signalset1.c) blocks SIGINT signal for 10 seconds using sigprocmask(2)* After that the signal is unblocked and  signal is handled.*/

#include<signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void hdl(intsig)
{
	printf("Got signal Cnt-C\n");
}

int main (int argc, char *argv[])
{
	sigset_t mask;
	sigset_t orig_mask;
	struct sigaction act;
	memset(&act, 0, sizeof(act)); //clear structure
	act.sa_handler= hdl; // set signal handler as hd1
	// set signlalhandler for SIGINT
	if(sigaction(SIGINT, &act, 0)) 
	{
		perror("sigaction");
		return 1;
	}
	sigemptyset(&mask); // clear signal set
	sigaddset(&mask, SIGINT); // add SIGINT
	// SIGINT is blocked
	if(sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) 
	{
		perror("sigprocmask");
		return 1;
	}
	int count =0;
	while(1)
	{ 
		if(count == 10)
		{
			printf("now unblocked\n");
			// SIGINT is unbloked
			if (sigprocmask(SIG_UNBLOCK, &mask, NULL) < 0) 
			{
				perror("sigprocmask");
				return 1;
			}
		}
		sleep(1);
		printf("running in cyle%d\n", ++count);
	}
	return 0;
}
