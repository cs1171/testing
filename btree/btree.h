#ifndef btree
#define btree
#define NAME_LENGTH 20

typedef struct Node
{
  char first_name[NAME_LENGTH + 1];
  char last_name[NAME_LENGTH + 1];
  
  struct Node* right,*left;
}Node;

#define pmalloc (Node *) malloc(sizeof(Node));
Node * populate_tree(Node * tree);
void checkExisting(char * first_name, char * last_name);
void addToFile(char * first_name, char * last_name);
Node * addToTree(Node * node, Node * current);
Node * newNode(Node * current);
void printTree(Node * tree);
void freeTree(Node * tree);

#endif
