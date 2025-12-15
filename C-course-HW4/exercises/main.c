#include "song.h"
#include "database.h"
#include "queue.h"
#include <stdlib.h>

int main(void) {
    Song *single = malloc(sizeof(Song));
    if (single == NULL) {
        return 1;
    }
    set_song(single, "Blinding Lights", "The Weeknd", 202, POP);
    print_song(single);
    free_song(single);

    Database *db = malloc(sizeof(Database));
    if (db == NULL) {
        return 1;
    }
    create_database(db, 5);

    Song *s1 = malloc(sizeof(Song));
    Song *s2 = malloc(sizeof(Song));
    Song *s3 = malloc(sizeof(Song));
    Song *s4 = malloc(sizeof(Song));
    Song *s5 = malloc(sizeof(Song));
    set_song(s1, "I Know The End", "Phoebe Bridgers", 300, ROCK);
    set_song(s2, "Smoke Signals", "Phoebe Bridgers", 250, ROCK);
    set_song(s3, "Funeral", "Phoebe Bridgers", 240, ROCK);
    set_song(s4, "Demi Moore", "Phoebe Bridgers", 260, ROCK);
    set_song(s5, "Scott Street", "Phoebe Bridgers", 280, ROCK);

    db_add_song(db, s1);
    db_add_song(db, s2);
    db_add_song(db, s3);
    db_add_song(db, s4);
    db_add_song(db, s5);

    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        return 1;
    }
    create_queue(q);
    queue_add_song(q, db, "I Know The End");
    queue_add_song(q, db, "Smoke Signals");
    queue_add_song(q, db, "Funeral");
    queue_add_song(q, db, "Demi Moore");
    queue_add_song(q, db, "Scott Street");

    print_queue(q);
    free_queue(q);
    free_db(db);

    return 0;
}