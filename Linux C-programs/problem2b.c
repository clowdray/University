/*
*  Problema2b.c   (threads)
*  Miquel Giné
*  
*  - service 1 : order meal
*  - service 2 : preparation time
*  - service 3 : total cost
*
*/

#include <stdio.h>      /* stderr, stdout, printf */
#include <unistd.h>     /* getpid */
#include <sys/wait.h>   /* wait */
#include <pthread.h>    /* thread */
#include <stdlib.h>     /* exit */

typedef enum {false, true} bool;

int arr[3];

int displayMenu()
{
	int inputMenu;

	printf("+------------------------------------------+\n");
	printf("|-----------ORDER-MACHINE--KIOSK-----------|\n");
	printf("+------------------------------------------+\n");
	printf("|                                          |\n");
	printf("|- 1 : Order customer meal  ---------------|\n");
	printf("|- 2 : Average time of preparation  -------|\n");
	printf("|- 3 : Total cost of the meal  ------------|\n");
	printf("|                                          |\n");
	printf("|- 0 : Exit menu  -------------------------|\n");
	printf("|                                          |\n");
	printf("+------------------------------------------+\n\n");
	printf("_- ");
	scanf("%d", &inputMenu);
	
	return inputMenu;
}

int displayEntrants()
{
	int inputChoice;

	printf("+------------------------------------------+\n");
	printf("|---------------ENTRANT--KIOSK-------------|\n");
	printf("+------------------------------------------+\n");
	printf("|                                          |\n");
	printf("|- 1 : Chrispy baked falafel  -------------|\n");
	printf("|- 2 : Peanut Slaw in soba Noodle  --------|\n");
	printf("|- 3 : Bio Hummus  ------------------------|\n");
	printf("|                                          |\n");
	printf("|- 0 : Exit menu  -------------------------|\n");
	printf("|                                          |\n");
	printf("+------------------------------------------+\n\n");
	printf("_- ");
	scanf("%d", &inputChoice);
	
	return inputChoice;
}

int displayMainDishes()
{
	int inputChoice;

	printf("+------------------------------------------+\n");
	printf("|------------MAIN-DISHES--KIOSK------------|\n");
	printf("+------------------------------------------+\n");
	printf("|                                          |\n");
	printf("|- 1 : Minimal Eggplant Lasagna  ----------|\n");
	printf("|- 2 : Spicy Veggie Tacos  ----------------|\n");
	printf("|- 3 : Plant Based XXL Burger  ------------|\n");
	printf("|                                          |\n");
	printf("|- 0 : Exit menu  -------------------------|\n");
	printf("|                                          |\n");
	printf("+------------------------------------------+\n\n");
	printf("_- ");
	scanf("%d", &inputChoice);
	
	return inputChoice;
}

int displayDrinks()
{
	int inputChoice;

	printf("+------------------------------------------+\n");
	printf("|---------------DRINKS--KIOSK--------------|\n");
	printf("+------------------------------------------+\n");
	printf("|                                          |\n");
	printf("|- 1 : Sparlinkg Water  -------------------|\n");
	printf("|- 2 : Macha Ice Tea  ---------------------|\n");
	printf("|- 3 : Bio Orange Juice  ------------------|\n");
	printf("|                                          |\n");
	printf("|- 0 : Exit menu  -------------------------|\n");
	printf("|                                          |\n");
	printf("+------------------------------------------+\n\n");
	printf("_- ");
	scanf("%d", &inputChoice);
	
	return inputChoice;
}

void errorOption(int type)
{
	switch (type)
	{
		case 1:
			printf("You must enter first at [ 1 : Order customer meal ]\n");
			break;
		default:
			printf("No valid option\n");		
	}
	
	printf("Press Any Key to Continue\n");  
	getchar();getchar();
	system("clear");
}

void *menuOP1()
{
	int Input1, Input2, Input3;

	displayEntrants:
		system("clear");
		Input1 = displayEntrants();
		if (Input1 == 0) { pthread_exit(NULL); }
		else if (Input1 > 3 || Input1 < 0) 
		{ 	errorOption(0); goto displayEntrants; }
	
	arr[0] = Input1;
						
	displayMainDishes:
		system("clear");
		Input2 = displayMainDishes();
		if (Input2 == 0) { pthread_exit(NULL); }					
		else if (Input2 > 3 || Input2 < 0) 
		{ 	errorOption(0); goto displayMainDishes; }
		
	arr[1] = Input2;
	
	displayDrinks:
		system("clear");
		Input3 = displayDrinks();						
		if (Input3 == 0) { pthread_exit(NULL); }
		else if (Input3 > 3 || Input3 < 0) 
		{ 	errorOption(0); goto displayDrinks; }
		
	arr[2] = Input3;
	
		
	pthread_exit(NULL);
}

void *menuOP2()
{
	double time1, time2, time3, total;

	if (arr[0] == 1) { time1 = 3.00; } 
	else if (arr[0] == 2) { time1 = 1.00; }
	else if (arr[0] == 3) { time1 = 2.00; }
	
	if (arr[1] == 1) { time2 = 3.00; } 
	else if (arr[1] == 2) { time2 = 4.00; }
	else if (arr[1] == 3) { time2 = 5.00; }
	
	if (arr[2] == 1) { time3 = 1.00; }
	else if (arr[2] == 2) { time3 = 1.00; }
	else if (arr[2] == 3) { time3 = 1.00; }
	
	total = time1 + time2 + time3;
	printf("Total cost of the meal: %.2f minutes\n", total);
	
	pthread_exit(NULL);
}

void *menuOP3()
{	
	double value1, value2, value3, total;
	
	if (arr[0] == 1) { value1 = 3.50; } 
	else if (arr[0] == 2) { value1 = 2.50; }
	else if (arr[0]  == 3) { value1 = 3.00; }

	if (arr[1]  == 1) { value2 = 4.00; } 
	else if (arr[1]  == 2) { value2 = 4.50; }
	else if (arr[1] == 3) { value2 = 5.00; }

	if (arr[2] == 1) { value3 = 1.00; }
	else if (arr[2] == 2) { value3 = 1.50; }
	else if (arr[2] == 3) { value3 = 2.50; }
							
	total = value1 + value2 + value3;
	printf("Total cost of the meal: %.2f €\n", total);
	
	pthread_exit(NULL);
}

/*-------------------------------------MAIN-----------------------------------------*/

int main(void)
{
	bool exitApp = false;
	bool validat = false;		
	
	pthread_t threads[3];
	
	do
	{	
		system("clear");	
		
		switch ( displayMenu() )
		{
			case 0:
				exitApp = true;
				break;
			case 1:				
				validat = true;
				pthread_create(&threads[0], NULL, menuOP1, NULL);
				pthread_join(threads[0], NULL);
				
				break;
			case 2:
				if (!validat) 
				{
					errorOption(1);
				}
				else 
				{	
					pthread_create(&threads[1], NULL, menuOP2, NULL);
					pthread_join(threads[1], NULL);
					sleep(3);
				}
				
				break;
			case 3:
				if (!validat) 
				{
					errorOption(1);
				}
				else 
				{	
					pthread_create(&threads[2], NULL, menuOP3, NULL);
					pthread_join(threads[2], NULL);
					sleep(3);
				}
				
				break;			
			default:
				errorOption(0);
		}
		
	} while (!exitApp);
}



