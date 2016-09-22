#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "btree.h"
#define pmalloc (struct Node *) malloc(sizeof(struct Node));

void populate_tree(struct Node ** tree, char *filename);

int main(void)
{
  struct Node *tree = NULL;
  populate_tree(&tree, "names.txt");
  //printf("First name   Last name   Age\n");
  //printf("----------------------------\n");
  //printTree(tree);
  //freeTree(tree);
}

void populate_tree(struct Node ** tree, char * filename)
{
  FILE *file = fopen(filename, "rt");
  struct Node * leaf = NULL;
  struct Node * current = NULL;
  
  // catch any file errors
  if(!file)
    {
      printf("Error opening file\n%s\n", strerror(errno));
      exit(1);
    }

  // reading names
  current = pmalloc;
  while(fscanf(file, "%20s", current->first_name) > 0)
    {
      fscanf(file, "%20s", current->last_name);

      // testing fscanf
      // printf("%s %s\n", current->first_name, current->last_name);

      
    }
}
