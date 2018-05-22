/*  
 * ioFunctions.h
 *
 * Declarations for the functions in ioFunctions.c
 *
 * Created by Sally Goldin, 31 August 2010 for CPE 100 demonstration
 * Updated 18 Oct 2014
 */

#define CHARMAX 32

/* Structure used to return both a number and 
 * the corresponding string from the same function 
 * in getNumericString()
 */
typedef struct
    {
    char stringVal[CHARMAX];   /* string version of a number */
    int integerVal;            /* integer version of a number */
    } VALUE_RECORD_T;

/*dateToday function: This function will get the present date
*					  then store the date of today into pDay,pMonth and pYear
**/
void dateToday(int* pDay, int *pMonth, int* pYear);

/*checkDate function: Check the input release date if the format is valid
*It return 'check' variable:	1 - if the input is not valid
*								0 - if the input is valid*/
int checkDate(char* inputDate);

/*dateCompare function: compare date input to the date today
*return 'check' value: 1 - if the input is over the date today
*					   0 - if the input is under the date today*/
int dateCompare(int day1,int month1,int year1, 
                int day2,int month2,int year2);

/*checkSeenDate function: Check if date that the user insert is within the present or the past
*return 'check' value: 1 - if the input is over the date today
*					   0 - if the input is under the date today*/
int checkSeenDate(char* inputDate);

/*	Check for the symbol that should not be allow 
	for the input. As these symbols act as a delimiter
	for the program to read the file
	Returns 1 if all are not either "," "|" ";", 0 if 
	found any of them in the input
*/
int symbolCheck(char * string);

/*  Check that a string contains only digits.
 *  testString  - String to be checked
 *  Returns 1 if all digits, 0 if not
 */
int isDigitString(char* testString);

/*  Check that a string contains only alphabetic characters.
 *  (No punctuation, digits or white space allowed)
 *  testString  - String to be checked
 *  Returns 1 if all alpha chars, 0 if not
 */
int isAlphaString(char* testString);

/* Get an integer value from the user that is between
 * a specified min and max value. Keeps asking until 
 * the user enters a valid value.
 * prompt - Message to print to ask the user for the value
 * min    - Smallest acceptable value for the integer
 * max    - Largest acceptable value for the integer
 * Returns the final, correct integer entered by the user.
 */
int getLimitedInteger(char* prompt, int min, int max);

/* Get a string no longer than a specified length, which 
 * must be all alphabetic characters. Note that the maximum
 * length that this function can handle is 255 characters.
 * prompt - Message to print to ask the user for the value
 * maxlength - Maximum length of the string
 * outputString - Array for returning the entered string.
 * Returns 1 if all is okay, 0 if the maxlength is too large.
 */
int getLimitedString(char* prompt, int maxlength, char * outputString);

/* Get any string - does not have to be  all alphabetic characters,
 * but cannot be empty.
 * prompt - Message to print to ask the user for the value
 * maxlength - Maximum length of the string
 * outputString - Array for returning the entered string.
 */
void getString(char* prompt, int maxlength, char * outputString);

/* Get a numeric string. Return the value as both
 * a string and an integer by setting elements 
 * of the passed structure.
 * prompt - Message to print to ask the user for the value
 * pValRec  - pointer to a structure whose fields
 *            we want to set
 */
void getNumericString(char* prompt, VALUE_RECORD_T * pValRec);
