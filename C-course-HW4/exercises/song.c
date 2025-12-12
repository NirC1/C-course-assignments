
#include "song.h"
#include <stdio.h>
#include <stdlib.h>

void print_song(const Song *s) {
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    if (s->title == NULL || s->artist == NULL) {
        printf("ERROR: Song has NULL fields.\n");
        exit(1);
    }

    static const char *genre_names[] = {
        "POP",
        "ROCK",
        "JAZZ",
        "CLASSICAL",
        "HIPHOP"
    };


    if (s->genre < POP || s->genre > HIPHOP) {
        printf("ERROR: Song has an unknown genre.\n");
        exit(1);
    }

 
    printf("Title: %s, Artist: %s, Duration: %ds, Genre: %s\n",
           s->title,
           s->artist,
           s->duration_in_seconds,
           genre_names[s->genre]);
}

/*
 * free_song
 *
 * Frees all dynamically allocated fields inside the Song.  It is the
 * caller's responsibility to ensure that the Song pointer itself
 * points to a valid struct allocated either on the stack or on the
 * heap.  After this call the title and artist pointers in the struct
 * will be NULL.  The struct itself is not freed here.
 */
void free_song(Song *s) {
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }

    // Free the dynamically allocated title if it exists
    if (s->title != NULL) {
        free(s->title);
        s->title = NULL;
    }

    // Free the dynamically allocated artist if it exists
    if (s->artist != NULL) {
        free(s->artist);
        s->artist = NULL;
    }
}