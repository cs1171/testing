#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "btree.h"

char * filename = "pms.txt";

int main()
{
  char sentinel = '1';
  
  do
    {
      printf("Welcome to ACME Solutions Personnel Management System\n");
      printf("\nPlease select one of the following options:\n");
      printf("1: Add employee to list\n");
      printf("2: Remove employee to list\n");
      printf("3: List all employees\n");
      printf("0: Exit program\n");
      
      sentinel = getchar();
      char * name1 = (char *) malloc(sizeof(21));
      char * name2 = (char *) malloc(sizeof(21));
      Node * tree = NULL;
      
      switch(sentinel)
	{
	case '0':
	  getchar();
	  printf("Thank you, goodbye.\n");
	  sleep(2);
	  break;
	  
	case '1':
	  printf("Please enter employee first name:\n");
	  getchar();
	  fgets(name1, 21, stdin);
	  printf("Please enter employee last name:\n");
	  fgets(name2, 21, stdin);

	  printf("Checking for duplicate name...\n");
	  checkExisting(name1, name2);
	  break;

	case '2':
	  break;

	case '3':
	  getchar();
	  tree = populate_tree(tree);
	  printTree(tree);
	  printf("\n");
	  freeTree(tree);
	  free(name1);
	  free(name2);
	  break;

	default:
	  break;
	}
    }while(sentinel != '0');
}

void checkExisting(char * first_name, char * last_name)
{
  FILE *file = fopen(filename, "r");
  char * tfname = (char *) malloc(sizeof(21));
  char * tlname = (char *) malloc(sizeof(21));
  
  // catch any file errors
  if(!file)
    {
      printf("%s\n", strerror(errno));
      exit(1);
    }


  printf("Looking for: %s %s", first_name, last_name);
  while(fgets(tfname, 21, file) != EOF)
    {
      fgets(tlname, 21, file);
      printf("TEST 1: %s\t%s\n", tfname, tlname);
      int test = strcmp(tfname,first_name);
      printf("Compare value: %d\n", test);
      if(strcmp(tfname,first_name) == 0)
	{
	  printf("MATCHING");
	  if(strcmp(tlname,last_name) == 0)
	    {
	      printf("Employee already in system.\n\n");
	      break;
	    }
	  else
	    {
	      // addToFile(first_name,last_name);
	      continue;
	    }
	}
      else
	{
	  // addToFile(first_name,last_name);
	  continue;
	}
    }
}

void addToFile(char * first_name, char * last_name)
{
  FILE * file = fopen(filename, "a");

  // catch any file errors
  if(!file)
    {
      printf("%s\n", strerror(errno));
      exit(1);
    }
  printf("Adding employee to file...\n\n");
  fprintf(file, "%s", first_name);
  fprintf(file, "%s", last_name);
  fclose(file);
}

int test_everything()
{
  Node * tree = NULL;
  tree = populate_tree(tree);
  printf("First name\t\tLast name\n");
  printf("---------------------------------\n");
  printTree(tree);
  freeTree(tree);
}

Node * populate_tree(Node * node)
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

  fclose(file);
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
