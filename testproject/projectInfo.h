/*****************************************************
	projectInfo.h
	<Header file>
	Contains the data for the chosen project
	and data for saved project

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 25/04/2018
*****************************************************/

/*Global Variables*/
char thisProject[128];/*Global variable containing the name of the chosen project*/
int NUMBEROFTASK;/*Number of task within the projec*/
int out;/*Global status*/
/****************************************************************/

/****************************************************************/
/*Struct for tasks in the project*/

typedef struct _taskmember
{
	char tName[128];
	struct _taskmember * pNext;
} TASKMEMBER_T;

/* Contains the information of each task*/
typedef struct
{
	char Topic[64];
	char taskDescription[1000];
	int Duration;
	TASKMEMBER_T * nameHead;
	char memberNameString[1000];
	char dependencyString[1000];	/*Store all dependency as a string*/
	int Status;						/*1 = DONE, -1 = IN PROGRESS*/
} TASK_T;

/****************************************************************/
/*Vertex handler struct from linkedListGraph.c*/
/* List items for the adjacency list.
 * Each one represents an edge leading to an existing vertex
 */
typedef struct _adjVertex
{
    void * pVertex;           /* pointer to the VERTEX_T this 
                               * item refers to.
                               */
    struct _adjVertex* next;  /* next item in the ajacency list */ 
} ADJACENT_T;

/* List items for the main vertex list.*/
typedef struct _vertex
{
    char * key;               /* key for this vertex */
    TASK_T * data;              /* additional data for this vertex */
    int color;                /* used to mark nodes as visited */
    struct _vertex * next;    /* next vertex in the list */
	struct _vertex * fromVertex;  /* vertex that arrive from */
    ADJACENT_T * adjacentHead;    /* pointer to the head of the
		                   * adjacent vertices list
                                   */
    ADJACENT_T * adjacentTail;    /* pointer to the tail of the
			           * adjacent vertices list
                                   */
}  VERTEX_T;


VERTEX_T * vListHead;
VERTEX_T * vListTail;
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
MEMBER_T * pHead;
MEMBER_T * pTail;
/*****************************************************************/

/*****************************************************************/
/*writeFile.c*/
void addDependency();
void printProjectInfo();
void deleteFile();
void breakNames(char * tempNameString);
void saveEdit();
/*****************************************************************/


