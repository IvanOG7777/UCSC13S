#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Purpose:      This is a recursive routine that prints a subtree
*               starting at a Node.  Usually it is not called directly,
*               but it is called by tree_print().
*
*               We use an "in-order" traversal of the tree.  This means
*               that the following order is followed:
*
*                   1. if node is NULL, then just return
*                   2. recurse to node->left
*                   3. print count and key of node
*                   4. recurse to node->right
*
*               When printing a Node, use the printf() format string
*               "%d %d\n".  The first number is the count of the Node;
*               the second number is the key of the Node.
*
* Paramter:     A pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_print_node(Node *node) {
// base case for recursive fucntion. Will break out of function and move back one once current nodes left or right nodes is null 
    if (node == NULL) {
        return;
    }

    tree_print_node(node->left); // recursively call this function on the left side
    printf("%d %d\n", node->count, node->key); // print nodes key and count
    tree_print_node(node->right); //recursively call this function on the right side
}

/*
* Purpose:      Print a Tree by calling tree_print_node() with the
*               root node of the tree.
*
*               The value of tree->root might be NULL, in which case
*               the tree is empty and nothing is printed.
*
* Parameter:    Pointer to the Tree.
*
* Returns:      nothing
*/
void tree_print(Tree *tree) {
// use the Trees root node and pass it into our print node helper function
    tree_print_node(tree->root); // calls the helper function from above
}

/*
* Purpose:      Allocate a new (empty) tree.
*
*               Remember to use assert() to check that calloc() returns 
*               a non-NULL pointer.
*
* Parameters:   none
*
* Returns:      Pointer to a new Tree.
*/
Tree *tree_alloc(void) {
	// when the function tree_alloc is called 
	// it will allocate memory for a new Tree struct and return the pointer to that address
	// using calloc we say we want to allocate enough space for 1 tree struct of size Tree
    return calloc(1, sizeof(Tree)); // return that new Tree pointer
}

// createNode helper function
// Purpose: to help the tree_add function create a new node to the tree.
// 	    Inside the function we create a new node asserting it to see if it was created fine
// 	    if everything is good we assign the newNodes key to the passed key, its count to 1, and its left and right Node pointer to NULL
// 	    Finally we return the address to this new node.
//
// Parameters: int key value
//
// return: Returns a pointer to an Address for a Node struct
Node *createNode(int key) {
    Node *newNode = calloc(1, sizeof(Node)); // use calloc to allocate memory for 1 Node struct, assign this to a Node newNode pointer
    assert(newNode != NULL); // checks if newNode is created sucesfully

    // if assert passes
    newNode->key = key; // we assign this newNodes key to the passed key
    newNode->count = 1; // set the count to 1 since its a new node
    newNode->left = NULL; // initlaize the left Node pointer to NULL
    newNode->right = NULL; // initlaize the right Node pointer to NULL

    return newNode; // return the a pointer to the Node struct in memory
}

/*
* Purpose:      This is the most important part of the Tree abstract
*               data type.
*
*               This function searches for the key, and then:
*
*                 - If the key is IN THE TREE, then increment the count
*                   for that key.
*
*                 - If the key is NOT IN THE TREE, then add it to the
*                   tree, and set its count to 1.
*
*               See Section 2.2 of the assignment PDF for more information.
*
* Parameters:   tree    - Pointer to the Tree.
*               key     - The value to add to the Tree.
*
* Returns:      nothing
*/


