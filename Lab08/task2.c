#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4
int *arr;
int counter = 0;
//Thread 1
void *t1(void * arg)
{
	int test[20];
	int score, nread, i;
	char buffer[BUFSIZ];
	//Get test scores from keyboard upto 20
	printf("Enter a test score\n");
	while(counter < 20 && (nread=read(0, &buffer, BUFSIZ))>0)
	{
		sscanf(buffer, "%d", &score);
		test[counter]=score;
		counter++;
		printf("Enter a test score\n");
	}
	//Create memory for the array
	arr = (int*)malloc(counter*sizeof(int));
	//Assign the test score into arr pointer
	for(i = 0; i< counter; i++)
		arr[i] = test[i];
	//Return code
	pthread_exit(NULL);
}
void *t2(void *arg)
{
	int i, sum = 0;
	//Do the sum
	for(i = 0; i < counter; i++)
		sum += arr[i];
	//Get and print the sum
	printf("Average: %.2f\n", sum/(float)counter);
	float median;
	//Temp array to not disterb the array
	int *temp = (int*) malloc(counter*sizeof(int));
	for(i = 0; i< counter; i++)
		temp[i] = arr[i];
	//sort bubble sort
	int j, k;
	for(j = 0; j < counter; j++)
	{
		for(k = j+1; k < counter ; k++)
		{
			if(temp[k] < temp[j])
			{
				int t = temp[j];
				temp[j] = temp[k];
				temp[k] = t;
			}
		}
	}
	//If there is even number, do average of middle two
	if(counter%2 == 0)
		median = (float)(temp[(counter/2)-1]+temp[(counter/2)])/2;
	//Odd number is just middle
	else
		median = temp[(counter/2)];
	printf("Median: %.2f\n", median);
	free(temp);
	pthread_exit(NULL);
}
void *t3(void *arg)
{
	int i;
	//initialize min and max to first score
	int min = arr[0], max = arr[1];
	//Check for min and max
	for(i = 1; i < counter; i++)
	{
		if(min > arr[i])
			min=arr[i];
		if(max < arr[i])
			max=arr[i];
	}
	printf("Min: %d\nMax: %d\n", min, max);
	pthread_exit(NULL);
}
void *t4(void *arg)
{
	int i;
	//set all the arr score to 0
	for(i = 0; i< counter; i++)
	{
		arr[i] = 0;
		printf("%d ", arr[i]);
	}
	printf("\n");
	pthread_exit(NULL);
}

int main()
{
	//Number of threads
	pthread_t threads[NUM_THREADS];
	int rc, t = 0, waitt = 0;
	void *wait;
	//Create thread 1
	rc = pthread_create(&threads[t++], NULL, t1, NULL);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}
	//Wait for thread 1 to finish
	rc = pthread_join(threads[waitt++], &wait);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
		exit(1);
	}
	//Create thread 2
	rc = pthread_create(&threads[t++], NULL, t2, NULL);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}	
	//Create thread 3
	rc = pthread_create(&threads[t++], NULL, t3, NULL);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}
	//Wait for trhead 2 to finish
	rc = pthread_join(threads[waitt++], &wait);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
		exit(1);
	}
	//Wait for thread 3 to finish
	rc = pthread_join(threads[waitt++], &wait);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
		exit(1);
	}
	//Create thread 4
	rc = pthread_create(&threads[t++], NULL, t4, NULL);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}
	//Wait for thread 4 to finish
	rc = pthread_join(threads[waitt], &wait);
	if(rc!=0)
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
		exit(1);
	}
	pthread_exit(NULL);
	free(arr);
	return 0;	
}
