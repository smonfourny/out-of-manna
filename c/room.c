#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* parseInput(char *, char*); // Function prototype to parse given input
void printHTML(int, int, char*);

int main(){
  int n = atoi(getenv("CONTENT_LENGTH")); // Get length of input
  char* inv = (char*)malloc(45); // Malloc a pointer to store input
  char* cmd = (char*)malloc(30); // For 2nd input value, will be tokenized
  fgets(inv,n+1,stdin); // Get input from stdin (POST)
  // Tokenize input, will make inv everything before & and cmd everything after
  // We are expecting inventory to be first and command to be last
  strtok_r(inv, "&", &cmd);
  int* numbers = parseInput(inv, cmd); // Remove the names from input and get them into raw values
  int mana = *(numbers); // numbers[0] has mana
  int gold = *(numbers+1); // numbers[1] has gold
  // Deal with various commands with if statements
  printHTML(mana, gold,cmd);
  free(inv); // Free memory
  free(cmd);
  return 0; // Successfully finished
}

int* parseInput(char* inv, char* cmd){
  // inv should be inventory=#%2C#, with %2C being a POST parsed comma and # being a number
  int numbers[2]; // Array to store mana and gold, will return as ptr
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
  // cmd should be command=SOMETHING
  // Trim off the command= part
  int length = strlen(cmd);
  k=0; // Reset temp index
  for(int i=8; i<=length; i++){ // Loop through entries 8 to end of input 
    *(temp+k)=*(cmd+i); // Assign current char to temp jth char
    k++; // Increment k 
  }
  strcpy(cmd, temp); // Copy temp to in
  free(temp); // Free mem used by temp
  int* nbAsPtr=numbers; // Make a pointer that points to array 
  return nbAsPtr; 
}
void printHTML(int mana, int gold, char* cmd){  
  printf("Content-type: text/html\n\n"); // Display HTML
  printf("<html>\n");
  printf("<body>\n"); // Opening tags
  printf("%d mana, %d gold, %s command",mana, gold, cmd);
  printf("</body>\n"
	 "</html>\n"); // Closing tags
}
