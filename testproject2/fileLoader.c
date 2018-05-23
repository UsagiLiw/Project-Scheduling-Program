/*********************************************
	fileLoader.c
	contains functions related to the load and
	read the project information within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "abstractNetwork.h"
#include "fileLoader.h"
#include "projectInfo.h"
#include "dirent.h"

/*	Break up dependency information of the task 
	seperated by "," delimiter then let addEdges function 
	operates on adding edges
*/
void dependencyHandler()
{
	char * token;
	char dependency[100];
	int retval = 0;				/*In case of bug*/
	TASK_T * pFrom = NULL;
	VERTEX_T * pCurrent = NULL;
	pCurrent = vListHead;
	while(pCurrent != NULL)
	{
		if(strcmp(pCurrent->data->dependencyString,"NONE") == 0)
		{}
		else
		{
			token = strtok(pCurrent->data->dependencyString,",");
			do
			{
				pFrom = findVertex(token);
				retval = addEdge(token,pCurrent->data->Topic,pFrom->Duration);
				if(retval != 1)
				{
					printf("Error - Unable to add dependency\n");
					exit(3);
				}
				token = strtok(NULL,",");
			}while(token != NULL);
		}
		pCurrent = pCurrent->next;
	}
}

/*	Read and break up data of each task.
	Information of each task is stored as a line with delimeters to 
	divide the type of data
	The information then being stored in a network
	task input format: taskname|description|duration|member|dependency|status\n;
	Argument:	taskString - contains the data of a single task within the project
				taskCount - the count of the current task that the function is reading
*/
void readTask(char * taskString)
{
	char name[128];
	char tempNameString[1000];
	TASK_T * pTempTask = NULL;
	char * token;

	pTempTask = (TASK_T*)calloc(1,sizeof(TASK_T));
	if(pTempTask == NULL)
	{
		printf("Error - Unable to allocate memory for a new task\n");
		exit(2);
	}
	sscanf(taskString,"%[^|]|%[^|]|%d|%[^|]|%[^|]|%d;",pTempTask->Topic
														,pTempTask->taskDescription
														,&pTempTask->Duration
														,pTempTask->taskMember
														,pTempTask->dependencyString
														,&pTempTask->Status);
	//printf("\n|%s|\n",pTempTask->Topic);
	//printf("\t%s\n",pTempTask->taskDescription);
	//printf("Duration: %d days\n",pTempTask->Duration);
	//printf("Responsible member: %s\n",pTempTask->taskMember);
	//strcpy(pTempTask->dependencyString,tempEdges);
	//if(pTempTask->Status == 1)
		//printf("Status: DONE\n");
	//else
		//printf("Status: IN PROGRESS\n");
	addVertex(pTempTask->Topic,pTempTask);
	NUMBEROFTASK += 1;
	printf("\n");
}

/*	Read the data within the project file and store and
	show the file
	RETURN:		status - to say whether to progress to the next operation or not
*/
int chooseProject()
{
	FILE * project = NULL;
	char chooseProject[256];
	char projectDirectory[] = "savefile/";
	char stringInput[1000];
	char tempNameString[1000];
	int status = 0;
	TASK_T * pCurrent = NULL;
	TASK_T * pTask = NULL;
		
	while(1)
	{
		strcpy(projectDirectory,"savefile/");
		printf("Choose the project name [Press RETURN to go back] : ");
		memset(stringInput,0,sizeof(stringInput));
		fgets(stringInput,sizeof(stringInput),stdin);
		/*In case user wanted to return to menu instead of choosing file*/
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("\tReturn to main menu\n\n");
			status = 0;
			break;
		}
		sscanf(stringInput,"%[^\n]",chooseProject);
		strcat(projectDirectory,chooseProject);
		project = fopen(projectDirectory,"r");
		if(project == NULL)
		{
			printf("Error - Unable to find the designated project.\n");
			printf("Wrong name or might missing <.txt>)\n\n");
		}
		
		else
		{		
			NUMBEROFTASK = 0;
			fgets(stringInput,sizeof(stringInput),project);			/*Get the project name*/
			sscanf(stringInput,"%[^;]",CHOSENPROJECT.projectName);
			//printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
			strcpy(thisProject,CHOSENPROJECT.projectName);
			fgets(stringInput,sizeof(stringInput),project);
			sscanf(stringInput,"%[^;]",CHOSENPROJECT.initDate);
			//printf("Started on: %s\n\n",CHOSENPROJECT.initDate);
			fgets(stringInput,sizeof(stringInput),project);			/*Get the project description*/
			sscanf(stringInput,"%[^;]",CHOSENPROJECT.description);
			//printf("Description:\n\t%s\n\n",CHOSENPROJECT.description);
			fgets(stringInput,sizeof(stringInput),project);			/*Get the members*/
			sscanf(stringInput,"%[^;]\n",tempNameString);
			breakNames(tempNameString);		
			/*There can be finite number of task so we loop to store each task in graph*/
			initGraph(100,1);
			while(fgets(stringInput,sizeof(stringInput),project) != NULL)
			{
				if(strcmp(stringInput,"\n") == 0)
					continue;
				readTask(stringInput);	
			}
			dependencyHandler();
			fclose(project);	
			status = 1;			
			break;			
		}
	}
	return status;
}

void projectNameList()
{
	DIR * dp = NULL;
	struct dirent * dptr = NULL;
	
	if(NULL == (dp = opendir("savefile/")))
	{
		printf("Error - Unable to find the save folder of the project\n\n");
		exit(1);
	}
	while(NULL != (dptr = readdir(dp)))
	{
		printf(" [ %s ]\n",dptr->d_name);
	}
	closedir(dp);
}


