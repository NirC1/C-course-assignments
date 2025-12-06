#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 10
#define STR_POOL_SIZE 20

int init_string_rotation_arr(char search_str[], char (*search_str_rotations)[MAX_STR_LEN + 1]);
int strcmp_insensitive(const char *s1, const char *s2);

int main(void){
    char search_str[MAX_STR_LEN + 1] = {0}, str_pool[STR_POOL_SIZE][MAX_STR_LEN +1] = {0};
    int pool_str_index = 0; // points at the location after the last string in the pool
    char search_str_rotations[MAX_STR_LEN][MAX_STR_LEN + 1]; // holds all of the possible rotations of the search string

    printf("Enter the search string:\n");
    scanf("%[^\n]%*c", search_str);


    int num_of_rotations = init_string_rotation_arr(search_str, search_str_rotations);

    printf("Enter the strings pool:\n");

    int ret;
    while(pool_str_index < STR_POOL_SIZE){
        ret = scanf("%[^\n]%*c", str_pool[pool_str_index]);

        if (ret == EOF) { // Successful EOF
            break; 
        }

        if (ret == 0) { // did not match anything, could only be \n
            getchar(); // Consume the '\n'
            str_pool[pool_str_index][0] = '\0';
            pool_str_index++;
        }

        if (ret == 1) { // successfully read a string terminated by a newline
            pool_str_index++; 
        }
    }
    


    // compare the strings
    int count = 0;
    for(int i = 0; i < pool_str_index; i++){
        for(int j = 0; j < num_of_rotations; j++){
            if(strcmp_insensitive(search_str_rotations[j], str_pool[i]) == 0){
                count++;
                break;
            }
        }
    }

    printf("Number of rotations of \"%s\" in the strings pool is: %d\n", search_str, count);

    
    return 0;
}


int init_string_rotation_arr(char search_str[], char (*search_str_rotations)[MAX_STR_LEN + 1])
{
    int N = strlen(search_str);
    if(0 == N){
        search_str_rotations[0][0] = '\0';
        return 1;
    }
    for(int i = 0; i < N; i++){
        int j = 0;
        for(; j < N; j++){
            search_str_rotations[i][j] = search_str[(j + i) % N];
        }
        search_str_rotations[i][j] = '\0';
    }
    return N;
}

int strcmp_insensitive(const char *s1, const char *s2)
{
    for(;; s1++, s2++){
        int d = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if(d != 0 || (*s1)=='\0'){
            return d;
        }
    }
}
