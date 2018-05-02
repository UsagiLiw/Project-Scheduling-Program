/***************************************************
	Project: Project Scheduling
	This program aims to help the user to manage
	the task and work within the group or individual

	By 	-Bhimapaka Thapanangkun 
		60070503447
		-Nutchanon Veraphichkasem
		60070503422
		-Nonthakorn Sukprom 
		60070503435
		-Thanapat Sakaekhao
		60070503430
****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fileLoader.h"
#include "projectInfo.h"

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
	int returnValue = 0;
	PROJECTLIST_T * pHead = NULL;

	out = 1;	

	switch(choice)
	{
		case 1:	/*Create new project*/
			printf("Create new project\n");
			printf("\tNot yet implemented\n\n");
			return 1;
			break;
		case 2: /*Load existing project*/
			printf("Load existing project\n");
			projectNameList();
			if(out == 1)
			{
				readProject(thisProject);
			}
			return 1;
			break;
		case 3: /*Open readme file*/
			printf("Open readme file\n");
			printf("\tNot yet implemented\n\n");
			return 1;
			break;
		case 4: /*Exit the program*/
			return 0;
			break;
		default:
			printf("Error - Please choose the existed options\n\n");
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
	while(status != 0)
	{
		printf("Please choose the options below :\n");
		choices();
		printf("Choose: ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choice);
		printf("\n");
		status = loadFunction(choice);
	}
	printf("Goodbye!\n");
	return 0;
}
