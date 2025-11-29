#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 10
#define STR_POOL_SIZE 20

void print_string_pool(char (*pool)[MAX_STR_LEN +1], int last);
void init_string_rotation_arr(char search_str[], char (*search_str_rotations)[MAX_STR_LEN]);

int main(void){
    char search_str[MAX_STR_LEN + 1], str_pool[STR_POOL_SIZE][MAX_STR_LEN +1];
    int pool_str_index = 0; // points at the location after the last string in the pool
    char search_str_rotations[MAX_STR_LEN][MAX_STR_LEN]; // holds all of the possible rotations of the search string

    printf("Enter the search string: \n");
    scanf("%[^\n]%*c", search_str);

    // for testing
    printf("%s\n", search_str);

    init_string_rotation_arr(search_str, search_str_rotations);

    int ret;
    while(pool_str_index < STR_POOL_SIZE){
        ret = scanf("%[^\n]%*c", str_pool[pool_str_index]);
        printf("scanf returned: %d\n", ret); // testing

        if (ret == EOF) { // Successful EOF
            break; 
        }

        if (ret == 0) { // did not match anything, could only be \n
            getchar(); // Consume the '\n'
            break; // Stop reading input
        }

        if (ret == 1) { // successfully read a string terminated by a newline
            pool_str_index++; 
        }
    }
    

    print_string_pool(str_pool, pool_str_index);


    
    return 0;
}

void print_string_pool(char (*pool)[MAX_STR_LEN +1], int last)
{
    printf("Printing string pool\n"); // testing
    for(int i = 0; i < last; i++){
        printf("%s\n", pool[i]);
    }
    printf("pool last: %d\n", last); 
    
}

void init_string_rotation_arr(char search_str[], char (*search_str_rotations)[MAX_STR_LEN])
{
    int N = strlen(search_str);
    for(int i = 0; i < N; i++){
        int j = 0;
        for(; j < N; j++){
            search_str_rotations[i][j] = search_str[(j + i) % N];
        }
        search_str_rotations[i][j] = '\0';
        printf("string i = :%d, %s\n", i, search_str_rotations[i]);
    }
}
