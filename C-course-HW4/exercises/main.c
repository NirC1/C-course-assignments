#include "song.h"
#include "database.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void print_db(const Database *db) {
    if (db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }
    printf("Database contains %d songs (capacity %d):\n", db->count, db->capacity);
    for (int i = 0; i < db->count; i++) {
        printf("Song %d: ", i + 1);
        print_song(db->songs[i]);
    }
}

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
    create_database(db, 2); // Set initial capacity low to trigger expansion

    Song *s1 = malloc(sizeof(Song));
    Song *s2 = malloc(sizeof(Song));
    Song *s3 = malloc(sizeof(Song));
    Song *s4 = malloc(sizeof(Song));
    Song *s5 = malloc(sizeof(Song));
    if (!s1 || !s2 || !s3 || !s4 || !s5) return 1;

    set_song(s1, "I Know The End", "Phoebe Bridgers", 300, ROCK);
    set_song(s2, "Smoke Signals", "Phoebe Bridgers", 250, ROCK);
    set_song(s3, "Funeral", "Phoebe Bridgers", 240, ROCK);
    set_song(s4, "Demi Moore", "Phoebe Bridgers", 260, ROCK);
    set_song(s5, "Scott Street", "Phoebe Bridgers", 280, ROCK);

    printf("--- Adding songs ---\n");
    db_add_song(db, s1);
    printf("Added 1 song. Capacity: %d\n", db->capacity);
    
    db_add_song(db, s2);
    printf("Added 2 songs. Capacity: %d\n", db->capacity);
    
    db_add_song(db, s3);
    printf("Added 3 songs. Capacity: %d\n", db->capacity);
    
    db_add_song(db, s4);
    printf("Added 4 songs. Capacity: %d\n", db->capacity);
    
    db_add_song(db, s5);
    printf("Added 5 songs. Capacity: %d\n", db->capacity);

    printf("\n--- Final Database State ---\n");
    print_db(db); // Print database to verify all songs were added correctly



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

    printf("\n--- Testing Queue Next Song ---\n");
    printf("Playing next song...\n");
    queue_next_song(q);
    if (q->cur_song) printf("Current song: %s\n", q->cur_song);
    if (q->prev_song) printf("Previous song: %s\n", q->prev_song);
    else printf("Previous song: None\n");   
    print_queue(q);

    printf("Playing next song...\n");
    queue_next_song(q);
    if (q->cur_song) printf("Current song: %s\n", q->cur_song);
    if (q->prev_song) printf("Previous song: %s\n", q->prev_song);
    print_queue(q);

    printf("\n--- Testing Remove Song ---\n");
    printf("Removing 'Funeral' from database...\n");
    db_remove_song(db, "Funeral");
    print_db(db);

    printf("Removing 'NonExistent' from database (should fail)...\n");
    db_remove_song(db, "NonExistent");
    print_db(db);

    free_queue(q);
    free_db(db);

    return 0;
}