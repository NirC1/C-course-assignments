#ifndef ORG_TREE_H
#define ORG_TREE_H

#define MAX_FIELD 100
#define MAX_POS   20

typedef struct Node {
    char first[MAX_FIELD];
    char second[MAX_FIELD];
    char fingerprint[MAX_FIELD];
    char position[MAX_POS];
    struct Node *left;          /* Boss’s left child (Left Hand)       */
    struct Node *right;         /* Boss’s right child (Right Hand)     */
    struct Node *supports_head; /* Head of support crew linked list    */
    struct Node *next;          /* Next node in a support crew list    */
} Node;

typedef struct {
    Node *boss;
    Node *left_hand;
    Node *right_hand;
} Org;

/* Read a clean file and build the organization tree. */
Org build_org_from_clean_file(const char *path);

/* Print the organization in the specified traversal order. */
void print_tree_order(const Org *org);

/* Free the entire organization tree and its support lists. */
void free_org(Org *org);

#endif /* ORG_TREE_H */
