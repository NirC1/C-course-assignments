#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *genre_names[] = {"POP", "ROCK", "JAZZ", "CLASSICAL", "HIPHOP"};

void set_song(Song *s, const char *title, const char *artist,
              int duration, Genre genre) {
    if(NULL == s){
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }if(NULL == title){
        printf("ERROR: NULL title pointer.\n");
        exit(1);
    }if(NULL == artist){
        printf("ERROR: NULL artist pointer.\n");
        exit(1);
    }

    char *allocated_title  = malloc(strlen(title)  * sizeof(char));
    char *allocated_artist = malloc(strlen(artist) * sizeof(char));
    if(NULL == allocated_title){
        printf("ERROR: Failed to allocate memory for title.\n");
    }if(NULL == allocated_artist){
        printf("ERROR: Failed to allocate memory for artist.\n");
    }

    strcpy(allocated_title,  title); //copies the title
    strcpy(allocated_artist, artist);

    s->title  = allocated_title;
    s->artist = allocated_artist;
    s->duration_in_seconds = duration;
    s->genre = genre;
}


void print_song(const Song *s) {
    if(NULL == s){
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }if(NULL == s->artist || NULL == s->title){
        printf("ERROR: Song has NULL fields.\n");
        exit(1);
    }

    printf("Title: %s, Artist: %s, Duration: %ds, Genre: %s\n", // remember to print genre string
            s->title, s->artist, s->duration_in_seconds, genre_names[s->genre]);
}

void free_song(Song *s) {
    if(NULL == s){
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }
    free(s->title);
    free(s->artist);
    free(s);
}
