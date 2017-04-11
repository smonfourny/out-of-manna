#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int* parseInput(char *, char*); // Function prototype to parse given input
int getDropN(char*); // For getting n from drop cmd
void printHTML(int, int, int, int); // To print the actual html
void toUp(char *); // String to uppercase
int* readCSV(); // Read csv file
void writeCSV(int,int,int); // Write to csv
void alterRes(int); // To alter hidden resources
void printRes(); // To print current resources
int takeRes(int, int); // To take resources, return type to report error
void oc(int); // Mark room as occupied or unoccupied
void succ(int,int);


int main(){
  int n = atoi(getenv("CONTENT_LENGTH")); // Get length of input
  char* inv = (char*)malloc(45); // Malloc a pointer to store input
  char* mem = (char*)malloc(30); // Extra pointer to keep original spot, free has problems after tokenizing
  char* cmd = mem; // For 2nd input value, will be tokenized
  fgets(inv,n+1,stdin); // Get input from stdin (POST)
  // Tokenize input, will make inv everything before & and cmd everything after
  // We are expecting inventory to be first and command to be last
  strtok_r(inv, "&", &cmd);
  
  int* numbers = parseInput(inv, cmd); // Remove the names from input and get them into raw values
  toUp(cmd); // Capitalize cmd
  int mana = *(numbers); // numbers[0] has mana
  int gold = *(numbers+1); // numbers[1] has gold

  if(mana <= 0){ // Death
    printHTML(mana, gold, 5, 0);
  }
  else{
  // Deal with various commands with if statements
    if(strncmp(cmd, "DROP", 4)==0){
      int n=getDropN(cmd); // The number part of the command is how much we want to drop
      printHTML(mana, gold, 0, n); // Call print method, 3rd argument is which command
    }
    else if(strncmp(cmd, "PLAY", 4)==0){
      printHTML(mana, gold, 1, 0);
    }
    else if(strncmp(cmd,"EXIT", 4)==0){
      printHTML(mana, gold, 2, 0);
    }
    else if(strncmp(cmd,"REFRESH", 7)==0){
      printHTML(mana, gold, 3, 0);
    }
    else if(strncmp(cmd,"WIN", 3)==0){
      printHTML(mana, gold, 6, 0);
    }
    else if(strncmp(cmd,"TAKE", 4)==0){
      int manaToTake = *(numbers+2);
      int goldToTake = *(numbers+3);
      if(takeRes(manaToTake, goldToTake)){ // If successful, update mana & gold and refresh
	mana += manaToTake;
	gold += goldToTake;
	printHTML(mana, gold, 3, 0);
      }
      else{ // Invalid amount requested
	succ(manaToTake, goldToTake);
	//printHTML(mana,gold, 7, 0); // Retry getting resources again
      }
    }
    else{ // Not a valid command, error
      printHTML(mana, gold, 4, 0);
    }
  }
  
  free(inv); // Free memory
  free(mem);
  return 0; // Successfully finished
}

int* parseInput(char* inv, char* cmd){
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
  if (strncmp(cmd, "command", 7)==0){ // If command 
    // cmd should be command=SOMETHING
    // Trim off the command= part
    int length = strlen(cmd);
    k=0; // Reset temp index
    for(int i=8; i<=length; i++){ // Loop through entries 8 to end of input 
      *(temp+k)=*(cmd+i); // Assign current char to temp jth char
      k++; // Increment k 
    }
    strcpy(cmd, temp); // Copy temp to cmd
  }
  else{ // Otherwise, taking mana and gold, i.e. mana=0&gold=0
    char c[2];
    c[0]=*(cmd+5);
    c[1]='\0';
    numbers[2]= atoi(c); // mana to take is 6th char-ascii val of 0
    c[0] = *(cmd+12);
    numbers[3]=atoi(c); // gold is 12th char
    char* t = "TAKE";
    strcpy(cmd, t); // Copy TAKE into t
  }
  free(temp); // Free mem used by temp
  int* nbAsPtr=numbers; // Make a pointer that points to array 
  return nbAsPtr; 
}

