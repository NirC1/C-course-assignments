#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void create_queue(Queue *q) {
    if (q == NULL) {
        printf("ERROR: NULL Queue pointer.\n");
        exit(1);
    }
    q->capacity = MAX_Q_SIZE;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->prev_song = NULL;
    q->cur_song = NULL;
    q->queue_songs = (char **)malloc(sizeof(char *) * q->capacity);
    if (q->queue_songs == NULL) {
        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);
    }
    for (int i = 0; i < q->capacity; i++) {
        q->queue_songs[i] = NULL;
    }
}


void queue_add_song(Queue *q, Database *db, const char *title) {
    if (q == NULL) {
        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }
    if (db == NULL) {
        printf("ERROR: NULL database pointer.\n");
        exit(1);
    }
    if (title == NULL) {
        printf("ERROR: NULL title.\n");
        exit(1);
    }
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        Song *curr = db->songs[i];
        if (curr != NULL && curr->title != NULL && strcmp(curr->title, title) == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("ERROR: Song was not found in database.\n");
        return;
    }
    if (q->size >= q->capacity) {
        printf("ERROR: Queue is full.\n");
        return;
    }
    char *new_title = strdup(title);
    if (new_title == NULL) {
        printf("ERROR: Failed to allocate memory for song title.\n");
        exit(1);
    }
    q->queue_songs[q->rear] = new_title;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}



void queue_next_song(Queue *q) {
    if (q == NULL) {
        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }
    if (q->size == 0) {
        printf("ERROR: Queue is empty.\n");
        return;
    }
    if (q->prev_song != NULL) {
        free(q->prev_song);
        q->prev_song = NULL;
    }
    q->prev_song = q->cur_song;
    char *next_title = q->queue_songs[q->front];
    q->queue_songs[q->front] = NULL;
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    q->cur_song = next_title;
}


void print_queue(const Queue *q) {
    if (q == NULL) {
        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }
    if (q->size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents:\n");
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        char *title = q->queue_songs[index];
        /* index for display is 1-based */
        printf("%d. %s\n", i + 1, title);
    }
}

void free_queue(Queue *q) {
    if (q == NULL) {
        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }
    if (q->prev_song != NULL) {
        free(q->prev_song);
        q->prev_song = NULL;
    }
    if (q->cur_song != NULL) {
        free(q->cur_song);
        q->cur_song = NULL;
    }
    if (q->queue_songs != NULL) {
        for (int i = 0; i < q->capacity; i++) {
            if (q->queue_songs[i] != NULL) {
                free(q->queue_songs[i]);
                q->queue_songs[i] = NULL;
            }
        }
        free(q->queue_songs);
        q->queue_songs = NULL;
    }
    free(q);
}

