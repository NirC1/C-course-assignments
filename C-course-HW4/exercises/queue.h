#ifndef QUEUE_H
#define QUEUE_H
#define MAX_Q_SIZE 20
#define MAX_SONG_LEN 100
#include "song.h"
#include "database.h"

typedef struct {
    char *prev_song; 
    char *cur_song;
    char **queue_songs;
    int capacity;
    int front;
    int rear;
    int size;
} Queue;

void create_queue(Queue *q);
void queue_add_song(Queue *q, Database *db, const char *title);
void queue_next_song(Queue *q);
void print_queue(const Queue *q);
void free_queue(Queue *q);

#endif 