int getDropN(char* cmd){
  // Get everything after DROP in cmd
  char* tmp = (char*)malloc(10); // Allocate memory for a tmp string to store 
  int j = 4; // Index after DROP
  int k = 0; // Index for temp
  char c = *(cmd+j); // Get next char
  while(c!='\0'){ // Loop until null
    *(tmp+k)=c; // Assign char to temp string
    j++;
    k++;
    c=*(cmd+j); // Get next char of cmd
  }
  int n = atoi(tmp); // tmp now stores just the number part of drop
  free(tmp);
  return n;
}

void printHTML(int mana, int gold, int cmd, int n){
  int enough=1; // Boolean for if we have enough money
  if(cmd==0){ // Drop command
    if(gold-n<0){ // If not enough money
      enough = 0;
    }
    else{
    gold-=n; // Drop n gold
    mana+=(n/2); // Get half of hold in mana
    alterRes(n); // Change resources.csv
    } 
  }
  else if(cmd == 5 || cmd == 2){ // Death or exit, mark room as unoccupied
    oc(0);
  }
  else if(cmd == 3){
    oc(1);
  }
  printf("Content-type: text/html\n\n"); // Display HTML
  printf("<html>\n"
	 "<head>\n"
	 "<title>T h e F l o r a l S h o p p e</title> \n"
	 "<!--Linking CSS-->\n");
  if(cmd == 5){ // Death screen, different css
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/dead.css\">\n");
  }
  else if(cmd == 2){ // Exit screen, different background, different css
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/exit.css\">\n");
  }
  else{ // Normal situation
   printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style.css\">\n"); 
  }
  printf("</head>\n"
	 "<body>\n"
	 "<div class=\"main\" id=\"bg\">\n"
	 "<div id=\"text\" class =\"output\">\n"
	 );
  // What to print as a message
  if (cmd==0){ // If DROP n
    printf("<p> You dropped g o l d and received precious m a n n a. </p>\n");
  }
  else if(cmd == 3){//If REFRESH
    printf("<p> Mmm fresh Arizona Iced Tea (c). </p> \n");
  }
  else if(cmd == 2){ // Exit
    printf("<p> THAT IS NOT VERY CASH MONEY OF YOU </p> \n");
  }
  else if(cmd == 5){ // Dead
    printf("<p> You have died. RIP </p> \n");
  }
  else if(cmd == 1){ // If play, print a box explaining game and linking to game
    printf("<p> You and I are going to create a song. Make sure that your lines rhyme with mine. </p>\n"
	   "<form method=\"post\" action=\"challenge.cgi\">\n"
	   "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n", mana,gold);
    printf("<input type=\"submit\" value=\"GO\">\n");
  }
  else if(cmd == 6 || cmd == 7){ // Win or retry
    if(cmd == 7){ // If retry
      printf("<p> Invalid pick of resources! Please try again. </p> \n");
    }
    printRes();
    printf("<p> Pick how much gold and manna you'd like. Note that you can take at most 5 units of something.</p> \n"
	   "<form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">\n"
	   "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
    printf("<select name=\"mana\">\n"
	   "<option value=\"0\"> 0 Manna </option>\n"
	   "<option value=\"1\"> 1 Manna </option>\n"
	   "<option value=\"2\"> 2 Manna </option>\n"
	   "<option value=\"3\"> 3 Manna </option>\n"
	   "<option value=\"4\"> 4 Manna </option>\n"
	   "<option value=\"5\"> 5 Manna </option>\n"
	   "</select>\n");
    printf("<select name=\"gold\">\n"
	   "<option value=\"0\"> 0 Gold </option>\n"
	   "<option value=\"1\"> 1 Gold </option>\n"
	   "<option value=\"2\"> 2 Gold </option>\n"
	   "<option value=\"3\"> 3 Gold </option>\n"
	   "<option value=\"4\"> 4 Gold </option>\n"
	   "<option value=\"5\"> 5 Gold</option>\n"
	   "</select>\n");
    printf("<input type=\"submit\" value=\"TAKE\">\n"
	   "</form>");
  }
  else{ // Not valid
    printf("<p> Invalid command, mortal! Try again. </p> \n");
  }
  if(cmd != 2 && cmd != 5 && cmd !=1 ){ // Not dead, exit or play, print instructions + navigation
    printf("<p> In this d i g i t a l reality, you can DROP 2 gold to get 1 manna. You may also REFRESH yourself with some delicious Arizona Iced Tea (c).</p>\n"
	   "<p> Type PLAY to PLAY. Type EXIT to EXIT this mortal coil. </p>\n"
	   "<p> Click a direction to travel to a new world. </p>\n"
	   "</div>\n");
  }
  printf("<div id=\"inv\" class=\"output\">\n"
	   "<p><b> Inventory </b> </p> \n");

  printf("<p> gold: %d </p>\n", gold);
  printf("<p> \"manna\": %d </p>\n", mana);
    
  printf("</div>\n"
	 "</div>\n"
	 "<div class=\"controls\">\n"
	 "<h1>The F l o r a l Shoppe</h1>\n");
  if(cmd !=2 && cmd !=5 && cmd !=1){ // Not dead, exit or play, print nav
    printf("<div>\n"
	   "<form method=\"post\" action=\"http://cs.mcgill.ca/~smonfo1/cgi-bin/transporter.py\">\n");

    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
  
    printf("<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">\n"
	   "<input id=\"N\" class=\"button\" type=\"submit\" value=\"North\" name=\"North\">\n"
	   "</form>\n"
	   "</div>\n");
    printf("<div>\n");
    printf("<div>\n"
	   "<form method=\"post\" action=\"room.cgi\">\n");

    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
  
    printf("<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">\n"
	   "<input id=\"W\" class=\"button\" type=\"submit\" value=\"West\" name=\"West\">\n"
	   "</form>\n"
	   "</div>\n");

  
    printf("<div>\n"
	   "<form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">\n");

    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
  
    printf("<input id=\"cmd\" type=\"text\" name=\"command\">\n"
	   "</form>\n"
	   "</div>\n");
  
    printf("<div>\n"
	   "<form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">\n");

    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
  
    printf("<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">\n"
	   "<input id=\"E\" class=\"button\" type=\"submit\" value=\"East\" name=\"East\">\n"
	   "</form>\n"
	   "</div>\n"
	   "</div>\n");
  
    printf("<div>\n"
	   "<form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">\n");

    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",mana, gold);
  
    printf("<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">\n"
	   "<input id=\"S\" class=\"button\" type=\"submit\" value=\"South\" name=\"South\">\n"
	   "</form>\n"
	   "</div>\n");
  }
  printf("</div>\n"
	 "</body>\n"
	 "</html>\n"); // Closing tags
}

void toUp(char* string){
  int n = strlen(string);
  for(int i=0; i<n; i++){ // Loop through entire string
    *(string+i)=toupper(*(string+i)); // Make each entry upper case
  }
}

int* readCSV(){
  int* vals = (int*)malloc(20);
  FILE* in = fopen("../resources.csv", "rt"); // new pointer to read existing vals
  fscanf(in, "%d,%d,%d", vals, vals+1, vals+2); // Assign values
  fclose(in); // Close csv for reading
  return vals;
}

void writeCSV(int mana, int gold, int occ){
  FILE* out = fopen("../resources.csv", "wt"); // Overwrite csv
  fprintf(out,"%d,%d,%d", mana, gold, occ); // Put in new values
  fclose(out); 
}

void alterRes(int goldAdded){ // How much gold to gain
  int* vals = readCSV(); // Read CSV
  *(vals+1)+=goldAdded; // vals+1 is gold
  writeCSV(*(vals),*(vals+1),*(vals+2)); // Write 
  free(vals); // Free memory
}

void printRes(){ // Print out what resources the room contains
  int* vals = readCSV();
  printf("<p> The room has %d mana and %d gold. </p>\n",*(vals),*(vals+1));
  free(vals);
}

int takeRes(int manaToTake, int goldToTake){ // To take resources
  int* vals = readCSV();
  int newMana = *(vals)-manaToTake;
  int newGold = *(vals+1)-goldToTake;
  int total = manaToTake+goldToTake;
  if(newMana<0 || newGold<0 || total>5){ // If any of the updated values are negative or taking more than 5, error
    return 0; // False
  }
  else{
    writeCSV(newMana, newGold, *(vals+2));
    return 1; // True
  }
}

void oc(int occup){
  int* vals = readCSV();
  *(vals+2)=occup; // Mark room as occupied
  writeCSV(*(vals),*(vals+1),*(vals+2));
  free(vals);
}

void succ(int a, int b){
  printf("Content-type: text/html\n\n"
	 "%d %d",a, b);
}
