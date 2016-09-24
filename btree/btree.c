#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "btree.h"
#define pmalloc (Node *) malloc(sizeof(Node));

Node * populate_tree(Node * tree, char *filename);
Node * addToTree(Node * node, Node * current);
Node * newNode(Node * current);
void printTree(Node * tree);
void freeTree(Node * tree);

int main(void)
{
  Node * tree = NULL;
  tree = populate_tree(tree, "names.txt");
  printf("First name\t\tLast name\n");
  printf("---------------------------------\n");
  printTree(tree);
  freeTree(tree);
}

Node * populate_tree(Node * node, char * filename)
{
  FILE *file = fopen(filename, "rt");
  Node * current = NULL;
  
  // catch any file errors
  if(!file)
    {
      printf("Error opening file\n%s\n", strerror(errno));
      exit(1);
    }
  current = pmalloc;
  // reading names
  while(fscanf(file, "%20s", current->first_name) > 0)
    {
      fscanf(file, "%20s", current->last_name);
      // testing fscanf
      // printf("%s %s\n", current->first_name, current->last_name);
      node = addToTree(node,current);
    }

  return node;
}

Node * addToTree(Node * tree, Node * current)
{
  if(tree == NULL)
    {
      tree = newNode(current);
    }

  else if(strcmp(current->first_name,tree->first_name) < 0)
    {
      tree->left = addToTree(tree->left,current);
    }
  else if(strcmp(current->first_name,tree->first_name) > 0)
    {
      tree->right = addToTree(tree->right,current);
    }
  else if(strcmp(current->first_name,tree->first_name) == 0)
    {
      if(strcmp(current->last_name,tree->last_name) < 0)
	{
	  tree->left = addToTree(tree->left,current);
	}
      else if(strcmp(current->last_name,tree->last_name) > 0)
	{
	  tree->right = addToTree(tree->right,current);
	}
    }
  return tree;
}

Node * newNode(Node * current)
{
  Node * node = pmalloc;
  memcpy(node->first_name,current->first_name,20);
  memcpy(node->last_name,current->last_name,20);
  // printf("%s %s\n", node->first_name, node->last_name);
  node->left = NULL;
  node->right = NULL;
  return node;
}

// will print tree in-order
void printTree(Node * tree)
{
  if(tree == NULL)
    {
      return;
    }
  printTree(tree->left);
  printf("%s %s\n", tree->first_name, tree->last_name);
  printTree(tree->right);
}

void freeTree(Node * tree)
{
  if(tree == NULL)
    {
      return;
    }
  freeTree(tree->left);
  free(tree);
  freeTree(tree->right);
}
