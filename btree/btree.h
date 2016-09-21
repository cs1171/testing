#ifndef btree
#define btree
#define NAME_LENGTH 20

typedef struct
{
  Node *left,*right;

  char first_name[NAME_LENGTH + 1];
  char last_name[NAME_LENGTH + 1];
} Node;

Node *btreeAlloc();
void btreeFree(Node *btree);
void add(Node *n);
void remove(Node *n);
void printAll(Node *n);

#endif
