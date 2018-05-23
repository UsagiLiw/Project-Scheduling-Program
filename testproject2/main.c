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

#include "fileLoader.h"
#include "projectInfo.h"
#include "abstractNetwork.h"
#include "loadFunctions.h"

void choices()
{
	printf("\t1.Create new project\n");
	printf("\t2.Load existing project\n");
	printf("\t3.Readme\n");
	printf("\t4.Exit program\n");
}

/*	Depends on the choice of the user
	The function will bring the user to 
	different functions for further operation
	Argument: choice - the number that the user chooses
	Return: 1 - if the user still wants to continue
			0 - if the user wants to exit the program
*/
int loadFunction(int choice)
{
	char stringInput[32];

	out = 1;	

	switch(choice)
	{
		case 1:	/*Create new project*/
			printf("Create new project\n\n");
			memset(thisProject,0,sizeof(thisProject));
			NUMBEROFTASK = 0;
			memCount = 0;
			newProject();
			addDependency();
			printProjectInfo();
			printCriticalPath();
			saveEdit();
			printf("\tSuccessfully create project: %s\n\n",thisProject);
			clearGraph();
			return 1;
			break;
		case 2: /*Load existing project and choose the actions*/
			printf("Load existing project\n");
			memset(thisProject,0,sizeof(thisProject));
			NUMBEROFTASK = 0;
			projectNameList();
			if(chooseProject() != 0)
			{
				printProjectInfo();
				printCriticalPath();
				displayOptions();
			}
			clearGraph();
			return 1;
			break;
		case 3: /*Open readme file*/
			printf("Open readme file\n");
			printf("\tNot yet implemented\n\n");
			return 1;
			break;
		case 4: /*Exit the program*/
			clearGraph();
			return 0;
			break;
		default:
			printf("Error - Please choose the existing options\n\n");
			return 1;
			break;
	}
	choice = 0;
}

int main()
{
	char stringInput[128];
	int choice = 0;
	int status = 1;
	printf("Welcome to Project Schedule Program\n");
	while(status != 0)
	{
		status = 1;
		choice = 0;
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
