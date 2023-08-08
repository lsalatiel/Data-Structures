#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "CircularArray.h"

typedef struct Deque Deque;

Deque *deque_construct(int size);

void deque_destroy(Deque *deque);

void deque_push_front(Deque *deque, data_type data);

void deque_push_back(Deque *deque, data_type data);

data_type deque_pop_front(Deque *deque);

data_type deque_pop_back(Deque *deque);

void deque_print(Deque *deque);

#endif
