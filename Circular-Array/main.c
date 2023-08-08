#include "Deque.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Deque *deque = deque_construct(5);

    deque_push_back(deque, 10);
    deque_push_back(deque, 5);
    deque_pop_front(deque);
    deque_push_front(deque, 2);
    deque_push_front(deque, 4);
    deque_push_front(deque, 7);
    deque_push_back(deque, 9);
    deque_pop_front(deque);
    deque_push_back(deque, 1);

    deque_print(deque);

    deque_destroy(deque);

    return 0;
}
