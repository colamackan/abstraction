#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Tree;

Tree cursor;
Tree list = NULL;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void readInput(const char *n,char *buffer){
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts(n);
}

Tree makeTree(char *keybuf, char *valuebuf, Tree newNode){
  if(newNode == NULL){ 
    // if the pointer is empty it makes a new entry
    Tree newNode = malloc(sizeof(struct node));  
    newNode->key = malloc(strlen(keybuf) + 1);
    strcpy(newNode->key, keybuf);
    newNode->value = malloc(strlen(valuebuf) + 1);
    strcpy(newNode->value, valuebuf);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }
  else if (strcmp(keybuf, newNode->key) > 0){
    //if the key is smaller than the key you want to insert
    newNode->right = makeTree(keybuf, valuebuf, newNode->right);
  } 
  else if(strcmp(keybuf, newNode->key) < 0){
    //if the key is bigger than the key you wnat to insert
    newNode->left = makeTree(keybuf, valuebuf, newNode->left);
  }
  return newNode;
  
}

Tree makeDB(FILE *database, Tree list){
  //makes a database in tree-form
  char keybuf[128];
  char valuebuf[128];
  readline(keybuf, 128, database);
  readline(valuebuf, 128, database);
  list = makeTree(keybuf, valuebuf, list);
  return list;
  
}

void printEntry(const char *n, Tree cursor){
  puts(n);
  printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
}

Tree findKey(Tree cursor, char *buffer){
  while(!(cursor == NULL)){
    //it searshes as long as it hasn't reached the end of the tree
    if(strcmp(buffer, cursor->key) == 0){
      printEntry("found entry:", cursor);
      return cursor;
      break;
    }
    else{ 
      //compares if the key we're searching for is bigger or smaller than the existing key
      if(strcmp(cursor->key, buffer) < 0) {
	cursor = cursor->right;	
      }
      else{
	cursor =  cursor->left;	
      }
    }
  }
  return NULL;
}
/*
  ändra så att det blir en valbuf och keybuf så värderna sätts i mainfunktionen
*/
Tree updateValue(char *buffer, char *valbuf, Tree cursor){
  //searches for the entry it wants to update, as long as it hasn't reached the end of the tree
  free(cursor->value);
  cursor->value = malloc(strlen(valbuf) + 1);
  strcpy(cursor->value, valbuf);
  puts("Value inserted successfully!");
  return cursor;
}
void Fmax(Tree cursor){
  Tree temp = NULL;
  while(cursor->right != NULL){
    temp = cursor;
    cursor = cursor->right;
  }
  while(cursor->left != NULL){
    temp = cursor;
    cursor = cursor->left;
  }
  if(cursor->right != NULL){
    Fmax(cursor);
  }
  if(temp->right != NULL){
    if(temp->right->key == cursor->key){
      free(cursor->value);
      free(cursor->key);
      free(cursor);
      temp->right = NULL;
    }
  }
  else{
    free(cursor->value);
    free(cursor->key);
    free(cursor);
    temp->left = NULL;
  }
}

void FreeTree(Tree list){
  while(list != NULL){
    if(list->right != NULL){
      Fmax(list);
    }
    else if(list->left != NULL){
      Fmax(list);
    }
    else{
      free(list->value);
      free(list->key);
      free(list);
      list = NULL;
      break;
    }
  }
}

Tree insertEntry(char *buffer, char *valbuf, Tree list){  
  //if cursor is NULL the key is unique and we can make a new entry
  list = makeTree(buffer, valbuf, list);
  puts("\nEntry inserted successfully:");
  printf("key: %s\nvalue: %s\n", buffer, valbuf);
  return list;
}

Tree maxValue(Tree cursor){
  Tree temp = NULL;
  while(cursor->right != NULL){
    temp = cursor;
    cursor = cursor->right;
  }  
  if(temp != NULL)
    temp->right = cursor->left;
  return cursor;
}

Tree minValue(Tree cursor){
  Tree temp = NULL;
  while(cursor->left != NULL){
    temp = cursor;
    cursor = cursor->left;
  }  
  if(temp != NULL)
    temp->left = cursor->right;
  return cursor;
}


void delete(char *buffer, Tree cursor){
  Tree temp = NULL;
  if(cursor != NULL) {
    if(strcmp(cursor->key, buffer) == 0) {
      if(cursor->right == NULL){
	if(cursor->left == NULL){ //ifall det bara finns en nod i trädet
	  FreeTree(cursor);
	}		
	else if(cursor->left->right != NULL){	   
	  temp = maxValue(cursor->left);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
	else{
	  temp = cursor->left;
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);	  
	  cursor->left = temp->left;
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
      }
      else if(cursor->left == NULL){
	if(cursor->right->left != NULL){
	  temp = minValue(cursor->right);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
	else{
	  temp = cursor->right;
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);	  
	  cursor->right = temp->right;
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
      }
      else if(cursor->right != NULL){
	if(cursor->right->left != NULL){
	  temp = minValue(cursor->right);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
	else{
	  temp = cursor->right;
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);	  
	  cursor->right = temp->right;
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
      }
      else if(cursor->left != NULL){
	if(cursor->left->right != NULL){	   
	  temp = maxValue(cursor->left);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}

	else{
	  temp = cursor->left;
	  free(cursor->value);
	  cursor->value = malloc(strlen(temp->value) + 1);
	  strcpy(cursor->value, temp->value);
	  free(cursor->key);
	  cursor->key = malloc(strlen(temp->key) + 1);
	  strcpy(cursor->key, temp->key);	  
	  cursor->left = temp->left;
	  free(temp->value);
	  free(temp->key);
	  free(temp);
	  temp = NULL;
	}
      }
    }
    else if((strcmp(buffer, cursor->key)) <= 0){
      if(cursor->left != NULL){
	temp = cursor->left;
	if(strcmp(buffer, cursor->left->key) == 0){
	  if(temp->left == NULL && temp->right == NULL){
	    free(temp->value);
	    free(temp->key);
      	    free(temp);
	    cursor->left = NULL;
	  }
	}
      }
      delete(buffer, cursor->left);
	  
    }
    else{
      if(cursor->right != NULL){
	temp = cursor->right;
	if(strcmp(buffer, cursor->right->key) == 0){
	  if(temp->left == NULL && temp->right == NULL){
	    free(temp->value);
	    free(temp->key);
	    free(temp);
	    cursor->right = NULL;
	  }
	}
      }
      delete(buffer, cursor->right);
    }
  }
  cursor = NULL;
}

Tree deleteEntry(char *buffer, Tree *list){
  Tree cursor = *list;
  delete(buffer, cursor);
  if(cursor == NULL){ //if it does not exists
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
    return *list;
  }
  puts("Entry was deleted sucsessfully");
  return cursor;
}   

void printDB(Tree cursor){
  if(!(cursor == NULL)){
    puts(cursor->key);
    puts(cursor->value);
  }
  if(cursor->left != NULL) {
    printDB(cursor->left);
  }
  if(cursor->right != NULL){
    printDB(cursor->right);
  }
}



