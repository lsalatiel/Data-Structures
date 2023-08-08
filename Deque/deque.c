#include "deque.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_ALLOC_ROW 7
#define COLUMN_SIZE 5

struct Deque {
    void ***array;
    int front_block;
    int rear_block;
    int allocated;
    int front; // first element in the front_block
    int rear; // first free position in the rear_block
};

Deque *deque_construct(void) {
    Deque *deque = malloc(sizeof(Deque));

    deque->array = malloc(INITIAL_ALLOC_ROW * sizeof(void **));

    deque->array[INITIAL_ALLOC_ROW / 2] = malloc(COLUMN_SIZE * sizeof(void *)); 

    deque->front = 0;
    deque->rear = 0;

    deque->front_block = INITIAL_ALLOC_ROW / 2;
    deque->rear_block = INITIAL_ALLOC_ROW / 2;

    deque->allocated = INITIAL_ALLOC_ROW;

    return deque;
}

void deque_push_back(Deque *d, void *val) {
    if(d->rear_block == d->allocated) {
        void ***new_array = malloc((d->allocated + 2) * sizeof(void **)); 

        int mid = (d->allocated + 2) / 2;
        int size = d->rear_block - d->front_block + 1;
        int front = mid - size / 2;
        int j = front;
        for(int i = d->front_block; i < d->rear_block; i++) {
            new_array[j] = d->array[i];
            j++;
        }

        d->front_block = front;
        d->rear_block = j;
        d->allocated += 2;
        free(d->array);
        d->array = new_array;
    }

    if(d->rear == 0 && deque_size(d) != 0)
        d->array[d->rear_block] = malloc(COLUMN_SIZE * sizeof(void *));

    d->array[d->rear_block][d->rear] = val;
    d->rear++;

    if(d->rear >= COLUMN_SIZE) {
        d->rear = 0;
        d->rear_block++;
    }
}

void deque_push_front(Deque *d, void *val) {
    if(d->front_block == 0 && d->front == 0) {
        void ***new_array = malloc((d->allocated + 2) * sizeof(void **)); 

        int gap = d->allocated - d->rear_block + 1;
        for(int i = d->front_block; i <= d->rear_block; i++) {
            int idx = i + gap / 2;
            new_array[idx] = d->array[i];
        }

        d->front_block += gap / 2;
        d->rear_block += gap / 2;
        d->allocated += 2;
        free(d->array);
        d->array = new_array;
    }
    
    if(deque_size(d) == 0) {
        d->rear++;
    }
    else
        d->front--;

    if(d->front < 0) {
        d->front = COLUMN_SIZE - 1;
        d->front_block--;
        d->array[d->front_block] = malloc(COLUMN_SIZE * sizeof(void *));
    }

    d->array[d->front_block][d->front] = val;
}

void *deque_pop_back(Deque *d) { // never desalocats the first array
    if(deque_size(d) == 0)
        return NULL;
    
    d->rear--;
    
    if(d->rear < 0) {
        d->rear_block--;
        d->rear = COLUMN_SIZE - 1;
    }

    if(deque_size(d) == 0) {
        void *to_remove = d->array[d->rear_block][d->rear];
        d->front = 0;
        d->rear = 0;
        d->rear_block = d->front_block;
        return to_remove;
    }
    else if(d->rear == 0) {
        void *to_remove = d->array[d->rear_block][d->rear];
        free(d->array[d->rear_block]);
        return to_remove;
    }

    void *to_remove = d->array[d->rear_block][d->rear];

    return to_remove;
}

void *deque_pop_front(Deque *d) {
    if(deque_size(d) == 0) {
        return NULL;
    }

    void *to_remove = d->array[d->front_block][d->front];

    d->front++;

    if(deque_size(d) == 0) {
        d->front = 0;
        d->rear = 0;
        d->rear_block = d->front_block;
    }
    else if(d->front >= COLUMN_SIZE) {
        free(d->array[d->front_block]);
        d->front_block++;
        d->front = 0;
    }

    return to_remove;
}

int deque_size(Deque *d) {
    return (d->rear_block - d->front_block) * COLUMN_SIZE + (d->rear - d->front);
}

void *deque_get(Deque *d, int idx);

void deque_destroy(Deque *d) {
    if(d->rear == 0 && d->rear_block != d->front_block)
        d->rear_block--;
    for(int i = d->front_block; i <= d->rear_block; i++) {
        if(d->array[i] == NULL)
            continue;
        
        int front = 0;
        int rear = COLUMN_SIZE;

        if(i == d->front_block)
            front = d->front;
        if(i == d->rear_block) {
            rear = d->rear;
        }

        for(int j = front; j < rear; j++) {
            if(d->array[i][j] != NULL)
                free(d->array[i][j]);
        }
        free(d->array[i]);
    }

    free(d->array);

    free(d);
}
