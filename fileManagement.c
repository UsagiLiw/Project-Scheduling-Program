/*********************************************
	fileManagement.c
	contains functions related to the read and
	write of the projects within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fileManagement.h"

/*	Read the data within the project file and store and
	show the file
	Argument:	thisProject - the name of the project file that the user chooses
*/
/*void readProject(char * thisProject)
{
	FILE * project = NULL;
	char projectName[128];
	char stringInput[128];
	
	while(1)
	{
		sscanf("savefile/thisProject","%s.txt",projectName);
		project = fopen(projectName,"r");
		if(project == NULL)
		{
			printf("Error - Unable to find the designated project\n");
			break;		
		}
		
	}
}*/

/*	Free the linked list from the data stored
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void freeLinklist(PROJECTLIST_T * pHead)
{
	PROJECTLIST_T * pDelete = NULL;
	PROJECTLIST_T * pCurrent = NULL;
	
	pCurrent = pHead;
	while(pCurrent != NULL)
	{
		pDelete = pCurrent;
		pCurrent = pCurrent->pNext;
		free(pDelete);
	}
}

/*	Let the user chooses the project they want
	to load, the program then find the project name from the linked list
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void chooseProject(PROJECTLIST_T * pHead,int count)
{
	char stringInput[64];
	int choose = 0;
	int out = 1;
	int i;
	PROJECTLIST_T * pCurrent = NULL;
	
	while(1)
	{
		printf("Choose the project number [Press RETURN to go back] :");
		fgets(stringInput,sizeof(stringInput),stdin);
		/*In case user wanted to return to menu instead of choosing file*/
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("\tReturn to main menu\n\n");
			out = 0;
			break;
		}
		sscanf(stringInput,"%d",&choose);
		if((choose > count) || (choose < 0))
		{
			printf("\tMust be numerical number of the project that exist in the list\n");
			continue;
		}
		else
		{
			break;
			out = 1;
		}
	}	
	if(out == 1)
	{
		/*Looking through the stored linked list for the project that the user choosed*/
		pCurrent = pHead;
		for(i = 1;i < choose; i++)
		{
			pCurrent = pCurrent->pNext; 		
		} 
		printf("\tYou choose : %s\n\n",pCurrent->projectName);
		strcpy(thisProject,pCurrent->projectName);		/*thisProject is a global variable in fileManagement.h*/
	}
	freeLinklist(pHead);
}

/*	Handle the read and store the project names 
	that exist within the database into a linked list
	Argument:	pHead - The head of the linked list that hold the first value
*/
int projectNameList()
{
	char stringInput[128];
	char tempName[128];
	int count = 0;
	
	PROJECTLIST_T * pHead = NULL;
	PROJECTLIST_T * pTail = NULL;
	PROJECTLIST_T * pCurrent = NULL;
	PROJECTLIST_T * pProject = NULL;
	FILE * nameFile = NULL;
	
	nameFile = fopen("savefile/projectList.txt","r");
	if(nameFile == NULL)
	{
		printf("ERROR - Unable to read project file, PROGRAM TERMINATED\n");
		exit(0);
	}
	while(fgets(stringInput,sizeof(stringInput),nameFile) != NULL)
	{
		/*Skip empty line in case of bug*/
		if(strcmp(stringInput,"\n") == 0)
			continue;
		memset(tempName,0,sizeof(tempName));
		sscanf(stringInput,"%[^\n]",tempName);
		/*Store the project list as a linked list*/
		pProject = (PROJECTLIST_T*) calloc(1,sizeof(PROJECTLIST_T));
		if(pProject == NULL)
		{
			//free(pProject);
			printf("ERROR - Unable to allocate memory for project list\n");
			exit(1);
		}
		printf("\t%d.%s\n",count+1,tempName);
		strncpy(pProject->projectName,tempName,sizeof(pProject->projectName)-1);
		if(pHead == NULL)
		{
			pHead = pTail = pProject;
		}
		else
		{
			pTail->pNext = pProject;
			pTail = pProject;
			pTail->pNext = NULL;
		}
		if(pCurrent == NULL)
		{
			pCurrent = pHead;
		}
		pCurrent = pCurrent->pNext;
		count++;
	}
	printf("Found %d projects stored\n\n",count);
	fclose(nameFile);
	chooseProject(pHead,count);
}


