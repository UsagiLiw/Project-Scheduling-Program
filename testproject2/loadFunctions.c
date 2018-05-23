/*********************************************
	loadFunctions.c
	Handle the operation after the user chooses
	to load specific project.
	Either to update, delete or exit.

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "loadFunctions.h"
#include "abstractNetwork.h"
#include "projectInfo.h"

/*	Ask for the task number that the user wants to
	edit its status
	ARGUMENTS:	taskString - the choosen task that the user wanted to edit
*/
int chooseTask(char * taskString)
{
	int count = 0,i;
	char stringInput[128];	
	int status = 1;
	int inCount = 0;
	char ** adjacentKeys;
	TASK_T * pCurrent = NULL;
	TASK_T * pDepen = NULL;
	VERTEX_T * pVertex2 = vListHead;
	
	printf("\nPlease enter the task name that you want to update\n");
	printf("Choose: ");
	fgets(stringInput,sizeof(stringInput),stdin);
	sscanf(stringInput,"%[^\n]",taskString);
	pCurrent = findVertex(taskString);
	if(pCurrent == NULL)
	{
		printf("Error - Unable to find | %s | within existed task\n",taskString);
		status = 0;
	}
	else
	{
		printf("Prior requirements: ");
		adjacentKeys = getDependencyVertices(pCurrent->Topic,&count);
		if(count < 1)
		{
			status = 1;
			printf("No prior requirement\n\n");
		}
		else
		{
			for(i = 0; i < count; i++)
			{
				pDepen = findVertex(adjacentKeys[i]);
				if(pDepen->Status != 1)
				{
					printf("\n\t - %s",adjacentKeys[i]);
					status = 0;
				}
				free(adjacentKeys[i]);
			}
			if(status != 0)
			{
				printf("NONE");
			}
			printf("\n\n");
		}
		free(adjacentKeys);
	}
	return status;
}

/*	Show the user what option they have after 
	successfully load a new file
*/
void displayOptions()
{
	int choose = 0;
	int task = 0;
	int status = 1;
	char stringInput[32];
	char taskString[100];
	int ret = 0;
	char projectDirectory[] = "savefile/";
	char projectType[] = ".txt";

	while(status != 0)
	{
		printf("\nWhat do you want to do next?:\n");
		printf("\t1.Update task status\n");
		printf("\t2.Edit\n");
		printf("\t3.Delete Project\n");
		printf("\t4.Go back to main menu\n");	
		printf("Choose :");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choose);
		switch(choose)
		{
			case 1: /*Update task status*/
				printf("\nUpdate Task Status\n");
				memset(taskString,0,sizeof(taskString));
				if(chooseTask(taskString) != 0)
				{	
					if(updateTaskStatus(taskString) != 0);
					{
						printCriticalPath();
					}
				}
				break;
			case 2: /*Edit*/
				printf("\nEdit\n");
				chooseEdit();
				printProjectInfo();
				printCriticalPath();
				break;
			case 3: /*Delete project*/
				printf("\nDelete Project\n");
				deleteFile();
				status = 0;
				break;
			case 4: /*Go back*/
				printf("\nBack to main menu\n");
				printProjectInfo();				
				//saveEdit();
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;	
	}
}
