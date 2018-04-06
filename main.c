#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void choices()
{
	printf("\t1.Create new project\n");
	printf("\t2.Load existing project\n");
	printf("\t3.Readme\n");
	printf("\t4.Exit program\n");
}

int loadFunction(int choice)
{
	char stringInput[32];

	switch(choice)
	{
		case 1:	/*Create new project*/
			printf("Create new project\n");
			printf("\tNot yet implemented\n");
			return 1;
			break;
		case 2: /*Load existing project*/
			printf("Load existing project\n");
			printf("\tNot yet implemented\n");
			return 1;
			break;
		case 3: /*Open readme file*/
			printf("Open readme file\n");
			printf("\tNot yet implemented\n");
			return 1;
			break;
		case 4: /*Exit the program*/
			return 2;
			break;
		default:
			printf("Error - Please choose the exist option\n");
			return 1;
			break;
	}
	
}

int main()
{
	char stringInput[128];
	int choice = 0;
	int status = 1;
	printf("Welcome to Project Schedule Program\n");
	while(status == 1)
	{
		printf("Please choose the options below :\n");
		choices();
		printf("Choose: ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choice);
		status = loadFunction(choice);
	}
	printf("Goodbye!\n");
	return 0;
}
