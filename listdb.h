/**
 *@file
 */

typedef struct node *Node;

extern Node cursor;

extern Node list;

/**
 * Reads a line of text from a file
 * @param dest Destination of read line
 * @param n Maximum length of a line
 * @param source Source of the line.
 */

void readline(char *dest, int n, FILE *source);

Node makeDB(char *buffer, FILE *database, Node list);

void printEntry(const char*n, Node cursor);

Node findKey(Node cursor, char*buffer);

Node updateValue(char *buffer, Node cursor);

Node insertEntry(char *buffer, Node list, Node cursor);

Node deleteEntry(char *buffer, Node *list);

void printDB(Node cursor);

