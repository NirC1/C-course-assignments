#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../exercises/org_tree.h"

// Helper function removed. Testing against provided file.

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <clean_file_path>\n", argv[0]);
        return 1;
    }
    const char *test_filename = argv[1];

    // Step 2: Build the organization tree
    printf("\n[TEST] Calling build_org_from_clean_file with %s...\n", test_filename);
    Org org = build_org_from_clean_file(test_filename);

    // Step 3: Print the tree
    printf("\n[TEST] Calling print_tree_order...\n");
    print_tree_order(&org);
    
    // Step 4: Free the organization
    printf("\n[TEST] Calling free_org...\n");
    free_org(&org);
    printf("[TEST] Organization freed.\n");

    return 0;
}
