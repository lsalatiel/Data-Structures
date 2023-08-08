#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef int data_type;

typedef struct {
    data_type *data;
    int front;
    int rear;
    int allocated;
    int size;
} CircularArray;

CircularArray *circular_array_construct(int size);

void circular_array_destroy(CircularArray *arr);

void circular_array_push_front(CircularArray *arr, data_type data);

void circular_array_push_back(CircularArray *arr, data_type data);

data_type circular_array_pop_front(CircularArray *arr);

data_type circular_array_pop_back(CircularArray *arr);

void circular_arry_print(CircularArray *arr);

#endif
