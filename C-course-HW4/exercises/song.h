#ifndef SONG_H
#define SONG_H

#include <stdbool.h>

typedef enum {
    POP, ROCK, JAZZ, CLASSICAL, HIPHOP
} Genre;

typedef struct {
    char* title;
    char* artist;
    int duration_in_seconds;
    Genre genre;
} Song;

void set_song(Song* s, const char* title, const char* artist, int duration, Genre genre);
void print_song(const Song* s);
void free_song(Song* s);

#endif 