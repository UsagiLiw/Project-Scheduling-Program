/*******************************************
	projectEdit.c

	Allow user to be able to edit the 
	content of the project
*******************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "loadFunctions.h"
#include "abstractNetwork.h"
#include "projectInfo.h"
#include "ioFunctions.h"

void updateDependency()
{
	int choose = 0;
	int status = 1;
	char stringInput[128];
	char choseTask[128];
	char fromTask[128];	
	char toTask[128];
	TASK_T * pCurrent;
	char ** adjacentKeys;
	int count = 0,i;	

	printDepthFirst();
	while(status != 0)
	{
		printf("What do you want to do?\n");
		printf("\t1.Show dependency of the task\n");
		printf("\t2.Add dependency\n");
		printf("\t3.Remove dependency\n");
		printf("\t4.Back to load menu\n");
		printf("Choose : ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choose);
		switch(choose)
		{
			case 1: /*show dependency*/
				printf("Choose Task : ");
				memset(stringInput,0,sizeof(stringInput));
				fgets(stringInput,sizeof(stringInput),stdin);
				sscanf(stringInput,"%[^\n]",choseTask);
				pCurrent = findVertex(choseTask);
				if(pCurrent == NULL)
				{
					printf("Error - Unable to find %s within existing task\n\n",choseTask);
				}
				else
				{
					adjacentKeys = getDependencyVertices(choseTask,&count);
					if(count > 0)
					{
						for(i = 0; i < count; i++)
						{
							printf("\n\t - %s",adjacentKeys[i]);
							free(adjacentKeys[i]);
						}
						printf("\n\n");
						free(adjacentKeys);
					}
					else
						printf("No prior requirement\n\n");
				}
				break;
			case 2: /*Add dependency*/
				addDependency();
				break;
			case 3: /*Remove dependency*/
				while(1)
				{
					memset(stringInput,0,sizeof(stringInput));
					printf("Please specify the dependency to be remove\n");
					printDepthFirst();
					memset(fromTask,0,sizeof(fromTask));
					memset(toTask,0,sizeof(toTask));
					printf("Enter FROM task [Press RETURN when done] : ");
					fgets(stringInput,sizeof(stringInput),stdin);
					if(strcmp(stringInput,"\n") == 0)
						break;
					sscanf(stringInput,"%[^\n]",fromTask);
					printf("Enter TO task :");
					memset(stringInput,0,sizeof(stringInput));
					fgets(stringInput,sizeof(stringInput),stdin);
					sscanf(stringInput,"%[^\n]",toTask);
					if(removeEdge(fromTask,toTask) != 1)
					{
						printf("Error - Unable to find one or both of the tasks\n");
					}
				}
				break;
			case 4:
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;
	}
}

