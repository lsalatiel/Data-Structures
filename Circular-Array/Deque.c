#include "Deque.h"
#include "CircularArray.h"
#include <stdlib.h>

struct Deque {
    CircularArray *arr;
};

Deque *deque_construct(int size) {
    Deque *deque = malloc(sizeof(Deque));
    deque->arr = circular_array_construct(size);

    return deque;
}

void deque_destroy(Deque *deque) {
    circular_array_destroy(deque->arr);
    free(deque);
}

void deque_push_front(Deque *deque, data_type data) {
    circular_array_push_front(deque->arr, data);
}

void deque_push_back(Deque *deque, data_type data) {
    circular_array_push_back(deque->arr, data);
}

data_type deque_pop_front(Deque *deque) {
    return circular_array_pop_front(deque->arr);
}

data_type deque_pop_back(Deque *deque) {
    return circular_array_pop_back(deque->arr);
}

void deque_print(Deque *deque) {
    circular_arry_print(deque->arr);
}
