#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "org_tree.h"
#define FP_LEN 9

/**
 * Helper: Reads the cipher file and converts 9 lines of binary strings to integers.
 * Returns 1 on success, 0 on failure.
 */
static int read_cipher(const char *path, int *cipher_out) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Error opening file: %s\n", path);
        return 0;
    }
    
    char line[64];
    for (int i = 0; i < FP_LEN; i++) {
        if (!fgets(line, sizeof(line), f)) {
            cipher_out[i] = 0;
        } else {
            int val = 0;
            for (int k = 0; line[k]; k++) {
                if (line[k] == '0' || line[k] == '1') {
                    val = (val << 1) | (line[k] - '0');
                } else if (line[k] == '\n' || line[k] == '\r') {
                    break;
                }
            }
            cipher_out[i] = val;
        }
    }
    fclose(f);
    return 1;
}

/**
 * Helper: Checks if a node's fingerprint matches the cipher using a specific mask and operation.
 * op_type: 0 for XOR, 1 for AND.
 * Returns 1 if match, 0 otherwise.
 */
static int check_node(const Node *node, const int *cipher, int mask, int op_type) {
    if (!node) return 0;
    
    for (int i = 0; i < FP_LEN; i++) {
        unsigned char plain = (unsigned char)node->fingerprint[i];
        int val = (op_type == 0) ? (plain ^ mask) : (plain & mask);
        
        if (val != cipher[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Helper: Searches the organization tree for a matching fingerprint.
 * Returns the matching Node pointer or NULL if no match found.
 */
static const Node* find_decrypted_match(const Org *org, const int *cipher, int mask, int op_type) {
    if (check_node(org->boss, cipher, mask, op_type)) return org->boss;
    if (check_node(org->left_hand, cipher, mask, op_type)) return org->left_hand;
    if (check_node(org->right_hand, cipher, mask, op_type)) return org->right_hand;
    
    if (org->left_hand) {
        Node *curr = org->left_hand->supports_head;
        while (curr) {
            if (check_node(curr, cipher, mask, op_type)) return curr;
            curr = curr->next;
        }
    }
    
    if (org->right_hand) {
        Node *curr = org->right_hand->supports_head;
        while (curr) {
            if (check_node(curr, cipher, mask, op_type)) return curr;
            curr = curr->next;
        }
    }
    
    return NULL;
}

static void print_success(int mask, char *op, char* fingerprint, char* First_Name, char* Second_Name)
{
    printf("Successful Decrypt! The Mask used was mask_%d of type (%s) and The fingerprint was %.*s belonging to %s %s\n",
                       mask, op, FP_LEN, fingerprint, First_Name, Second_Name);
}

static void print_unsuccess()
{
    printf("Unsuccesful decrypt, Looks like he got away\n");
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <clean_file.txt> <cipher_bits.txt> <mask_start_s>\n", argv[0]);
        return 0;
    }
    
    // TODO: read the input files
    const char *clean_file  = argv[1];
    const char *cipher_file = argv[2];
    int start_mask          = (int)strtol(argv[3], NULL, 10);
    int cipher[FP_LEN] = {0};


    // TODO: build the organization
    Org org = build_org_from_clean_file(clean_file);
    if (!org.boss && !org.left_hand && !org.right_hand) {
        // Error message printed by build function usually, but check if we need to print specific file error
        // The instructions say "In case of file opening failure - print ... Error opening file: ..."
        // build_org_from_clean_file is expected to handle that. 
        // For cipher file we must handle it here.
        return 0;
    }
    
    // Read cipher
    if (!read_cipher(cipher_file, cipher)) {
        free_org(&org);
        return 0;
    }
    

    // TODO: attempt to decrypt the file
    int found = 0;
    int found_mask = 0;
    char *found_op_str = NULL;
    const Node *match = NULL;

    for (int m = start_mask; m <= start_mask + 10 && !found; m++) {

        // Try XOR (0)
        match = find_decrypted_match(&org, cipher, m, 0);
        if (match) {
            found = 1;
            found_mask = m;
            found_op_str = "XOR";
            break;
        }
        
        // Try AND (1)
        match = find_decrypted_match(&org, cipher, m, 1);
        if (match) {
            found = 1;
            found_mask = m;
            found_op_str = "AND";
            break;
        }
    }

    if (found && match) {
        print_success(found_mask, (char*)found_op_str, (char*)match->fingerprint, (char*)match->first, (char*)match->second);
    } else {
        print_unsuccess();
    }

    // TODO: free any memory you may have allocated
    free_org(&org);
    return 0;
}
