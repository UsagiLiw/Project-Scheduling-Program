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
char projectFileName[128];
int NUMBEROFTASK;/*Number of task within the projec*/
int out;/*Global status*/
int	memCount;
/****************************************************************/

/****************************************************************/
/*Struct for tasks in the project*/

/* Contains the information of each task*/
typedef struct
{
	char Topic[64];
	char taskDescription[1000];
	int Duration;
	char taskMember[128];
	char dependencyString[1000];	/*Store all dependency as a string*/
	int Status;						/*1 = DONE, -1 = IN PROGRESS*/
} TASK_T;

/****************************************************************/
/*Vertex handler struct from linkedListGraph.c*/
/* List items for the adjacency list.
 * Each one is a reference to an existing vertex
 */
typedef struct _adjacent
{
    void * pVertex;           /* pointer to the VERTEX_T this 
                               * item refers to.
                               */
    unsigned int weight;      /* weight of this edge */
    struct _adjacent * next;  /* next item in the ajacency list */ 
} ADJACENT_T;

/* List items for the main vertex list.*/
typedef struct _vertex
{
    char * key;               /* key for this vertex */
    TASK_T * data;              /* ancillary data for this vertex */
    int color;                /* used to mark nodes as visited */
    int dValue;               /* sum of weights for shortest path so far to this vertex */
    struct _vertex * parent;  /* pointer to parent found in Dijkstra's algorithm */     
    struct _vertex * next;    /* next vertex in the list */
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
	char initDate[64];
	char description[1000];
} PROJECT_T;

PROJECT_T CHOSENPROJECT;
MEMBER_T * pHead;
MEMBER_T * pTail;
/*****************************************************************/

/*****************************************************************/
/*writeFile.c*/
void printProjectInfo();
void deleteFile();
void breakNames(char * tempNameString);
void saveEdit();
/*****************************************************************/
/*createProject.c*/
void addDependency();
void addTaskMember(TASK_T ** pCurrent);
void newProject();
