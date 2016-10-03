#ifndef btree
#define btree
#define NAME_LENGTH 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

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
void removeEmployee(char * name1, char * name2);
Node * addToTree(Node * node, Node * current);
Node * newNode(Node * current);
void printTree(Node * tree);
void freeTree(Node * tree);

#endif
