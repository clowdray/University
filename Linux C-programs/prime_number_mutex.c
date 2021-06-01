/*
*  prime_number_mutex.c  (Problem 3b)
*  Miquel Giné
*  
*  - Num 1 : initial number of range
*  - Num 2 : final number of range
*  - Divide whole range with number of threads to 
*      make every thread work on the same amount.
*  - Save values into a global variable, using mutex
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

/*----------------------------ARRAY-METHODS---------------------------------*/

typedef struct 
{
	int *array;
	size_t used;
	size_t size;
} Array;

void initArray(Array *a, size_t initialSize)
{
  	a->array = malloc(initialSize * sizeof(int));
  	a->used = 0;
  	a->size = initialSize;
}

void insertArray(Array *a, int element) 
{	  
	if (a->used == a->size) 
	{
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(int));
	}
	
	a->array[a->used++] = element;
}

void freeArray(Array *a) 
{
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

void quicksort(Array *a, int first, int last)
{
	int pivot,j,temp,i;

	if(first<last)
	{
		pivot=first;
		i=first;
		j=last;

		while(i<j)
		{
			while(a->array[i]<=a->array[pivot]&&i<last) i++;
			while(a->array[j]>a->array[pivot]) j--;

			if(i<j)
			{
				temp=a->array[i];
				a->array[i]=a->array[j];
				a->array[j]=temp;
			}
		}

		temp=a->array[pivot];
		a->array[pivot]=a->array[j];
		a->array[j]=temp;

		quicksort(a,first,j-1);
		quicksort(a,j+1,last);
	}
}

/*------------------------------END-METHODS---------------------------------*/

pthread_t threads[NUMOFTHREADS];
pthread_mutex_t mutexprime;
Array a;

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
		
			pthread_mutex_lock (&mutexprime);
			
			insertArray(&a, number1);
			
			pthread_mutex_unlock (&mutexprime);
		}
		number1++;
	}
	printf("\n");
	
	clock_gettime(threadClockId, &tend);
	
	double delta = time_spec_seconds(&tend) - time_spec_seconds(&tstart);
	printf("Thread[%ld], computation took %lf seconds.\n\n", pthread_self(), delta);
	
	pthread_exit((void*) 0);
}

int main()
{
	/* Create threads */	
	int rc;
	long t;
	
	initArray(&a, 1); //initialize 1 element
	
	pthread_mutex_init(&mutexprime, NULL);
	
	for (t = 0; t < NUMOFTHREADS; t++) 
	{
		/* Creates threads */
		rc = pthread_create(&threads[t], NULL, PrimeThreadCalculation, (void *)t);
		
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d \n", rc);
			exit(-1);
		}
	}
    
	for (t = 0; t < NUMOFTHREADS; t++) 
	{
		pthread_join(threads[t],NULL);
	}
	
	printf("All threads have Finalized. \n");
	
	quicksort(&a, 0, a.used);
	
	for (int i = 0; i<a.used; i++)
	{
		printf("%d\n", a.array[i]);
	}
	
	/* Free array space */
	freeArray(&a);
	/* Destroy the mutex */
	pthread_mutex_destroy(&mutexprime);
	/* Exits the threads */
	pthread_exit(NULL);
	return 0;
}