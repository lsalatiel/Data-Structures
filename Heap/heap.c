#include "heap.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    void *data;
    double priority;
} HeapNode;

struct Heap {
    HeapNode **nodes;
    int size;
    int capacity;
    CmpFunction compare;
};

HeapNode *heap_node_construct(void *data, double priority) {
    HeapNode *node = malloc(sizeof(HeapNode));

    node->data = data;
    node->priority = priority;
    
    return node;
}

Heap *heap_construct(CmpFunction compare) {
    Heap *heap = malloc(sizeof(Heap));

    heap->size = 0;
    heap->capacity = INITIAL_CAPACITY;

    heap->nodes = malloc(INITIAL_CAPACITY * sizeof(HeapNode *));

    heap->compare = compare;

    return heap;
}

void heap_destroy(Heap *heap) {
    for(int i = 0; i < heap->size; i++) {
        free(heap->nodes[i]);
    }

    free(heap->nodes);
    free(heap);
}

void _swap_nodes(Heap *heap, int index1, int index2) {
    HeapNode *temp = heap->nodes[index1];
    heap->nodes[index1] = heap->nodes[index2];
    heap->nodes[index2] = temp;
}

void _heapify_up(Heap *heap, int index) {
    int parent = (index - 1) / 2;

    if(heap->nodes[parent]->priority > heap->nodes[index]->priority) {
        _swap_nodes(heap, index, parent);
        return _heapify_up(heap, parent);
    }
}

void _heapify_down(Heap *heap, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if(left >= 0 && left < heap->size && heap->nodes[left]->priority < heap->nodes[index]->priority)
        min = left;
    if(right >= 0 && right < heap->size && heap->nodes[right]->priority < heap->nodes[min]->priority)
        min = right;

    if(min != index) {
        _swap_nodes(heap, index, min);
        _heapify_down(heap, min);
    }
}

void *heap_push(Heap *heap, void *data, double priority) {
    int index = -1;

    for(int i = 0; i < heap->size; i++) {
        if(!heap->compare(heap->nodes[i]->data, data))
            index = i;
    }

    if(index != -1) {
        if(priority >= heap->nodes[index]->priority)
            return data;
        
        heap->nodes[index]->priority = priority;

        if((index - 1) / 2 >= 0 && heap->nodes[(index - 1) / 2]->priority > priority)
            _heapify_up(heap, index);
        else
            _heapify_down(heap, index);
        
        return data;
    }

    if(heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = realloc(heap->nodes, heap->capacity * sizeof(HeapNode *));
    }

    HeapNode *node = heap_node_construct(data, priority);

    heap->nodes[heap->size] = node;

    _heapify_up(heap, heap->size);

    heap->size++;

    return NULL;
}

void *heap_pop(Heap *heap) {
    HeapNode *root = heap->nodes[0];

    heap->nodes[0] = heap->nodes[heap->size - 1];

    heap->size--;

    _heapify_down(heap, 0);

    void *data = root->data;
    free(root);

    return data;
}

bool heap_empty(Heap *heap) {
    return heap->size == 0;
}

void *heap_min(Heap *heap) {
    return heap->nodes[0]->data;
}

double heap_min_priority(Heap *heap) {
    return heap->nodes[0]->priority;
}
