#include "CircularArray.h"
#include <stdlib.h>
#include <stdio.h>

CircularArray *circular_array_construct(int size) {
    CircularArray *arr = malloc(sizeof(CircularArray));
    arr->allocated = size;
    arr->data = malloc(arr->allocated * sizeof(data_type));
    arr->size = 0;

    return arr;
}

void circular_array_destroy(CircularArray *arr) {
    free(arr->data);
    free(arr);
}

int circular_array_is_full(CircularArray *arr) {
    return (arr->allocated == arr->size);
}

void circular_array_push_front(CircularArray *arr, data_type data) {
    if(circular_array_is_full(arr)) {
        printf("Error: Array is FULL\n");
        return;
    }

    if(arr->size != 0) {
        arr->front--;
        if(arr->front < 0)
            arr->front = arr->allocated - 1;
    }
    
    arr->data[arr->front] = data;
    
    arr->size++;
}

void circular_array_push_back(CircularArray *arr, data_type data) {
    if(circular_array_is_full(arr)) {
        printf("Error: Array is FULL\n");
        return;
    }

    arr->data[arr->rear] = data;

    arr->rear++;

    if(arr->rear == arr->allocated)
        arr->rear = 0;

    arr->size++;
}

data_type circular_array_pop_front(CircularArray *arr) {
    data_type to_remove = arr->data[arr->front];

    arr->data[arr->front] = 0;

    arr->front++;

    arr->size--;

    return to_remove;
}

data_type circular_array_pop_back(CircularArray *arr) {
    arr->rear--;

    data_type to_remove = arr->data[arr->rear];

    arr->data[arr->rear] = 0;

    arr->size--;

    return to_remove; 
}

void circular_arry_print(CircularArray *arr) {
    int curr = arr->front;

    for(int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[curr]);
        curr++;

        if(curr == arr->allocated)
            curr = 0;
    }
}
