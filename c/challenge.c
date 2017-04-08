#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printParts(char *toPrint);
void printHTML(char *toPrint);
void removeEnter(char *toChange);
int checkTrailingSpaces(char *toCheck);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);
int findRhyme(char *inWord, int startLine, int endLine);
void *pickWord(int *lines);

void main()
{
	char playerIn[256];
	char lastWord[256];
	int linesInFile[2] = {0,0};
	int inputValidity = 0;
	pickWord(linesInFile);
	while(inputValidity == 0)
	{
		fgets(playerIn,255,stdin);
		removeEnter(playerIn);
		inputValidity = checkTrailingSpaces(playerIn);
	}
	//printParts(playerIn);
	getLastWord(playerIn,lastWord);
	//printParts(lastWord);
	makeLowerCase(lastWord);
	//printParts(lastWord);
	purgeExtraChars(lastWord);
	//printParts(lastWord);
	int isRhyme = findRhyme(lastWord,linesInFile[0],linesInFile[1]);
	if (isRhyme == 1)
	{
		printParts("Good rhyme!");
	}
	else
	{
		printParts("That doesn't rhyme...");
	}

}

void removeEnter(char *toChange)
{
	char *pointer;

	pointer = toChange;

	int counter = -1;
	
	while(*pointer != '\0')
	{
		*pointer++;
		counter++;
	}
	toChange[counter] = '\0';
}

int checkTrailingSpaces(char *toCheck)
{
        char *pointer;

        pointer = toCheck;

        int counter = -1;

        while(*pointer != '\0')
        {
                *pointer++;
                counter++;
        }
	if(toCheck[counter] == ' ')
	{
		printParts("Please don't end your input with spaces.");
		return 0;
	}
	else
	{
		return 1;
	}
}


void printParts(char *toPrint)
{
        char *pointer;
	struct timespec waitTime;
	waitTime.tv_sec = 0;
	waitTime.tv_nsec = 75000000;

        pointer = toPrint;

        while(*pointer != '\0')
        {
		printf("%c",*pointer);
		fflush(stdout);
		nanosleep(&waitTime, NULL);
                *pointer++;
        }
	printf("\n");
}

void printHTML(char *toPrint)
{
	printf("Content-type: text/html\n\n");
	printf("<html>");
	printf("<body>");
	printf("<h1>%s</h1>",toPrint);
	printf("</body>");
	printf("</html>");
}

void getLastWord(char *input, char *lastWord)
{
	char *pointer;

	pointer = strrchr(input,' ');
	if (!pointer)
	{
		copyString(lastWord,input);
	}
	else
	{
		*pointer++;

		int counter = 0;

		while(*pointer != '\0')
        	{
			lastWord[counter] = *pointer;
			*pointer++;
			counter++;
	        }
		lastWord[counter] = '\0';
	}
}

void makeLowerCase(char *toChange)
{
	char *pointer;

	pointer = toChange;

	int counter = 0;

	while(*pointer != '\0')
	{
		if((*pointer >= 'A') && (*pointer <= 'Z'))
		{
			toChange[counter] = toChange[counter] + 32;
		}

		*pointer++;
		counter++;

	}

}

void copyString(char *newString, char *oldString)
{
        char *pointer;

        pointer = oldString;

        int counter = 0;

        while(*pointer != '\0')
        {
		newString[counter] = *pointer;
                *pointer++;
                counter++;
        }
	newString[counter] = '\0';
}

void purgeExtraChars(char *toChange)
{
	char *pointer;
	char newString[256];

	pointer = toChange;

	int counter = 0;

	while(*pointer != '\0')
	{
		if(((*pointer >= 'a') && (*pointer <= 'z')) || (*pointer == '-') || (*pointer == '\''))
		{
			newString[counter] = *pointer;
		}
		else
		{
			counter--;
		}
		*pointer++;
		counter++;

	}
	newString[counter] = '\0';

	copyString(toChange,newString);

}


int findRhyme(char *inWord, int startLine, int endLine)
{
	FILE *rhymeList;
	char *currentWord;
	char wordCopy[256];
	size_t wordSize = 256;
	ssize_t thisLine;
	int counter = 1;
	rhymeList = fopen("rhymelist.txt","r");

	while ((thisLine = getline(&currentWord,&wordSize,rhymeList)) != -1)
	{
		//Only works when you copy the word from the file to a new string
		copyString(wordCopy,currentWord);
		removeEnter(wordCopy);
		//Also remove the carriage return character
		removeEnter(wordCopy);
		if ((strcmp(wordCopy,inWord) == 0) && (counter >= startLine) && (counter <= endLine))
		{
			return 1;
		}
		counter++;
	}

	return 0;

}

void *pickWord(int *lines)
{
	int picker = 0;
	while (picker == 0)
	{
		srand(time(NULL));
		picker = rand() % 4;
	}
	if(picker == 1)
	{
		printHTML("I stand over the lake and cast out my rod,");
		lines[0] = 2;
		lines[1] = 161;
	}
	else if(picker == 2)
        {
		printHTML("The soft breeze in the mountains keeps me cool,");
                lines[0] = 164;
                lines[1] = 293;
        }
	else if(picker == 3)
        {
		printHTML("I arrive at the park and begin to wander,");
                lines[0] = 296;
                lines[1] = 327;
        }
	else
	{
		lines[0] = 1;
                lines[1] = 1;
	}

}
