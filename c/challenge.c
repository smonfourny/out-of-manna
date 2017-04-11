#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printImage(int inputState);
void printBold(char *toPrint);
int checkState(char *toPrint);
void removeEnter(char *toChange);
void plusesToSpaces(char *toChange);
void restoreCharacters(char *toChange);
int getInputState(char *playerIn);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);
int findRhyme(char *inWord, int startLine, int endLine);
void printFile();
void pickWord(int inputState, int mana, int gold);
void *pickLines(int inputState, int *lines);
void newSong();
void addSongLine(char *toWrite);
int* parseInv(char*);

void main()
{
	fflush(stdout);
	printf("Content-type: text/html\n\n");
	printf("<html><head><title>T h e F l o r a l S h o p p e</title><!--Linking CSS-->");
	int n = atoi(getenv("CONTENT_LENGTH")); // Get the length of stdin
	char inv[n+2]; // Array to store inventory
	fgets(inv, n+1, stdin); // Get the input
	char* playerIn = (char*) malloc(256);
	strtok_r(inv, "&", &playerIn); // Tokenize input, separating inventory
	int * numbers = parseInv(inv); // Get mana and gold from inv
	int mana = *(numbers);
	int gold = *(numbers+1); 
	char lastWord[256];
	int linesInFile[2] = {0,0};
	int inputState;
	fgets(playerIn,255,stdin);
	plusesToSpaces(playerIn);
	restoreCharacters(playerIn);
	inputState = getInputState(playerIn);
	if (inputState == -1)
	{
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">");
		printBold("You're going to leave?");
		printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                printf("<form method=\"POST\" action=\"../gametest.html\"> Press Here To Return: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold); //SET THE ACTION TO THE DESTINATION
	}
	if (inputState == 0)
	{
		newSong();
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/can03.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">");
		pickWord(inputState, mana, gold);
	}
	else
	{
		getLastWord(playerIn,lastWord);
		makeLowerCase(lastWord);
		purgeExtraChars(lastWord);
		pickLines(inputState, linesInFile);
		int isRhyme = findRhyme(lastWord,linesInFile[0],linesInFile[1]);
		if (isRhyme == 1)
		{
			if (inputState > 4)
			{
				addSongLine(playerIn);
				printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/can00.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">");
				printFile();
				printBold("You're winner!");
				printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                                printf("<form method=\"POST\" action=\"./room.cgi\"> Press Here To Return: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"hidden\" name=\"command\" value=\"WIN\"><input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold); //SET THE ACTION TO THE DESTINATION
			}
			else {
				addSongLine(playerIn);
				inputState+=2;
				printImage(inputState);
				inputState-=2;
				printBold("Well done. Here is your next rhyme.");
				pickWord(inputState, mana, gold);
			}
		}
		else if (inputState != -1)
		{
			printImage(inputState);
			printBold("That does not rhyme, try again. Here's your prompt:");
			if (inputState == 1)
        		{
                        	printBold("I just can't comprehend it");
				printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
                	}
                	else if (inputState == 2)
                	{
                        	printBold("I'm giving everything I've got");
				printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
				printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
			}
                	else if (inputState == 3)
                	{
                        	printBold("I won't slow down");
				printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                		printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
			}
                	else if (inputState == 4)
                	{
                        	printBold("I'll keep going on");
                                printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                		printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
			}
			else if (inputState == 5)
                        {
                                printBold("So it's not up to you");
                                printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"3O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
			}
                        else if (inputState == 6)
                        {
                                printBold("So don't say you can't make a move");
                                printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"3T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
			}


		}
	}
	printf("</div></body></html>");
}

void printImage(int inputState)
{
	if ((inputState == 1) || (inputState == 2))
	{
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/can03.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">"); // No cans
	}
	else if ((inputState == 3) || (inputState == 4))
        {
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/can02.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">"); // One can
        }
	else if ((inputState == 5) || (inputState == 6))
        {
		printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/can01.css\"></head><body><div class=\"main\" id=\"bg\"><div id=\"text\" class=\"output\">"); // Two cans
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

void plusesToSpaces(char *toChange)
{
        char *pointer;

        pointer = toChange;

        int counter = 0;

        while(*pointer != '\0')
        {
		if (*pointer == '+')
		{
			toChange[counter] = ' ';
		}
                *pointer++;
                counter++;
        }
	if (*pointer == '+')
	{
		toChange[counter] = ' ';
	}

}

void restoreCharacters(char *toChange)
{
        char *pointer;

        pointer = toChange;

        int counter = 0;

        while(*pointer != '\0')
        {
                if ((*pointer == '%') && (toChange[counter+1] == '2') && (toChange[counter+2] == '7'))
                {
                        toChange[counter] = '\'';
			*pointer++;
			*pointer++;
                }
		else if ((*pointer == '%') && (toChange[counter+1] == '2') && (toChange[counter+2] == 'C'))
                {
                        toChange[counter] = ',';
                        *pointer++;
                        *pointer++;
                }
		else if (*pointer == '%')
                {
			while (*pointer == '%')
			{
                        	*pointer++;
                        	*pointer++;
				*pointer++;
			}
			toChange[counter] = *pointer;
                }
		else
		{
			toChange[counter] = *pointer;
		}
                *pointer++;
                counter++;
        }
        toChange[counter] = '\0';

}


