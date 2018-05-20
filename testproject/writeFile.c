/***************************************************************
	writeFile.c
	Handle the write data onto file operations
	for the whole project.

	By Bhimapaka Thapanangkun
	ID: 60070503447
***************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "projectInfo.h"
#include "abstractGraph.h"

MEMBER_T * pHead = NULL;
MEMBER_T * pTail = NULL;

void deleteFile()
{
	int ret = 0;
	char answer[32];

	printf("Are you sure you want to delete %s project?\n",CHOSENPROJECT.projectName);
	printf("[Y/N] :");
	fgets(answer,sizeof(answer),stdin);
	if ((answer[0] == 'Y') || (answer[0] == 'y'))
	{
		ret = remove(thisProject);
		if(ret == 0)
			printf("%s successfully deleted\n",thisProject);
		else
		{
			printf("Error - Unable to delete %s, program terminated\n",thisProject);
			exit(3);
		}
	}
}

void printProjectInfo()
{
	MEMBER_T * pMember = pHead;
	VERTEX_T * pVertex = vListHead;
	TASKMEMBER_T * pTaskMem = NULL;

	printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
	printf("Description:\n\t%s\n\n",CHOSENPROJECT.description);
	printf("Member(s):\n");
	while(pMember != NULL)
	{
		printf("\t- %s\n",pMember->memberName);
		pMember = pMember->pNext; 	
	}
	
	while(pVertex != NULL)
	{
		printf("\n|%s|\n",pVertex->data->Topic);
		printf("\t%s\n",pVertex->data->taskDescription);
		printf("Duration: %d days\n",pVertex->data->Duration);
		printf("Responsible members:\n");
		pTaskMem = pVertex->data->nameHead;
		while(pTaskMem != NULL)
		{
			printf("\t - %s\n",pTaskMem->tName);
			pTaskMem = pTaskMem->pNext;
		}
		if(pVertex->data->Status == 1)
			printf("Status: DONE\n");
		else
			printf("Status: IN PROGRESS\n");
		pVertex = pVertex->next;
	}
	printf("\n\n");
}


/*	Break up member names from a string so that we can store it in the struct
	The names are being seperate by "," which act as a delimiter
	Argrument: tempNameString - The string with all the member names
								seperate by comma
*/
void breakNames(char * tempNameString)
{
	int count = 0;	
	char * token;	
	MEMBER_T * pMember = NULL;
	token = strtok(tempNameString,",");
	printf("Member(s):\n");
	do
	{
		pMember = (MEMBER_T*) calloc(1,sizeof(MEMBER_T));
		if(pMember == NULL)
		{
			printf("Error - Unable to allocate memory for a new member\n");
			exit(2);
		}
		else
		{ 
			strcpy(pMember->memberName,token);
			if(pHead == NULL)
			{
				pHead = pMember;
			}
			else
			{
				pTail->pNext = pMember;
			}
			pTail = pMember;
			printf("\t- %s\n",token);
			count++;
			token = strtok(NULL,",");
		}
	}while(token != NULL);
	printf("\nFound %d members\n\n",count);
}

void saveEdit()
{
	FILE * pOut = NULL;
	MEMBER_T * pMember = NULL;
	VERTEX_T * pVertex = vListHead;
	char nameString[1000];
	char comma[] = ",";
	
	pOut = fopen(thisProject,"w");
	if(fopen == NULL)
	{
		printf("Error - Unable to open and write on %s\n",thisProject);
		exit(3);	
	}
	fprintf(pOut,"%s;\n",CHOSENPROJECT.projectName);
	fprintf(pOut,"%s;\n",CHOSENPROJECT.description);
	pMember = pHead;
	memset(nameString,0,sizeof(nameString));
	while(pMember != NULL)
	{
		strcat(nameString,pMember->memberName);
		strcat(nameString,comma);
		pMember = pMember->pNext; 	
	}
	nameString[strlen(nameString) - 1] = '\0';/*Take out the extra comma*/
	fprintf(pOut,"%s;\n",nameString);
	fprintf(pOut,"%d;\n",NUMBEROFTASK);
	while(pVertex != NULL)
	{
		fprintf(pOut,"%s|%s|%d|",pVertex->data->Topic
							,pVertex->data->taskDescription
							,pVertex->data->Duration);
		fprintf(pOut,"%s|",pVertex->data->memberNameString);
		fprintf(pOut,"%s|",pVertex->data->dependencyString);
		fprintf(pOut,"%d;\n",pVertex->data->Status);	
		pVertex = pVertex->next;
	}
	fclose(pOut);
}
