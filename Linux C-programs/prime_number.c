/*
*  prime_number.c  (Problem 3a)
*  Miquel Giné
*  
*  - Num 1 : initial number of range
*  - Num 2 : final number of range
*  - Divide whole range with number of threads to 
*      make every thread work on the same amount.
*
*  - Possibile improve of this code is, If thread has already finished
*      take data from other thread to make the maximum of threads working
*      and balance the weight of work.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NUM1    1
#define NUM2    10000000
#define NUMOFTHREADS    10

double time_spec_seconds(struct timespec* ts) 
{
	return (double) ts->tv_sec + (double) ts->tv_nsec * 1.0e-9;
}

void *PrimeThreadCalculation(void *threadid) 
{
	printf("Initialize %ld \n", pthread_self());
	
	clockid_t threadClockId;
	struct timespec tstart = {0,0}, tend = {0,0};

	pthread_getcpuclockid(pthread_self(), &threadClockId);
	clock_gettime(threadClockId, &tstart);
	

	static int cnt=0; //cnt=count
	int number1 = NUM1+(NUM2-NUM1)*cnt/NUMOFTHREADS;
	int number2 = NUM1+(NUM2-NUM1)*(cnt+1)/NUMOFTHREADS;
	cnt+=1;
	int isPrime, i;

	/* Calculations */
	while (number1 <= number2) {
		/* Assume isPrime is true */
		isPrime = 1;

		for (i = 2; i < number1 && isPrime; i++) {
			if (number1 % i == 0) {
				isPrime = 0;
			}
		}
		if (isPrime == 1) {
			printf("Thread[%ld] .:  %d\n", pthread_self(), number1);
		}
		number1++;
	}
	printf("\n");
	
	clock_gettime(threadClockId, &tend);
	
	double delta = time_spec_seconds(&tend) - time_spec_seconds(&tstart);
	printf("Thread[%ld], computation took %lf seconds.\n\n", pthread_self(), delta);
}

int main()
{
	/* Create threads */
	pthread_t threads[NUMOFTHREADS];
	int rc;
	long t;
	
	for (t = 0; t < NUMOFTHREADS; t++) {
		/* Creates threads */
		rc = pthread_create(&threads[t], NULL, PrimeThreadCalculation, (void *)t);
		
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d \n", rc);
			exit(-1);
		}
	}
    
	for (t = 0; t < NUMOFTHREADS; t++) {
		pthread_join(threads[t],NULL);
	}
	
	printf("All threads have Finalized.");
    
	/* Exits the threads */
	pthread_exit(NULL);
	return 0;
}



