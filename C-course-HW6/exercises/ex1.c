#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/* Trim leading/trailing whitespace in place. */
static void trim_inplace(char *str) {
    size_t start = 0;
    while (str[start] && isspace((unsigned char)str[start])) {
        start++;
    }
    size_t end = strlen(str);
    if (end == 0) return;
    size_t idx = end;
    while (idx > start && isspace((unsigned char)str[idx - 1])) {
        idx--;
    }
    str[idx] = '\0';
    if (start > 0) {
        memmove(str, str + start, idx - start + 1);
    }
}

/* Structure for a single cleaned entry. */
typedef struct Entry {
    char *first;
    char *second;
    char *fingerprint;
    char *position;
} Entry;

/* Free memory for one Entry. */
static void free_entry(Entry *e) {
    if (!e) return;
    free(e->first);
    free(e->second);
    free(e->fingerprint);
    free(e->position);
}

/* Check for duplicate fingerprints. */
static int fingerprint_exists(const char *fp, Entry *list, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (strcmp(list[i].fingerprint, fp) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Append an Entry to a dynamic array. */
static int append_entry(Entry **array, size_t *count, Entry item) {
    Entry *tmp = (Entry *)realloc(*array, (*count + 1) * sizeof(Entry));
    if (!tmp) return -1;
    *array = tmp;
    (*array)[*count] = item;
    (*count)++;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <input_corrupted.txt> <output_clean.txt>\n", argv[0]);
        return 0;
    }
    const char *in_path = argv[1], *out_path = argv[2];
    char *content = read_and_clean_file(in_path);
    if (!content) {
        return 0;
    }

    /* Labels and lengths. */
    const char *label_first = "First Name:";
    const char *label_second = "Second Name:";
    const char *label_fp = "Fingerprint:";
    const char *label_pos = "Position:";
    size_t label_first_len = strlen(label_first);
    size_t label_second_len = strlen(label_second);
    size_t label_fp_len = strlen(label_fp);
    size_t label_pos_len = strlen(label_pos);

    /* Dynamic arrays for each category. */
    Entry *boss_list = NULL;   size_t boss_count = 0;
    Entry *right_list = NULL;  size_t right_count = 0;
    Entry *left_list = NULL;   size_t left_count = 0;
    Entry *sr_list = NULL;     size_t sr_count = 0;
    Entry *sl_list = NULL;     size_t sl_count = 0;
    Entry *all_entries = NULL; size_t all_count = 0;

    /* Parse cleaned string. */
    size_t pos = 0;
    size_t content_len = strlen(content);
    while (1) {
        char *p_first = strstr(content + pos, label_first);
        if (!p_first) break;
        pos = (size_t)(p_first - content) + label_first_len;
        char *p_second = strstr(content + pos, label_second);
        if (!p_second) break;
        size_t len_first = (size_t)(p_second - (content + pos));
        char *first_val = malloc(len_first + 1);
        if (!first_val) { printf("Error allocating memory\n"); goto cleanup; }
        strncpy(first_val, content + pos, len_first);
        first_val[len_first] = '\0';
        trim_inplace(first_val);

        pos = (size_t)(p_second - content) + label_second_len;
        char *p_fp = strstr(content + pos, label_fp);
        if (!p_fp) { free(first_val); break; }
        size_t len_second = (size_t)(p_fp - (content + pos));
        char *second_val = malloc(len_second + 1);
        if (!second_val) { free(first_val); printf("Error allocating memory\n"); goto cleanup; }
        strncpy(second_val, content + pos, len_second);
        second_val[len_second] = '\0';
        trim_inplace(second_val);

        pos = (size_t)(p_fp - content) + label_fp_len;
        char *p_poslbl = strstr(content + pos, label_pos);
        if (!p_poslbl) { free(first_val); free(second_val); break; }
        size_t len_fp = (size_t)(p_poslbl - (content + pos));
        char *fp_val = malloc(len_fp + 1);
        if (!fp_val) { free(first_val); free(second_val); printf("Error allocating memory\n"); goto cleanup; }
        strncpy(fp_val, content + pos, len_fp);
        fp_val[len_fp] = '\0';
        trim_inplace(fp_val);

        pos = (size_t)(p_poslbl - content) + label_pos_len;
        char *p_next = strstr(content + pos, label_first);
        size_t len_pos;
        if (p_next) {
            len_pos = (size_t)(p_next - (content + pos));
        } else {
            len_pos = content_len - pos;
        }
        char *pos_val = malloc(len_pos + 1);
        if (!pos_val) { free(first_val); free(second_val); free(fp_val); printf("Error allocating memory\n"); goto cleanup; }
        strncpy(pos_val, content + pos, len_pos);
        pos_val[len_pos] = '\0';
        trim_inplace(pos_val);

        pos += len_pos;

        /* Deduplicate by fingerprint. */
        if (fingerprint_exists(fp_val, all_entries, all_count)) {
            free(first_val); free(second_val); free(fp_val); free(pos_val);
            continue;
        }
        Entry entry = { first_val, second_val, fp_val, pos_val };
        if (append_entry(&all_entries, &all_count, entry) != 0) {
            printf("Error allocating memory\n");
            free_entry(&entry);
            goto cleanup;
        }
        /* Categorize by position. */
        if (strcmp(pos_val, "Boss") == 0) {
            append_entry(&boss_list, &boss_count, entry);
        } else if (strcmp(pos_val, "Right Hand") == 0) {
            append_entry(&right_list, &right_count, entry);
        } else if (strcmp(pos_val, "Left Hand") == 0) {
            append_entry(&left_list, &left_count, entry);
        } else if (strcmp(pos_val, "Support Right") == 0) {
            append_entry(&sr_list, &sr_count, entry);
        } else if (strcmp(pos_val, "Support Left") == 0) {
            append_entry(&sl_list, &sl_count, entry);
        }
    }

    /* Write output in specified order. */
    FILE *outf = fopen(out_path, "w");
    if (!outf) {
        printf("Error opening file: %s\n", out_path);
        goto cleanup;
    }
    for (size_t i = 0; i < boss_count; i++) {
        fprintf(outf, "First Name: %s\n", boss_list[i].first);
        fprintf(outf, "Second Name: %s\n", boss_list[i].second);
        fprintf(outf, "Fingerprint: %s\n", boss_list[i].fingerprint);
        fprintf(outf, "Position: %s\n\n", boss_list[i].position);
    }
    for (size_t i = 0; i < right_count; i++) {
        fprintf(outf, "First Name: %s\n", right_list[i].first);
        fprintf(outf, "Second Name: %s\n", right_list[i].second);
        fprintf(outf, "Fingerprint: %s\n", right_list[i].fingerprint);
        fprintf(outf, "Position: %s\n\n", right_list[i].position);
    }
    for (size_t i = 0; i < left_count; i++) {
        fprintf(outf, "First Name: %s\n", left_list[i].first);
        fprintf(outf, "Second Name: %s\n", left_list[i].second);
        fprintf(outf, "Fingerprint: %s\n", left_list[i].fingerprint);
        fprintf(outf, "Position: %s\n\n", left_list[i].position);
    }
    for (size_t i = 0; i < sr_count; i++) {
        fprintf(outf, "First Name: %s\n", sr_list[i].first);
        fprintf(outf, "Second Name: %s\n", sr_list[i].second);
        fprintf(outf, "Fingerprint: %s\n", sr_list[i].fingerprint);
        fprintf(outf, "Position: %s\n\n", sr_list[i].position);
    }
    for (size_t i = 0; i < sl_count; i++) {
        fprintf(outf, "First Name: %s\n", sl_list[i].first);
        fprintf(outf, "Second Name: %s\n", sl_list[i].second);
        fprintf(outf, "Fingerprint: %s\n", sl_list[i].fingerprint);
        fprintf(outf, "Position: %s\n\n", sl_list[i].position);
    }
    fclose(outf);

cleanup:
    free(content);
    for (size_t i = 0; i < all_count; i++) {
        free_entry(&all_entries[i]);
    }
    free(all_entries);
    free(boss_list);
    free(right_list);
    free(left_list);
    free(sr_list);
    free(sl_list);
    return 0;
}
