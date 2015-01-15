/**
 * @file
 */

/**
 * Node that contains keys and values
 */

typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Tree;


extern Tree cursor;
extern Tree list;

/**
 * Makes the tree consisting of keys and values
 * @param keybuf Pointer to the key to be inserted
 * @param valbuf Pointer to the value to be inserted
 * @param tree The tree to be made
 * @return newNode The tree made
 */

Tree makeTree(char *keybuf, char *valbuf, Tree tree);


/**
 * Makes a database into a tree structure
 * @param database The file to make into a tree
 * @param tree The tree to be made
 * @return list The made tree
 */

Tree makeDB(FILE *database, Tree tree);

/**
 * Prints the string and the first key and value from tree 
 * @param string The string to be printed
 * @param tree The tree from which the key and value is printed
 */

void printEntry(const char *string, Tree tree);

/**
 * Searches the tree for the key and prints the key and the value
 * @param tree The tree to be searched
 * @param key the key to search for
 * @return cursor if key is found, else NULL
 */
Tree findKey(Tree tree, char *key);

/**
 * Searches the tree for the key and let you update the value linked to the key
 * @param key The key to search for
 * @param value The value to be updated
 * @param tree The tree to search
 * @return cursor The updated cursor
 */

Tree updateValue(char *key, char *value, Tree tree);

/**
 * Searches the tree for a key, if the key does not exist, the function prompts 
 * you to input a value and it creates a new entry in the tree with the key and  * value
 * @param key The key to search for
 * @param value The value to be inserted
 * @return tree The updated tree
 */
Tree insertEntry(char *key, char *value, Tree tree);

/**
 * Compares to values and returns the highest one
 * @param tree The tree to search in
 * @return cursor The value that is the highest
 */
Tree maxValue(Tree tree);

/**
 * Compares to values and returns the lowest one
 * @param tree The tree to search in
 * @return cursor The value that is the lowest
 */
Tree minValue(Tree tree);

/**
 * Deletes the key and its value from the tree, if it exist
 * @param keybuf A pointer to the key to be deleted
 * @param tree The tree to search in
 */
void delete(char *keybuf, Tree tree);

Tree deleteEntry(char *key, Tree *tree);

/**
 * Prints the entries in the tree
 * @param tree The tree to be printed
 */

/**
 * Prints the database
 * @param tree The tree from which the database is found
 */
void printDB(Tree tree);

/**
 * Frees the tree
 * @param tree The tree to be freed
 */
void FreeTree(Tree tree);
