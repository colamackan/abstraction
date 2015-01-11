
typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Tree;


extern Tree cursor;
extern Tree list;

Tree makeTree(char *keybuf, char *valbuf, Tree tree);

//makes a database into a tree structure
Tree makeDB(FILE *database, Tree tree);

//prints the string and the first key and value from tree 
void printEntry(const char *string, Tree tree);

//searches the tree for the key and prints the key and the value
Tree findKey(Tree tree, char *key);

//searches the tree for the key and let you update the value linked to the key
Tree updateValue(char *key, char *value, Tree tree);

//searches the tree for a key, if the key does not exist, the function prompts you to input a value and it creates a new entry in the tree with the key and value
Tree insertEntry(char *key, char *value, Tree tree);

Tree maxValue(Tree tree);
Tree minValue(Tree tree);
void delete(char *keybuf, Tree tree);

// deletes the entry with key, from tree if it exists
Tree deleteEntry(char *key, Tree *tree);

//prints the entrys in tree
void printDB(Tree tree);

//free everything in tree
void FreeTree(Tree tree);
