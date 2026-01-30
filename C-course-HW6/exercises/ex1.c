#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LABEL_COUNT 4

/* Determine if a character is a noise character (to be ignored). */
static int is_noise_char(int c) {
    return (c == '#' || c == '?' || c == '!' || c == '@' ||
            c == '&' || c == '$' || c == '\n' || c == '\r');
}

/* Read a file and return a buffer containing only non-noise characters. */
static char *read_and_clean_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("Error opening file: %s\n", path);
        return NULL;
    }
    size_t cap = 1024, len = 0;
    char *buf = (char *)malloc(cap);
    if (!buf) {
        fclose(fp);
        printf("Error allocating memory\n");
        return NULL;
    }
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (is_noise_char(ch)) {
            continue;
        }
        if (len + 2 > cap) {
            cap *= 2;
            char *tmp = (char *)realloc(buf, cap);
            if (!tmp) {
                free(buf);
                fclose(fp);
                printf("Error allocating memory\n");
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)ch;
    }
    buf[len] = '\0';
    fclose(fp);
    return buf;
}

char* trim(char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (*s == 0) return s;
    char *back = s + strlen(s) - 1;
    while (back > s && isspace((unsigned char)*back)) back--;
    *(back + 1) = '\0';
    return s;
}

/* Structure for a single cleaned entry. */
typedef struct {
    char *fields[4]; // Order: First, Second, Fingerprint, Position
} Entry;

// Labels to look for in the clean buffer
const char *LABELS[] = {"First Name:", "Second Name:", "Fingerprint:", "Position:"};


size_t count_substring(const char *text, const char *sub) {
    if (*sub == '\0') return 0;  // avoid infinite loop

    size_t count = 0;
    const char *p = text;

    while ((p = strstr(p, sub)) != NULL) {
        count++;
        p += strlen(sub);  // jump past this occurrence
    }

    return count;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <input_corrupted.txt> <output_clean.txt>\n", argv[0]);
        return 0;
    }

    char *buffer = read_and_clean_file(argv[1]);
    if (!buffer) return 0;

    // printf("Cleaned Buffer:\n%s\n", buffer);

    // 2. Count entries
    size_t entry_count = count_substring(buffer, LABELS[0]);
    char **label_ptrs = (char **)malloc(entry_count * LABEL_COUNT * sizeof(char *));
    if (!label_ptrs) {
        printf("Error allocating memory for label pointers\n");
        free(buffer);
        return 0;
    }

    char *curr = buffer;



    for(size_t i = 0; i < entry_count; i++){
        for(size_t j = 0; j < LABEL_COUNT; j++){
            char *label_pos = strstr(curr, LABELS[j]);
            if(label_pos == NULL){
                label_ptrs[i * LABEL_COUNT + j] = NULL;
                continue;
            }
            curr = label_pos + strlen(LABELS[j]); // move past found label

            label_ptrs[i * LABEL_COUNT + j] = label_pos;
        }
    }


    // 3. Isolate values
    for (size_t i = 0; i < entry_count*LABEL_COUNT; i++)
    {
        int lbl = i % LABEL_COUNT;
        if(label_ptrs[i] == NULL){
            continue;
        }
        char *label_start = label_ptrs[i];
    
        // The data actually starts after the label string
        char *data_start = label_start + strlen(LABELS[lbl]);
        // Terminate the field BEFORE this one (if it's not the very first label)
        if (i > 0) {
            *label_start = '\0'; 
        }
        // Now update the pointer to point to the actual value, not the label
        label_ptrs[i] = data_start;
        // printf("Label %zu: %s\n", i, label_ptrs[i]);
    }


    Entry *list = NULL;
    int count = 0;

    list = (Entry *)malloc(entry_count * sizeof(Entry));
    if (!list) {
        printf("Error allocating memory for entries\n");
        free(buffer);
        free(label_ptrs);
        return 0;
    }

    // 4. Populate entries
    for (size_t i = 0; i < entry_count; i++) {
        Entry e;
        if(label_ptrs[i * LABEL_COUNT] == NULL ||
           label_ptrs[i * LABEL_COUNT + 1] == NULL ||
           label_ptrs[i * LABEL_COUNT + 2] == NULL ||
           label_ptrs[i * LABEL_COUNT + 3] == NULL) {
            continue; // skip incomplete entries
        }
        for (size_t j = 0; j < LABEL_COUNT; j++) {
            e.fields[j] = trim(label_ptrs[i * LABEL_COUNT + j]);
        }

        // Check for duplicate fingerprints
        int exists = 0;
        for (int k = 0; k < count; k++) {
            if (strcmp(list[k].fields[2], e.fields[2]) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            list[count++] = e;
        }
    }

    free(label_ptrs);


    // 5. Output based on required ordering 
    FILE *out = fopen(argv[2], "w");
    const char *order[] = {"Boss", "Right Hand", "Left Hand", "Support_Right", "Support_Left"};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(list[j].fields[3], order[i]) == 0) {
                fprintf(out, "First Name: %s\nSecond Name: %s\nFingerprint: %s\nPosition: %s\n\n",
                        list[j].fields[0], list[j].fields[1], list[j].fields[2], list[j].fields[3]);
            }
        }
    }

    fclose(out);
    free(buffer);
    free(list);
    return 0;


}
