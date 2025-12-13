#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void create_database(Database *db, int initial_capacity) {
    if(NULL == db){
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    Song **song_arr_ptr = malloc(sizeof(Song*) * initial_capacity);
    
    if(NULL == song_arr_ptr){
        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);
    }

    db->songs = song_arr_ptr;
    db->capacity = initial_capacity;
    db->count = 0;
}


void db_add_song(Database *db, Song *s) {
    if(NULL == db){
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }if(NULL == s){
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    if(db->capacity <= db->count){
        Song **song_arr_ptr = realloc(db->songs, sizeof(Song*) * db->capacity * 2);
        if(NULL == song_arr_ptr){
            printf("ERROR: Failed to expand database.\n");
            exit(1);
        }
        db->songs = song_arr_ptr;
        db->capacity = db->capacity * 2;
    }

    db->songs[db->count] = s;
    db->count++;
}

void db_remove_song(Database *db, const char *title) {
    if(NULL == db){
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }if(NULL == title){
        printf("ERROR: NULL title.\n");
        exit(1);
    }

    int song_idx = find_song_in_db(db, title);
    if(-1 == song_idx){
        printf("ERROR: Song not found in database.\n");
        return;
    }

    free(db->songs[song_idx]);
    int i = song_idx;
    for(; (i + 1) < db->count; i++){
        db->songs[i] = db->songs[i + 1];
    }
    db->count = i;

}

void free_db(Database *db) {

    printf("ERROR: NULL Database pointer.\n");

}

int find_song_in_db(const Database *db, const char *title) {
    int i = 0;
    for(; i < db->count; i++){
        if(strcmp((db->songs[i])->title, title) == 0){
            return i;
        }
    }
    return -1;
}
