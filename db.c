#include <stdio.h>
#include "logo.h"
#include "treedb.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  printWelcome();
  // Read the input file
  char *filename = argv[1];
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  char buffer[128];
  // Main loop
  while(!(feof(database))){
    list = makeDB(database, list);
  }
  fclose(database);
  int choice = -1;
  while(choice != 0) {
    makeChoice(choice);
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      // Query
      readInput("Searching database...", buffer);
      cursor = findKey(list, buffer);
      if(cursor == NULL){
	printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
      break;
    case 2:
      // Update
      readInput("Searching database...", buffer); 
      cursor = findKey(list, buffer);
      if(cursor != NULL){
	char valbuf[128];
	printf("Enter new value: ");
	readline(valbuf, 128, stdin);
	updateValue(buffer, valbuf, cursor);
      }
      else{
	printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
      break;   
    case 3:
      // Insert
      readInput("Searching database for duplicate keys...", buffer);
      Tree cursor = list;
      cursor = findKey(list, buffer);
      //if findKey doesn't find a key matching the one we want to insert, it will return NULL 
      if(cursor == NULL){
	char valbuf[128];
	puts("Key is unique!\n");
	printf("Enter value: ");
	readline(valbuf, 128, stdin);
	list = insertEntry(buffer, valbuf, list);      // Insert new node to the front of the list
      }
      else if(!(cursor == NULL)){
	puts("Key not unique");
      }
      break;	      
    case 4:
      // Delete
      readInput("Searching database...", buffer);
      cursor = deleteEntry(buffer, &list);
      break;     
    case 5:
      // Print database
      printDB(list);
      break;
    case 0:
      // Exit
      puts("Good bye!");
      FreeTree(list);
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again"); 
    }
    puts(""); 
  } 
  
  return 0;
}