void tree_add(Tree *tree, int key) {
// check if Tree root value is NULL
    if (tree->root == NULL) {
        tree->root = createNode(key); // if it is we call createNode passing in the key for the function
				      // and set this new node to the Tree's root node
	return; // return early out of the function
    }
    // if tree already has a root node we do the bellow

    Node *current = tree->root; // initlaize a current pointer node to the trees root node. We will use current to traverse the tree

    // while our current node isnt null
    // we do the bellow
    while (current != NULL) {
        if (current->key == key) { // if current node key in the tree is the same as the passed key 
            current->count++; // add 1 to the count
            return; // return early out of the function
        }

        if (key < current->key) { // if the key is less than the current nodes key, we traverse to the left of the node
            if (current->left == NULL) { // if the current nodes left node pointer is NULL
                current->left = createNode(key); // set currents left Node pointer to a new node calling createNode and passing in the key
		return; // return early out of function
            } else {
                current = current->left; // else we keep traversing down the left side
            }
        } else if (key > current->key) { // if the key is greater that the current nodes key, we traverse the right side
            if (current->right == NULL) { // if current nodes right Node pointer is NULL
                current->right = createNode(key); // set currents left Node pointer to a new node calling createNode and passing in the key
		return; // return eatlyout of the function
            } else {
                current = current->right; // else keep traversing down the right side
            }
        }
    }
}


/*
* Purpose:      This is a recursive routine that frees a subtree
*               starting at a node.  Usually it is not called
*               directly, but it is called by tree_free().
*
*               We use a "postorder" traversal of the tree to free all
*               of the nodes of the tree.  This means that the
*               following order is followed:
*
*                  1. if node is NULL, then just return.
*                  2. recurse to node->left
*                  3. recurse to node->right
*                  4. free the node
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_free_node(Node *node) {

// base case for our recursive function
    if (node == NULL) { // if node is NULL
	    return; // return out of the function
    }

    tree_free_node(node->left); // traverse down the left side
    tree_free_node(node->right); // traverse down the right side

    free(node); // use free to free the memory of where the node is stored
}

/*
* Purpose:      Free a Tree that had been allocated by tree_alloc().
*
*                 1. If the tree pointer *p already is NULL, then the
*                    tree already has been freed, and so just return.
*                 2. Free the nodes of the tree by calling tree_free_node()
*                    with the root of the tree.
*                 3. Free the tree node by calling free(*p);
*                 4. Set the tree pointer to NULL:  *p = NULL;
*
* Parameter:    p  -  Pointer to a pointer to the node to be freed.
*/
void tree_free(Tree **p) {
// checks if the addres of an allocated tree (p) is NULL or  if the struct Tree struct within that address is NULL
    if (p == NULL || *p == NULL) {
	    return; // if true we return out of function
    }

    // we we pass the above we move down bellow

    tree_free_node((*p)->root); // call the tree_free_node on the trees root
				// will recursivally run down the tree freeing all nodes

    free(*p); // finally free memory of Tree struct itself

    *p = NULL; // extra sanitation set the address of where the struct was to NULL
}

/*
* Purpose:      Recursive routine for printing a debugging dump of a
*               binary tree.  Usually this routine is not called
*               directly, but it is called by tree_dump().
*
* Parameters:   node    - pointer to the root node of the tree
*               level   - indentation level
*               prefix  - char to print first:  <, /, or \
*
* Returns:      nothing
*/
void tree_dump_node(Node *node, int level, char prefix) {
    if (node) {
        tree_dump_node(node->right, level + 1, '/');
        printf("%*c %d (x%d)\n", 4 * level + 1, prefix, node->key,
                node->count);
        tree_dump_node(node->left, level + 1, '\\');
    } else {
        printf("%*c NULL\n", 4 * level + 1, prefix);
    }
}

/*
* Purpose:      Print debugging output by calling tree_dump_node() with
*               the root of the tree.
*
*               The result of calling this routine is a text-based image of
*               the tree that is printed sideways with the root on the
*               left.  For example, this is the debugging output for a tree
*               with 314 at the root, 76 to the left, and 95064 to the
*               right.  (Rotate your head to the left to see it with the
*               root at the top.)
*
*                                 / NULL
*                             / 95064 (x2)
*                                 \ NULL
*                         < 314 (x1)
*                                 / NULL
*                             \ 76 (x3)
*                                 \ NULL
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_dump(Tree *tree) {
    assert(tree);
    tree_dump_node(tree->root, 0, '<');
}

