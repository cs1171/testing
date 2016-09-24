#ifndef btree
#define btree
#define NAME_LENGTH 20

typedef struct Node
{
  char first_name[NAME_LENGTH + 1];
  char last_name[NAME_LENGTH + 1];
  
  struct Node* right,*left;
}Node;

#endif
