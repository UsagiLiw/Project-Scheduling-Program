
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int symbolCheck(char * string)
{
	char* symbol = ",|;";
	int bOk = 1;
	int i;
	for (i=0; i < strlen(string); i++)
	{
		if (strchr(symbol,string[i]) != NULL) 
		{
			bOk = 0; 
		}
	}
	return bOk;
}

int main()
{
	char input[100];
	char string[100];
	int bOk;
	printf("Enter: ");
	fgets(input,100,stdin);
	sscanf(input,"%s",string);
	printf("-- %d\n",symbolCheck(string));
}

