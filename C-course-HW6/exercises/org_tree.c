#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "org_tree.h"

/* Create a node with the given field values. */
static Node* create_node(const char *first, const char *second,
                         const char *fingerprint, const char *position) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        printf("Error allocating memory\n");
        return NULL;
    }
    strncpy(n->first, first, MAX_FIELD - 1);
    n->first[MAX_FIELD - 1] = '\0';
    strncpy(n->second, second, MAX_FIELD - 1);
    n->second[MAX_FIELD - 1] = '\0';
    strncpy(n->fingerprint, fingerprint, MAX_FIELD - 1);
    n->fingerprint[MAX_FIELD - 1] = '\0';
    strncpy(n->position, position, MAX_POS - 1);
    n->position[MAX_POS - 1] = '\0';
    n->left = n->right = NULL;
    n->supports_head = NULL;
    n->next = NULL;
    return n;
}

Org build_org_from_clean_file(const char *path) {
    Org org;
    org.boss = org.left_hand = org.right_hand = NULL;

    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Error opening file: %s\n", path);
        return org;
    }
    char line[256];
    char first[MAX_FIELD], second[MAX_FIELD];
    char fp[MAX_FIELD], position[MAX_POS];

    Node *sr_head = NULL, *sr_tail = NULL;
    Node *sl_head = NULL, *sl_tail = NULL;

    while (1) {
        if (!fgets(line, sizeof(line), f)) break;
        if (sscanf(line, "First Name: %[^\n]", first) != 1) break;
        if (!fgets(line, sizeof(line), f)) break;
        if (sscanf(line, "Second Name: %[^\n]", second) != 1) break;
        if (!fgets(line, sizeof(line), f)) break;
        if (sscanf(line, "Fingerprint: %[^\n]", fp) != 1) break;
        if (!fgets(line, sizeof(line), f)) break;
        if (sscanf(line, "Position: %[^\n]", position) != 1) break;
        fgets(line, sizeof(line), f); /* blank line */

        Node *node = create_node(first, second, fp, position);
        if (!node) continue;
        if (strcmp(position, "Boss") == 0) {
            if (!org.boss) org.boss = node;
            else free(node);
        } else if (strcmp(position, "Right Hand") == 0) {
            if (!org.right_hand) org.right_hand = node;
            else free(node);
        } else if (strcmp(position, "Left Hand") == 0) {
            if (!org.left_hand) org.left_hand = node;
            else free(node);
        } else if (strcmp(position, "Support Right") == 0) {
            if (!sr_head) sr_head = sr_tail = node;
            else {
                sr_tail->next = node;
                sr_tail = node;
            }
        } else if (strcmp(position, "Support Left") == 0) {
            if (!sl_head) sl_head = sl_tail = node;
            else {
                sl_tail->next = node;
                sl_tail = node;
            }
        } else {
            free(node);
        }
    }
    fclose(f);

    /* Attach children and support lists */
    if (org.boss) {
        org.boss->left = org.left_hand;
        org.boss->right = org.right_hand;
    }
    if (org.left_hand) {
        org.left_hand->supports_head = sl_head;
    }
    if (org.right_hand) {
        org.right_hand->supports_head = sr_head;
    }
    return org;
}

/* Print a single node (4 lines + blank line). */
static void print_node(const Node *node) {
    if (!node) return;
    printf("First Name: %s\n", node->first);
    printf("Second Name: %s\n", node->second);
    printf("Fingerprint: %s\n", node->fingerprint);
    printf("Position: %s\n\n", node->position);
}

void print_tree_order(const Org *org) {
    if (!org) return;
    if (org->boss) {
        print_node(org->boss);
    }
    if (org->left_hand) {
        print_node(org->left_hand);
        Node *curr = org->left_hand->supports_head;
        while (curr) {
            print_node(curr);
            curr = curr->next;
        }
    }
    if (org->right_hand) {
        print_node(org->right_hand);
        Node *curr = org->right_hand->supports_head;
        while (curr) {
            print_node(curr);
            curr = curr->next;
        }
    }
}

/* Recursively free a node and its descendants. */
static void free_node(Node *node) {
    if (!node) return;
    Node *curr = node->supports_head;
    while (curr) {
        Node *next = curr->next;
        free_node(curr);
        curr = next;
    }
    free_node(node->left);
    free_node(node->right);
    free(node);
}

void free_org(Org *org) {
    if (!org) return;
    free_node(org->boss);
    org->boss = org->left_hand = org->right_hand = NULL;
}
