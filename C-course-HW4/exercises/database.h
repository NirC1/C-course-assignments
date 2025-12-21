#ifndef DATABASE_H
#define DATABASE_H

#include "song.h"

typedef struct {
    Song **songs;
    int count;      
    int capacity;
} Database;

void create_database(Database *db, int initial_capacity);
void db_add_song(Database *db, Song *s);
void db_remove_song(Database *db, const char *title);
void free_db(Database *db);

#endif 

