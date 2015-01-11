#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

Node cursor;
Node list = NULL;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

Node makeDB(char *buffer, FILE *database, Node list){
  Node newNode = malloc(sizeof(struct node));
  readline(buffer, 128, database);
  newNode->key = malloc(strlen(buffer) + 1);
  strcpy(newNode->key, buffer);
  readline(buffer, 128, database);
  newNode->value = malloc(strlen(buffer) + 1);
  strcpy(newNode->value, buffer);
  newNode->next = list;
  return newNode;
}

void printEntry(const char *n, Node cursor){
  puts(n);
  printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
}

Node findKey(Node cursor, char *buffer){
  while(cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      printEntry("found entry:", cursor);
      return cursor;
    }else{
      cursor = cursor->next;
    }
  }
  return NULL;
}

Node updateValue(char *buffer, Node cursor){
  if(cursor != NULL){
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!");
    return cursor;
  }
 else{
   printf("Could not find an entry matching key \"%s\"!\n", buffer);
   return cursor;
 }
}

Node insertEntry(char *buffer, Node list, Node cursor){
  if(cursor == NULL){
    puts("Key is unique!\n");
    Node newNode = malloc(sizeof(struct node));	
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    printf("Enter value: ");
    readline(buffer, 128, stdin);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;    
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", list->key, list->value);
    return list;
  }
  return list;
}


Node deleteEntry(char *buffer, Node *list){
  Node prev = NULL;
  Node cursor = *list;
  while(cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
	printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
	*list = cursor->next;
	return *list;
      }
      else{
	printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);  	
	cursor = cursor->next;
	prev = cursor->next;
     	return prev; 
      }
    }
    else{
      prev = cursor;
      cursor  = cursor->next;
      
    }
  }
  printf("Could not find an entry matching key \"%s\"!\n", buffer);
  return prev;
}    

void printDB(Node cursor){
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}
