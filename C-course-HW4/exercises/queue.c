#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void create_queue(Queue *q) {

    printf("ERROR: NULL Queue pointer.\n");

    printf("ERROR: Failed to allocate songs array.\n");
}


void queue_add_song(Queue *q, Database *db, const char *title) {

    printf("ERROR: NULL queue pointer.\n");

    printf("ERROR: NULL database pointer.\n");

    printf("ERROR: NULL title.\n");

    printf("ERROR: Song was not found in database.\n");

    printf("ERROR: Queue is full.\n");

    printf("ERROR: Failed to allocate memory for song title.\n");
}



void queue_next_song(Queue *q) {

    printf("ERROR: NULL queue pointer.\n");

    printf("ERROR: Queue is empty.\n");
}


void print_queue(const Queue *q) {
    printf("ERROR: NULL queue pointer.\n");

    printf("Queue is empty.\n");

    printf("Queue contents:\n");
}

void free_queue(Queue *q) {
    printf("ERROR: NULL queue pointer.\n");
}
