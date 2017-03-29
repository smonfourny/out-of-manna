#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printParts(char *toPrint);
void removeEnter(char *toChange);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);
int findRhyme(char *inWord, int startLine, int endLine);

void main()
{
	char playerIn[256];
	char lastWord[256];
	printf("Enter a phrase that ends with a word that rhymes with cool.\n");
	fgets(playerIn,255,stdin);
	removeEnter(playerIn);
	printParts(playerIn);
	getLastWord(playerIn,lastWord);
	printParts(lastWord);
	makeLowerCase(lastWord);
	printParts(lastWord);
	purgeExtraChars(lastWord);
	printParts(lastWord);
	int isRhyme = findRhyme(lastWord,13,17);
	if (isRhyme == 1)
	{
		printf("The word at the end of your phrase does rhyme with cool!\n");
	}
	else
	{
		printf("The word at the end of your phrase does not rhyme with cool...\n");
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
		if ((strcmp(wordCopy,inWord) == 0) && (counter >= startLine) && (counter <= endLine))
		{
			return 1;
		}
		counter++;
	}

	return 0;

}
