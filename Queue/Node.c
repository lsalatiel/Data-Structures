#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

Node *node_construct(data_type value, Node *next) {
    Node *n = malloc(sizeof(Node));
    
    n->value = value;
    n->next = next;

    return n;
}

void node_destroy(Node *n) {
    free(n);
}
