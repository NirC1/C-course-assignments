#include "song.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_db(Database *db);

int main(void){
    printf("testing song.h\n");
    size_t song_size = sizeof(Song);
    printf("size of Song in bytes: %d\n", (int)song_size);
    printf("allocating song\n");

    Song *S;
    S = malloc(sizeof(Song));
    if(NULL == S){
        printf("allocation failed");
        exit(1);
    }
    printf("allocation successful\n");

    set_song(S, "title", "artist", 15, ROCK);
    print_song(S);

    //printf("testing set song with NULL title\n");
    //set_song(S, NULL, "artist", 15, POP);

    free_song(S);
    printf("song freed\n");

    S = NULL;

    //printf("testing set song with NULL song\n");
    //set_song(S, "title", "artist", 15, 0);
    
    printf("testing database\n");
    Database *db = malloc(sizeof(Database));
    if(NULL == db){
        printf("allocation failed");
        exit(1);
    }

    create_database(db, 2);
    printf("created database with capacity 2\n");
    printf("capacity: %d\n", db->capacity);

    char *titles[] = {"blinding", "signals", "the end"};
    char *artists[] = {"week", "end", "bobi"};
    int seconds[] = {520, 202, 141};
    Genre genres[] = {POP, ROCK, CLASSICAL};

    for(int i = 0; i < 3; i++){
        S = malloc(sizeof(Song));
        if(NULL == S){
            printf("allocation failed");
            exit(1);
        }
        printf("setting new song");
        set_song(S, titles[i], artists[i], seconds[i], genres[i]);
        print_song(S);
        printf("adding song\n");
        db_add_song(db, S);
        printf("added song, count: %d, capacity: %d\n", db->count, db->capacity);
    }

    printf("printing songs\n");
    print_db(db);
    
    printf("searching song \"blinding\"\n");
    int i = find_song_in_db(db, "blinding");
    printf("found: %d\n", i);

    printf("removing song\n");
    db_remove_song(db, "signals");
    print_db(db);

    return 0;
}

void print_db(Database *db)
{
    for(int i = 0; i < db->count; i++){
        printf("song %d: %s\n", i, db->songs[i]->title);
    }
}
