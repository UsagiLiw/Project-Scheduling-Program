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
void chooseTask(char * taskString)
{
	int count = 0;
	int i = 0;
	char stringInput[64];	
	char ** adjacentKeys = NULL;
	
	while(1)
	{
		printf("\nPlease enter the task name that you want to update\n");
		printf("Choose: ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%[^\n]",taskString);
		adjacentKeys = getAdjacentVertices(taskString,&count);
		if(count < 0)
		{
			printf("Error - %s is not within the existing tasks\n",taskString);
		}
		else if(count > 0)
		{
			printf("Task: |%s| has previous required tasks to be done first\n",taskString);
			printf("Included:\n");
			for (i = 0; i < count; i++)
			{
				printf("\t- %s\n",adjacentKeys[i]);
				free(adjacentKeys[i]);
			}
			printf("\n");
			free(adjacentKeys);
		}
		else
			break;		
	}	
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
		printf("What do you want to do next?:\n");
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
				chooseTask(taskString);
				if(updateTaskStatus(taskString) != 0);
				{
					printCriticalPath();
					saveEdit();
				}
				break;
			case 2: /*Edit*/
				printf("\nEdit\n");
				chooseEdit();
				while(1)
				{
					printf("Do you want to save your changes?\n");
					printf("[Y/N] :");
					fgets(stringInput,sizeof(stringInput),stdin);
					if ((stringInput[0] == 'Y') || (stringInput[0] == 'y'))
					{
						strcat(projectDirectory,thisProject);
						strcat(projectDirectory,projectType);
						ret = remove(projectDirectory);
						if(ret != 0)
						{
							printf("Error -  Unable to delete the old %s project\n",thisProject);
							exit(3);
						}
						printCriticalPath();
						saveEdit();
						break;
					}
					else if((stringInput[0] == 'N') || (stringInput[0] == 'n'))
					{
						break;
					}
				}
				printProjectInfo();
				break;
			case 3: /*Delete project*/
				printf("\nDelete Project\n");
				deleteFile();
				status = 0;
				break;
			case 4: /*Go back*/
				printf("\nBack to main menu\n");
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;	
	}
}
