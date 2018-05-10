/****************************************
	createProject.c

	This file contains function for creating
	a new project

	By: Bhimapaka Thapanangkun
	ID: 60070503447
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abstractGraph.h"
#include "loadFunctions.h"
#include "projectInfo.h"

void enterTaskMember(char * tempNameString)
{
	char tempName[128];
	char stringInput[128];
	char comma[] = ",";
	int memCount = 0;

	while(1)
	{
		printf("Enter responsible member name NO.%d [Press RETURN when done]: ",memCount+1);
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(memCount <= 0)
			{
				printf("Must have at least one responsible member\n");
				continue;
			}
			else
				break;
		}
		sscanf(stringInput,"%s",tempName);
		strcat(tempNameString,tempName);
		strcat(tempNameString,comma);
		memCount++;
	}
}

void enterProjectMember(char * tempNameString)
{
	char tempName[128];
	char stringInput[128];
	char comma[] = ",";
	int memCount = 0;
	char projectNameString[1000];

	while(1)
	{
		printf("Enter member name NO.%d [Press RETURN when done]: ",memCount+1);
		memset(stringInput,0,sizeof(stringInput));
		memset(tempName,0,sizeof(tempName));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(memCount <= 0)
			{
				printf("Must have at least one member\n");
				continue;
			}
			else
				break;
		}
		sscanf(stringInput,"%s",tempName);
		strcat(tempNameString,tempName);
		strcat(tempNameString,comma);	
		memCount++;
	}
}

void newProject()
{
	char stringInput[1000];
	char tempName[100];
	char tempNameString[1000];
	char projectNameString[1000];
	int memCount = 0;
	char comma[] = ",";
	TASK_T * pCurrent = NULL;

	NUMBEROFTASK = 0;
	printf("Enter the project name: ");
	memset(stringInput,0,sizeof(stringInput));	
	fgets(stringInput,sizeof(stringInput),stdin);
	sscanf(stringInput,"%s",CHOSENPROJECT.projectName);
	printf("Description of the project: \n");
	memset(stringInput,0,sizeof(stringInput));	
	fgets(stringInput,sizeof(stringInput),stdin);
	sscanf(stringInput,"%s",CHOSENPROJECT.description);
	memset(tempNameString,0,sizeof(tempNameString));
	enterProjectMember(tempNameString);
	tempNameString[strlen(tempNameString) - 1] = '\0';
	strcpy(projectNameString,tempNameString);
	initGraph(100,1);
	while(1)
	{
		pCurrent = (TASK_T*) calloc(1,sizeof(TASK_T));
		if(pCurrent == NULL)
		{
			printf("Error - Unable to allocate memory for a new task\n");
			exit(2);
		}
		printf("Enter task name NO.%d [Press RETURN when done]: ",NUMBEROFTASK+1);
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(NUMBEROFTASK <= 0)
			{
				printf("Must have at least one task\n");
				continue;
			}
			else
				break;
		}
		sscanf(stringInput,"%s",pCurrent->Topic);
		printf("Enter task description: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%s",pCurrent->taskDescription);
		printf("Duration(days) of this task: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&pCurrent->Duration);
		memset(tempNameString,0,sizeof(tempNameString));
		
		tempNameString[strlen(tempNameString - 1)] = '\0';
		strcpy(pCurrent->memberNameString,tempNameString);
		strcpy(pCurrent->dependencyString,"NONE");
		pCurrent->Status = -1;
		addVertex(pCurrent->Topic,pCurrent);
		NUMBEROFTASK++;
	}
}
