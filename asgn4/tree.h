typedef struct s_node Node; // give s_node the new name Node by using typedef

// create a struct called s_node
// struct will have
// and int key
// int count
// typedef left Node struct
// typedef right Node struct
struct s_node {
    int key;
    int count;
    Node *left;
    Node *right;
};

typedef struct s_tree Tree; // give s_tree the new name Treeby unsing typedef

// create a struct calleds_tree
// struct will have 
// Node *root when initialzed
struct s_tree {
    Node *root;
};

Tree *tree_alloc(void); // Tree struct pointer function tree_alloc to allocate mem for Tree
void tree_add(Tree *tree, int key); // function to add a node to tree
void tree_print(Tree *tree); // function to print tree
void tree_free(Tree **p); // function to free mem of the tree

void tree_dump(Tree *tree); // function to debug tree 
