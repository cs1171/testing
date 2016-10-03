#include "btree.h"

int main()
{
  char sentinel = '5';
  
  do
    {
      printf("Welcome to ACME Solutions Personnel Management System\n");
      printf("\nPlease select one of the following options:\n");
      printf("1: Add employee to list\n");
      printf("2: Remove employee from list\n");
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
	  printf("Please enter employee first name:\n");
	  getchar();
	  fgets(name1, 21, stdin);
	  printf("Please enter employee last name:\n");
	  fgets(name2, 21, stdin);

	  printf("Deleting employee...\n");
	  removeEmployee(name1, name2);
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
