#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_song(Song *s, const char *title, const char *artist,
              int duration, Genre genre) {
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    if (title == NULL) {
        printf("ERROR: NULL title pointer.\n");
        exit(1);
    }
    if (artist == NULL) {
        printf("ERROR: NULL artist pointer.\n");
        exit(1);
    }
    s->title = strdup(title);
    if (s->title == NULL) {
        printf("ERROR: Failed to allocate memory for title.\n");
        exit(1);
    }
    s->artist = strdup(artist);
    if (s->artist == NULL) {
        free(s->title);
        s->title = NULL;
        printf("ERROR: Failed to allocate memory for artist.\n");
        exit(1);
    }
    s->duration_in_seconds = duration;
    s->genre = genre;
}


void print_song(const Song *s) {
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    if (s->title == NULL || s->artist == NULL) {
        printf("ERROR: Song has NULL fields.\n");
        exit(1);
    }
    static const char *genre_strings[] = {"POP", "ROCK", "JAZZ", "CLASSICAL", "HIPHOP"};
    const char *genre_name = "";
    if (s->genre >= POP && s->genre <= HIPHOP) {
        genre_name = genre_strings[s->genre];
    }
    printf("Title: %s, Artist: %s, Duration: %ds, Genre: %s\n",
           s->title, s->artist, s->duration_in_seconds, genre_name);
}

void free_song(Song *s) {
    if (s == NULL) {
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    if (s->title != NULL) {
        free(s->title);
        s->title = NULL;
    }
    if (s->artist != NULL) {
        free(s->artist);
        s->artist = NULL;
    }
    free(s);
}
