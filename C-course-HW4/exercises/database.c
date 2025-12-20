#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void create_database(Database *db, int initial_capacity) {
    if (db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    
    db->songs = (Song **)malloc(sizeof(Song *) * initial_capacity);
    if (db->songs == NULL) {
        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);
    }
   
    db->count = 0;
    db->capacity = initial_capacity;
    /* set all pointers to NULL to avoid accidental frees */
    for (int i = 0; i < initial_capacity; i++) {
        db->songs[i] = NULL;
    }
}


void db_add_song(Database *db, Song *s) {
    if (db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    /* expand the database if it is full */
    if (db->count >= db->capacity) {
        int new_capacity = db->capacity * 2;
        Song **new_array = (Song **)realloc(db->songs, sizeof(Song *) * new_capacity);
        if (new_array == NULL) {
            printf("ERROR: Failed to expand database.\n");
            exit(1);
        }
       
        db->songs = new_array;
    
        for (int i = db->capacity; i < new_capacity; i++) {
            db->songs[i] = NULL;
        }
        db->capacity = new_capacity;
    }
    
    db->songs[db->count] = s;
    db->count++;
}

void db_remove_song(Database *db, const char *title) {
    if (db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    if (title == NULL) {
        printf("ERROR: NULL title.\n");
        exit(1);
    }
    int index = -1;
    for (int i = 0; i < db->count; i++) {
        Song *curr = db->songs[i];
        if (curr != NULL && curr->title != NULL && strcmp(curr->title, title) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("ERROR: Song not found in database.\n");
        return;
    }
    if (db->songs[index] != NULL) {
        free_song(db->songs[index]);
    }
    for (int j = index; j < db->count - 1; j++) {
        db->songs[j] = db->songs[j + 1];
    }
    
    db->songs[db->count - 1] = NULL;
    db->count--;
}

void free_db(Database *db) {
    if (db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    for (int i = 0; i < db->count; i++) {
        if (db->songs[i] != NULL) {
            free_song(db->songs[i]);
            db->songs[i] = NULL;
        }
    }
    
    free(db->songs);
    db->songs = NULL;
    free(db);
}
