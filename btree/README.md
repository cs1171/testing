For this project the task was to create a program with an interface in which the user
can add, remove, and print employees. The employees will be sorted into a binary search
tree.

For my implementation I have 3 files: The main file which runs the interface and allows
users to select actions, a btree.c file which contains all the functions, and the btree.h
which is a header file for all functions and Node definition. To make it easier to show
the functionality, I have included a text file with a few names. This file is hard-coded
but there are checks to make sure it exists.

Because the program is going to be reading/writing to a file and making comparisons
to determine where each new leaf to the tree goes, I included several libraries in
the header file to make those tasks possible (or easier).



The following functions are present within btree.c:

checkExisting function - This is designed to check if the employee already exists in the
file. If it does, then a duplicate flag will be set and the employee will not be added.
If the duplicate flag is not set, then the user gets added with a call to addToFile.

addToFile - This function takes the first and last name of an employee and appends them
to the database file.

populateTree - This function starts the tree population process. It opens the database
file and creates a null node for the root. The program then scans through the file and
collects the first then last name of each employee, which gets passed to the addToTree
function. When complete, it returns the root.

addToTree - This function takes two Nodes (existing tree and current node). There is a
check to make sure if the root is null it will be given the current node values. If
the tree is not empty, then the sorting process begins. Strcmp is used to check if
the current first name is less than the tree's first name. If it is, then it is added
to the left branch. The next check is for greater than, which does the same but to the
right branch. If the first name turns out to be equal, then the last name is checked.
If the last name is less then it goes right, if greater it goes left. Duplicates are not
allowed to be added to the tree through the checkExisting function.

newNode - this function is used for node creation. It just copies first and last name
into the node and sets the right and left branches to NULL.

printTree - This function will print out the tree in-order. It does this by recursively
calling the left branch until it reaches NULL, then prints out the node values until it
reaches the root. Then it traverses through the right branch. This results in printing
all names in lexographical order.

freeTree - Similar to printTree in function, instead of printing the leaf values this
will free the memory used for each node (destroying the tree).

removeEmployee - This function will take the first and last name of an employee the
user wishes to remove, and will check them against the existing file. If there is a match,
then the non-matching names will be copied over to a temp file. When done, the temp
file is renamed and the tree is recreated.


The following information is for the code in main.c:
The main driver file controls the user interface by using a do-while loop (set to true)
and a sentinel value. The interface presents a list of options: 1 for add employee,
2 to remove employee, 3 to list all employees, and 0 to exit from the program. A switch
case is used to determine what action to take when a user enters a menu item. Whenever
a user selects one of the menu items, the sentinel value is updated (so if they select
0 for exit, it will cause the loop to break and end the program). Any other value input
by the user will simply continue the loop.


The following information is about my Makefile:
Since I have 3 separate files, my Makefile will link both c files with the header file
into an object file, then link both objects into the executable. There is also a make
clean option to remove all files that are created by the make process. Make all is
the default option.