#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 5

//Factorial function
void *factorial(void *arg)
{
	//change the arg to num
	int n = atoi(arg);
	int i;
	int fact = 1;
	//Do the factorial
	for(i = 1; i <=n; i++)
		fact *= i;
	//Print out the factorial
	printf("Factorial: %d\n", fact);
	//Exit the thread
	pthread_exit(NULL);
}

//Sum function
void *sum(void *arg)
{
	//Change the arg to int
	int n = atoi(arg);
	int i;
	int sum = 0;
	//Do the sum
	for (i = 1; i <=n; i++)
		sum += i;
	//Print the sum
	printf("Sum: %d\n", sum);
	//Exit the thread
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	//Check to see if there is one arg
	if(argc != 2)
	{
		perror("Need one argument");
		exit(1);
	}
	//Create 2 threads
	pthread_t threads[NUM_THREADS];
	int rc, t = 0;
	//Create first thread with sum function
	rc = pthread_create(&threads[t++], NULL, sum, (void*)argv[1]);
	//Thread create error
	if(rc!=0)
	{
		printf("pthread Error: %d\n", rc);
		exit(1);
	}
	//Create secon thread with factorial function
	rc = pthread_create(&threads[t++], NULL, factorial, (void*)argv[1]);
	//Thread create error
	if(rc!=0)
	{
		printf("pthread Error: %d\n", rc);
		exit(1);
	}
	pthread_exit(NULL);
	exit(0);
}
