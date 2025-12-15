#include "tree.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  unique NUM NUM NUM ...       (normal output)\n");
    printf("        unique -d NUM NUM NUM ...    (debugging output)\n");
    exit(0);
}

// Purpose: To check if passed string of numbers has a character in it. If it does we print message and exit early if it doesnt we continue as normally.
// Parameters: a string of characters
// return nothing (void function)
void check_number(const char *s) { // pass in char array string
// for loop goes through each char in the string until the null terminator
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) { // if char at s[i] is not a number we
		print_usage(); // we call print_usage
		return; // exit the function early;
        }
    }
}


int main(int argc, char **argv) {

 Tree *tree = tree_alloc(); // assign memory for a new Tree struct using tree_alloc(). Tree *tree points to this Tree struct address
    bool wasDSeen = false; // bool to check is '-d' was seen. Initially set it to fasle;

    // for loop to loop through all the arguments in that will be passed
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-d") == 0) { // check if '-d' was one of these arguments
					 // if it is we note that we saw it by setting wasDSeen to true
            wasDSeen = true;
            continue; // continue to the next index
        }

        check_number(argv[i]); // call the check_number function on the current argument to see if it consists of numbers only

        tree_add(tree, atoi(argv[i])); // if we pass the number checker we add that value to the tree
    }

    // after we loop through all the arguments
    // we check if '-d' was seen
    if (wasDSeen == true) { // if it was
        tree_dump(tree); // we call tree dump and pass in the tree for it
    } else { // if node
        tree_print(tree); // print the tree normally
    }

    tree_free(&tree); // free all nodes and tree struct from memory

    return 0;
}
