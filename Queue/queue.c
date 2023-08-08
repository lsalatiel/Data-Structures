#include "queue.h"
#include <stdlib.h>
#include "forward_list.h"

struct Queue {
    ForwardList *list;
};

Queue *queue_construct() {
    Queue *queue = (Queue *)calloc(1, sizeof(Queue));
    queue->list = forward_list_construct();
    return queue;
}

void queue_enqueue(Queue *queue, data_type value) {
    forward_list_push_back(queue->list, value);
}

data_type queue_dequeue(Queue *queue) {
    return forward_list_pop_front(queue->list);
}

int queue_empty(Queue *queue) {
    return forward_list_size(queue->list) == 0;
}

void queue_destroy(Queue *queue) {
    forward_list_destroy(queue->list);
    free(queue);
}