void updateTask()
{
	int choose = 0;
	int status = 1;
	char stringInput[128];
	char taskRemove[128];
	TASK_T * pCurrent = NULL;

	printDepthFirst();
	while(status != 0)
	{
		printf("What do you want to do?\n");
		printf("\t1.Add new task\n");
		printf("\t2.Remove task\n");
		printf("\t3.Return to load menu\n");
		printf("Choose : ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choose);
		switch(choose)
		{
			case 1:
				while(1)
				{
					pCurrent = (TASK_T*) calloc(1,sizeof(TASK_T));
					if(pCurrent == NULL)
					{
						printf("Error - Unable to allocate memory for a new task\n\n");
						exit(2);
					}
					printf("Enter task name NO.%d : ",NUMBEROFTASK+1);
					memset(stringInput,0,sizeof(stringInput));	
					fgets(stringInput,sizeof(stringInput),stdin);
					if(strcmp(stringInput,"\n") == 0)
					{
						continue;
					}
					if(symbolCheck(stringInput) == 0)
					{
						printf("Error - < ; | , > symbols are not allow in the input\n\n");
						continue;
					}
					sscanf(stringInput,"%[^\n]",pCurrent->Topic);
					while(1)
					{
						printf("Enter task description: ");
						memset(stringInput,0,sizeof(stringInput));	
						fgets(stringInput,sizeof(stringInput),stdin);
						if(symbolCheck(stringInput) == 0)
						{
							printf("Error - < ; | , > symbols are not allow in the input\n\n");
							continue;
						}
						if(strcmp(stringInput,"\n") == 0)
						{
							strcmp(pCurrent->taskDescription,"NONE");
						}
						else
						{
							sscanf(stringInput,"%[^\n]",pCurrent->taskDescription);
						}			
						break;
					}
					while(1)
					{
						printf("Duration(days) of this task: ");
						memset(stringInput,0,sizeof(stringInput));	
						fgets(stringInput,sizeof(stringInput),stdin);
						stringInput[strlen(stringInput) - 1] = '\0';
						if(isDigitString(stringInput) == 0)
						{
							printf("Error - Only numerics are allow\n\n");
							continue;
						}
						sscanf(stringInput,"%d",&pCurrent->Duration);
						break;
					}
					addTaskMember(&pCurrent);
					//printf("%s;\n",pCurrent->memberNameString);
					//strcpy(pCurrent->dependencyString,"NONE");
					pCurrent->Status = -1;
					if(addVertex(pCurrent->Topic,pCurrent) != 1)
					{
						printf("\nError - task: %s already exist\n\n",pCurrent->Topic); 
					}
					printf("\n");
					NUMBEROFTASK++;
					break;
				}
				break;
			case 2:
				printf("Remove task: ");
				fgets(stringInput,sizeof(stringInput),stdin);
				sscanf(stringInput,"%[^\n]",taskRemove);
				if(removeVertex(taskRemove) == NULL)
					printf("Error - Unable to remove task: %s\n",taskRemove);
				break;
			case 3:
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;
	}
}

void updateMember()
{
	int choose = 0;
	int task = 0;
	int status = 1;
	char stringInput[128];
	char removeName[128];
	char tempName[128];
	int bOk = 0;
	MEMBER_T * pMember = NULL;
	MEMBER_T * pMemCheck = NULL;
	MEMBER_T * pPred = NULL;
	MEMBER_T * pFound = NULL;
	
	printf("Members: \n");
	pMember = pHead;
	while(pMember != NULL)
	{
		printf("\t - %s\n",pMember->memberName);
		pMember = pMember->pNext;
	}
	while(status != 0)
	{
		printf("What do you want to do?\n");
		printf("\t1.Add new member\n");
		printf("\t2.Remove member\n");
		printf("\t3.Back to Edit menu\n");
		printf("Choose: ");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choose);
		switch(choose)
		{
			case 1:
				while(1)
				{
					printf("Enter member name NO.%d : ",memCount+1);
					memset(stringInput,0,sizeof(stringInput));
					memset(tempName,0,sizeof(tempName));	
					fgets(stringInput,sizeof(stringInput),stdin);
					if(strcmp(stringInput,"\n") == 0)
					{
						continue;
					}
					if(symbolCheck(stringInput) == 0)
					{
						printf("Error - < ; | , > symbols are not allow in the input\n\n");
						continue;
					}
					sscanf(stringInput,"%[^\n]",tempName);
					pMemCheck = pHead;
					bOk = 1;
					while(pMemCheck != NULL)
					{
						if(strcmp(pMemCheck->memberName,tempName) == 0)	
						{
							bOk = 0;
							printf("Error - This name already exist, please use something else\n\n");
							break;
						}
						pMemCheck = pMemCheck->pNext;
					}
					if(bOk == 1)
					{
						pMember = (MEMBER_T*) calloc(1,sizeof(MEMBER_T));
						if(pMember == NULL)
						{
							printf("Error - Unable to allocate memory\n\n");
							exit(2);
						}
						strcpy(pMember->memberName,tempName);
						if(pHead == NULL)
						{
							pHead = pMember;
						}
						else
						{
							pTail->pNext = pMember;
						}
						pTail = pMember;
						memCount++;
					}
					break;
				}
				break;
			case 2:
				printf("Enter the member name to be remove : ");
				memset(stringInput,0,sizeof(stringInput));
				fgets(stringInput,sizeof(stringInput),stdin);
				sscanf(stringInput,"%s",removeName);
				pMemCheck = pHead;
				bOk = 0;
				while(pMemCheck != NULL)
				{
					if(strcmp(pMemCheck->memberName,removeName) == 0)	
					{
						bOk = 1;
						pFound = pMemCheck;
						break;
					}
					pPred = pMemCheck;
					pMemCheck = pMemCheck->pNext;
				}	
				if(bOk == 0)
					printf("Error - Cannot find %s in the list\n\n",removeName);
				else
				{
					if(pPred != NULL)
					{
						pPred->pNext = pFound->pNext;
					}
					else
					{
						pHead = pFound->pNext;
					}
					if(pFound == pTail)
					{
						pTail = pPred;
					}
					free(pFound);
					memCount--;
				}
				break;
			case 3:
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;
				
	}
}

void chooseEdit()
{
	int choose = 0;
	int task = 0;
	int status = 1;
	char stringInput[1000];
	char taskString[100];

	while(status != 0)
	{
		printf("What do you want to edit?:\n");
		printf("\t1.Starting Date\n");
		printf("\t2.Project Description\n");
		printf("\t3.Project Member\n");
		printf("\t4.Task\n");
		printf("\t5.Dependency\n");
		printf("\t6.Back to load menu\n");
	
		printf("Choose :");
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%d",&choose);
		switch(choose)
		{

			case 1:	/*Starting Date*/
				while(1)
				{
					printf("Change starting date to [yyyy-mm-dd]: ");
					memset(stringInput,0,sizeof(stringInput));	
					fgets(stringInput,sizeof(stringInput),stdin);
					stringInput[strlen(stringInput) - 1] = '\0';
					if(strcmp(stringInput,"\n") == 0)
					{
						printf("Error - Cannot leave the date empty\n\n");
						continue;
					}
					if(checkDate(stringInput) == 0)
					{
						continue;
					}
					sscanf(stringInput,"%[^\n]",CHOSENPROJECT.initDate);
					printf("\n\n");
					break;
				}
				break;
			case 2: /*Project Description*/
				while(1)
				{
					printf("Change project description to : \n");
					memset(stringInput,0,sizeof(stringInput));	
					fgets(stringInput,sizeof(stringInput),stdin);
					if(symbolCheck(stringInput) == 0)
					{
						printf("Error - < ; | , > symbols are not allow in the input\n\n");
						continue;
					}
					if(strcmp(stringInput,"\n") == 0)
					{
						strcpy(CHOSENPROJECT.description,"NONE");
					}
					else
					{
						sscanf(stringInput,"%[^\n]",CHOSENPROJECT.description);
					}
					printf("\n\n");
					break;
				}
				break;
			case 3: /*Project Member*/
				updateMember();
				break;
			case 4: /*Task*/
				updateTask();
				break;
			case 5:	/*Dependency*/
				updateDependency();
				break;
			case 6:
				printf("Back to load menu\n");
				status = 0;
				break;
			default:
				printf("\nError - Please choose the existed options\n");
				break;
		}
		choose = 0;	
	}
}
