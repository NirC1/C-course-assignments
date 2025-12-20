#include <stdio.h>
#include <stdlib.h>

#include "../exercises/song.h"
#include "../exercises/database.h"
#include "../exercises/queue.h"

int main(void) {
    Database *db = (Database *)malloc(sizeof(Database));
    if (db == NULL) {
        return 1;
    }
    create_database(db, 5);

    Song *s1 = (Song *)malloc(sizeof(Song));
    Song *s2 = (Song *)malloc(sizeof(Song));
    Song *s3 = (Song *)malloc(sizeof(Song));
    Song *s4 = (Song *)malloc(sizeof(Song));
    Song *s5 = (Song *)malloc(sizeof(Song));
    if (!s1 || !s2 || !s3 || !s4 || !s5) {
        return 1;
    }

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

    Queue *q = (Queue *)malloc(sizeof(Queue));
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

    /* The expected output file has a blank line after the queue. */
    printf("\n");

    free_queue(q);
    free_db(db);
    return 0;
}
