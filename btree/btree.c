#include "btree.h"

char * filename = "pms.txt";

void checkExisting(char * name1, char * name2)
{
  FILE * file = fopen(filename, "r");
  char * tfname = (char *) malloc(sizeof(21));
  char * tlname = (char *) malloc(sizeof(21));
  int duplicate = 0;
  
  // catch any file errors
  if(!file)
    {
      printf("%s\n", strerror(errno));
      exit(1);
    }

  // check if employee exists in file
  while(1)
    {
      if(feof(file))
	break;
      
      fgets(tfname, 21, file);
      fgets(tlname, 21, file);
      
      if(strcmp(tfname,name1) == 0)
	{
	  if(strcmp(tlname,name2) == 0)
	    {
	      printf("Employee already in system.\n\n");
	      duplicate = 1;
	    }
	}
    }

  // if no duplicate
  if(duplicate == 0)
    {
      printf("%s %s", name1, name2);
      addToFile(name1,name2);
    }

  free(tfname);
  free(tlname);
  fclose(file);
}

// add employee to file
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

// test all functions
int test_everything()
{
  Node * tree = NULL;
  tree = populate_tree(tree);
  printf("First name\t\tLast name\n");
  printf("---------------------------------\n");
  printTree(tree);
  freeTree(tree);
}

// read from file and pass to tree creator
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
  bstFile(node);
  return node;
}

// add nodes to binary tree
Node * addToTree(Node * tree, Node * current)
{
  // if tree does not exist
  if(tree == NULL)
    {
      tree = newNode(current);
    }

  // left/right branch control
  // checks first name. if less adds to left, if greater
  // adds to right branch. if equal checks last name,
  // then adds to left or right branch
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

// node creation
Node * newNode(Node * current)
{
  Node * node = pmalloc;
  memcpy(node->first_name,current->first_name,20);
  memcpy(node->last_name,current->last_name,20);
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

// frees nodes from memory
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

// remove employee from file
void removeEmployee(char * name1, char * name2)
{
  FILE * file = fopen(filename, "r");
  FILE * tempFile = fopen("temp.txt", "a+");
  
  char * tfname = (char *) malloc(sizeof(21));
  char * tlname = (char *) malloc(sizeof(21));
  
  // catch any file errors
  if(!file || !tempFile)
    {
      printf("%s\n", strerror(errno));
      exit(1);
    }

  // check if employee exists in file
  while(1)
    {
      if(feof(file))
	break;
      
      fgets(tfname, 21, file);
      fgets(tlname, 21, file);
      
      if(strcmp(tfname,name1) == 0)
	{
	  if(strcmp(tlname,name2) == 0)
	    {
	      continue;
	    }
	}
      printf("Transferring...\n");
      fputs(tfname, tempFile);
      fputs(tlname, tempFile);
    }

  fclose(file);
  fclose(tempFile);
  unlink(filename);
  rename("temp.txt", filename);
  
  free(tfname);
  free(tlname);
}
