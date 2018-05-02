/*****************************************************
	projectInfo.h
	<Header file>
	Contains the data for the chosen project
	and data for saved project

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 25/04/2018
*****************************************************/

/****************************************************************/
/*Global variable containing the name of the chosen project*/
char thisProject[128];
int out;
/****************************************************************/

/****************************************************************/
/*Struct for tasks in the project*/
/*Linked-list contain the member responsible for each task*/
typedef struct _taskMember
{
	char name[128];
	struct _taskMember * pNext;
} TASKMEMBER_T; 

typedef struct _task
{
	char Topic[64];
	char taskDescription[1000];
	int Duration;
	TASKMEMBER_T * taskMember;
    struct _task * nextTask;
} TASK_T;

TASK_T * LISTTASK;
/****************************************************************/

/****************************************************************/
/*Struct for the information of the whole project(task not included)*/
typedef struct _member
{
	char memberName[128];
	struct _member * pNext;
} MEMBER_T;

typedef struct
{
	char projectName[32];
	char description[1000];
} PROJECT_T;

PROJECT_T CHOSENPROJECT;
MEMBER_T * MEMBER;
/*****************************************************************/


