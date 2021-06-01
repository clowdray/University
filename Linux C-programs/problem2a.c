/*
*  Problema2a.c    (process)
*  Miquel Giné
*  
*  - service 1 : order meal
*  - service 2 : preparation time
*  - service 3 : total cost
*
*/

#include <stdio.h>      /* stderr, stdout, printf */
#include <unistd.h>     /* fork */
#include <sys/wait.h>   /* wait */
#include <stdlib.h>     /* exit */

typedef enum {false, true} bool;

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

/*-------------------------------------MAIN-----------------------------------------*/

int main(void)
{
	bool exitApp = false;
	bool validat = false;;
	int menuInput1, menuInput2, menuInput3;
	double value1, value2, value3, total;
	double time1, time2, time3;
	pid_t pid;
	int status;
	int fd[2]; // creating array with 2 places for 2 fd'stdio
	// fd[0] is set to read file in the pipe
	// fd[1] is set to write file in the pipe
	pipe(fd);
	int arr[3];
	
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
								
				pid = fork();
				if (pid == 0){					
					close(fd[0]);
					
					displayEntrants:
						system("clear");
						menuInput1 = displayEntrants();						
						if (menuInput1 == 0) { exit(-1); }
						else if (menuInput1 > 3 || menuInput1 < 0) 
						{ 	errorOption(0); goto displayEntrants; }
					
					arr[0] = menuInput1;					
										
					displayMainDishes:
						system("clear");
						menuInput2 = displayMainDishes();						
						if (menuInput2 == 0) { exit(-1); }					
						else if (menuInput2 > 3 || menuInput2 < 0) 
						{ 	errorOption(0); goto displayMainDishes; }
					
					arr[1] = menuInput2;
					
					displayDrinks:
						system("clear");
						menuInput3 = displayDrinks();						
						if (menuInput3 == 0) { exit(-1); }
						else if (menuInput3 > 3 || menuInput3 < 0) 
						{ 	errorOption(0); goto displayDrinks; }
					
					arr[2] = menuInput3;
					write(fd[1],arr,sizeof(arr));
					
					exit(0);
				}
				else if (pid > 0)
				{
					int fpid = wait(&status);					
					printf("Console.log('Son [%d] ended with Status [%i]')\n", fpid, WEXITSTATUS(status));
					
					if (WEXITSTATUS(status) == 0 )
					{
						close(fd[1]);
						read(fd[0],arr,sizeof(arr));
					}
					else { validat = false; }
					
					sleep(2);										
				}
				
				break;
			case 2:
				pid = fork();
				if (pid == 0)
				{					
					if (!validat) 
					{
						errorOption(1);
						exit(-1);					
					}
					else 
					{	
						menuInput1 = arr[0];
						menuInput2 = arr[1];
						menuInput3 = arr[2];
									
						if (menuInput1 == 1) { time1 = 3.00; } 
						else if (menuInput1 == 2) { time1 = 1.00; }
						else if (menuInput1 == 3) { time1 = 2.00; }
						
						if (menuInput2 == 1) { time2 = 3.00; } 
						else if (menuInput2 == 2) { time2 = 4.00; }
						else if (menuInput2 == 3) { time2 = 5.00; }
						
						if (menuInput3 == 1) { time3 = 1.00; }
						else if (menuInput3 == 2) { time3 = 1.00; }
						else if (menuInput3 == 3) { time3 = 1.00; }
						
						total = time1 + time2 + time3;
						printf("Total cost of the meal: %.2f minutes\n", total);
						
						exit(0);
					}
				}
				else if (pid > 0)
				{			
					int fpid = wait(&status);
					printf("Console.log('Son [%d] ended with Status [%i]')\n", fpid, WEXITSTATUS(status));
					sleep(2);
				}
				
				break;
			case 3:
				pid = fork();
				if (pid == 0)
				{
					if (!validat) 
					{
						errorOption(1);
						exit(-1);
					}
					else 
					{
						menuInput1 = arr[0];
						menuInput2 = arr[1];
						menuInput3 = arr[2];
							
						if (menuInput1 == 1) { value1 = 3.50; } 
						else if (menuInput1 == 2) { value1 = 2.50; }
						else if (menuInput1 == 3) { value1 = 3.00; } 
					
						if (menuInput2 == 1) { value2 = 4.00; } 
						else if (menuInput2 == 2) { value2 = 4.50; }
						else if (menuInput2 == 3) { value2 = 5.00; }
					
						if (menuInput3 == 1) { value3 = 1.00; }
						else if (menuInput3 == 2) { value3 = 1.50; }
						else if (menuInput3 == 3) { value3 = 2.50; }						
												
						total = value1 + value2 + value3;
						printf("Total cost of the meal: %.2f €\n", total);
						
						exit(0);
					}
				}
				else if (pid > 0)
				{
					int fpid = wait(&status);					
					printf("Console.log('Son [%d] ended with Status [%i]')\n", fpid, WEXITSTATUS(status));
					sleep(2);
				}
				
				break;			
			default:
				errorOption(0);
		}
		
	} while (!exitApp);
}