int getInputState(char *playerIn)
{
	char *pointer;

	pointer = playerIn;

	int counter = 0;

	int inputState = 0;

	while(*pointer != '\0')
	{
		if (counter < 2)
		{
			if (*pointer == '1')
			{
				inputState++;
			}
			if (*pointer == '2')
                        {
                                inputState+=3;
                        }
			if (*pointer == '3')
                        {
                                inputState+=5;
                        }
			if (*pointer == 'T')
                        {
                                inputState++;
                        }
		}
		if ((counter == 3) && (*pointer == 'Q'))
		{
			*pointer++;
			if (*pointer == 'U')
			{
				*pointer++;
				if (*pointer == 'I')
				{
					*pointer++;
					if (*pointer == 'T')
					{
						*pointer++;
						if (*pointer == '\0')
						{
							return -1;
						}
						else
						{
							*pointer--;
						}
					}
					else
					{
						*pointer--;
					}
				}
				else
				{
					*pointer--;
				}
			}
			else {
				*pointer--;
			}
		}
		if (counter > 2)
		{
			playerIn[counter - 3] = *pointer;
		}
		*pointer++;
		counter++;
	}
	playerIn[counter - 3] = '\0';

	return inputState;

	

}

void printBold(char *toPrint)
{
	printf("<p>%s</p>",toPrint);
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

void printFile()
{

	printBold("We have reached C R I T I C A L   A E S T H E T I C. Here is the song we wrote:");
	FILE *file;
        char *currentLine;
        char lineCopy[256];
        size_t lineSize = 256;
        ssize_t thisLine;
        file = fopen("song.txt","r");

        while ((thisLine = getline(&currentLine,&lineSize,file)) != -1)
        {
                //Only works when you copy the word from the file to a new string
                copyString(lineCopy,currentLine);
		printf("<p>%s</p>",lineCopy);
		fflush(stdout);
        }

}


void pickWord(int inputState, int mana, int gold)
{
	int picker;
	srand(time(NULL));
	picker = rand() % 2;
	if (inputState == 0)
	{
		if (picker == 0)
		{
			printBold("I just can't comprehend it");
			addSongLine("I just can't comprehend it");
			printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
		}
		else if (picker == 1)
        	{
			printBold("I'm giving everything I've got");
			addSongLine("I'm giving everything I've got");
			printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
        		printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
		}
	}
	else if ((inputState == 1) || (inputState == 2))
	{
		if (picker == 0)
        	{
			printBold("I won't slow down");
			addSongLine("I won't slow down");
			printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
        		printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
		}
		else if (picker == 1)
		{
			printBold("I'll keep going on");
			addSongLine("I'll keep going on");
			printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
		}
	}
	else if ((inputState == 3) || (inputState == 4))
        {
                if (picker == 0)
                {
                        printBold("So it's not up to you");
                        addSongLine("So it's not up to you");
                        printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"3O\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
                }
                else if (picker == 1)
                {
                        printBold("So don't say you can't make a move");
                        addSongLine("So don't say you can't make a move");
                        printf("</div></div><div class=\"controls\"><h1>The F l o r a l Shoppe</h1><div>");
                	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"> <input type=\"text\" name=\"3T\"> <input type=\"submit\" value=\"Yeah!\"> </form></div>",mana,gold);
		}
        }
}

void *pickLines(int inputState, int *lines)
{
	if (inputState == 1)
	{
		lines[0] = 2;
                lines[1] = 148;
	}
	else if (inputState == 2)
	{
		lines[0] = 151;
                lines[1] = 428;
	}
	else if (inputState == 3)
	{
                lines[0] = 431;
                lines[1] = 561;
        }
	else if (inputState == 4)
	{
                lines[0] = 564;
                lines[1] = 1114;
        }
	else if (inputState == 5)
        {
                lines[0] = 1117;
                lines[1] = 1656;
        }
        else if (inputState == 6)
        {
                lines[0] = 1659;
                lines[1] = 1688;
        }
}

void newSong()
{
	fflush(stdout);
	FILE *file;
	char emptyString[1];
	emptyString[0] = '\0';
	file = fopen("song.txt","w");
	fprintf(file,"%s",emptyString);
	fclose(file);
}

void addSongLine(char *toWrite)
{
	fflush(stdout);
	FILE *file;
        file = fopen("song.txt","a");
        fprintf(file,"%s\n",toWrite);
        fclose(file);
}

int* parseInv(char* inv){
	// inv should be inventory=#%2C#, with %2C being a POST parsed comma and # being a number
	int numbers[4]; // Array to store mana and gold, will return as ptr
	char* temp = (char*)malloc(40); // Malloc temp pointer
	int k=0; // Int to index through temp
	int j = 10; // Int to index through inv, start at 10, after =
	char c=*(inv+j); // Char after =
	// Will iterate through inv until char is %
	while(c!='%'){
	  *(temp+k)=c; // If we passed check of c='%', then we have a number
	  k++; // Increment k
	  j++; // Increment j
	  c = *(inv+j); // Get next char
	}
	*(temp+k)='\0'; // Add a null at the end
	numbers[0] = atoi(temp); // Mana as an int
	// j is now at the index of the %, so j+3 will give us char after %2C
	j+=3;
	k=0; // Reset index of temp, starting over for next number
	c=*(inv+j);
	while(c!='\0'){ // Iterate until we hit end of string
	  *(temp+k)=c; // Take number that passed check
	  k++;
	  j++;
	  c = *(inv+j);
	}
	*(temp+k)='\0'; // Add null
	numbers[1] = atoi(temp); // Gold as an int
	int* nbAsPtr=numbers; // Make a pointer that points to array 
	return nbAsPtr; 
}
