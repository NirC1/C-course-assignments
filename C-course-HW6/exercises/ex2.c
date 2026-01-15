#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "org_tree.h"
#define FP_LEN 9

/* Helper to print a success message. */
static void print_success(int mask, char *op,
                          char* fingerprint,
                          char* first_name,
                          char* second_name)
{
    printf("Successful Decrypt! The Mask used was mask_%d of type (%s) and "
           "The fingerprint was %.*s belonging to %s %s\n",
           mask, op, FP_LEN, fingerprint, first_name, second_name);
}

/* Helper to print a failure message. */
static void print_unsuccess()
{
    printf("Unsuccesful decrypt, Looks like he got away\n");
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <clean_file.txt> <cipher_bits.txt> <mask_start_s>\n", argv[0]);
        return 0;
    }
    const char *clean_path  = argv[1];
    const char *cipher_path = argv[2];
    int start_mask          = (int)strtol(argv[3], NULL, 10);

    Org org = build_org_from_clean_file(clean_path);
    /* If the file fails to open, build_org_from_clean_file already prints an error
       and leaves org empty. */
    if (!org.boss && !org.left_hand && !org.right_hand) {
        return 0;
    }

    FILE *cf = fopen(cipher_path, "r");
    if (!cf) {
        printf("Error opening file: %s\n", cipher_path);
        free_org(&org);
        return 0;
    }
    int cipher[FP_LEN] = {0};
    char line[64];
    for (int i = 0; i < FP_LEN; i++) {
        if (!fgets(line, sizeof(line), cf)) {
            cipher[i] = 0;
        } else {
            int value = 0;
            for (int j = 0; line[j] != '\0'; j++) {
                if (line[j] == '0' || line[j] == '1') {
                    value = (value << 1) | (line[j] - '0');
                } else if (line[j] == '\n' || line[j] == '\r') {
                    break;
                }
            }
            cipher[i] = value;
        }
    }
    fclose(cf);

    int found = 0, found_mask = 0;
    char *found_op     = NULL;
    char *found_fp     = NULL;
    char *found_first  = NULL;
    char *found_second = NULL;

    /* Try masks from start_mask to start_mask+10 and both XOR/AND operations. */
    for (int mask = start_mask; mask <= start_mask + 10 && !found; mask++) {
        for (int op_idx = 0; op_idx < 2 && !found; op_idx++) {
            const char *op_name = (op_idx == 0 ? "XOR" : "AND");
            /* Gather all nodes into an array for easy iteration. */
            const Node *nodes[100];
            int count = 0;
            if (org.boss)      nodes[count++] = org.boss;
            if (org.left_hand) nodes[count++] = org.left_hand;
            if (org.right_hand)nodes[count++] = org.right_hand;
            if (org.left_hand) {
                Node *c = org.left_hand->supports_head;
                while (c && count < 100) {
                    nodes[count++] = c;
                    c = c->next;
                }
            }
            if (org.right_hand) {
                Node *c = org.right_hand->supports_head;
                while (c && count < 100) {
                    nodes[count++] = c;
                    c = c->next;
                }
            }
            for (int n = 0; n < count && !found; n++) {
                const Node *node = nodes[n];
                int ok = 1;
                for (int i = 0; i < FP_LEN; i++) {
                    unsigned char plain = (unsigned char)node->fingerprint[i];
                    int out = (op_idx == 0 ? (plain ^ mask) : (plain & mask));
                    if (out != cipher[i]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    found      = 1;
                    found_mask = mask;
                    found_op   = (char *)op_name;
                    found_fp   = node->fingerprint;
                    found_first  = node->first;
                    found_second = node->second;
                }
            }
        }
    }

    if (found) {
        print_success(found_mask, found_op, found_fp, found_first, found_second);
    } else {
        print_unsuccess();
    }
    free_org(&org);
    return 0;
}
