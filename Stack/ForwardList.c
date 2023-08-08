#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardList* forward_list_construct() {
    ForwardList *l = malloc(sizeof(ForwardList));
    l->size = 0;
    l->head = NULL;

    return l;
}

void node_destroy_recursive(Node *n) {
    if(n == NULL) return;

    node_destroy_recursive(n->next);
    free(n);
}

void forward_list_destroy(ForwardList* l) {
    node_destroy_recursive(l->head);
    free(l);
}

int forward_list_size(ForwardList* l) {
    return l->size;
}

void forward_list_push_front(ForwardList* l, data_type val) {
    Node *n = node_construct(val, l->head);
    l->head = n;

    l->size++;
}

void forward_list_print(ForwardList* l, void (*print_fn)(data_type)) {
    Node *n = l->head;
    
    printf("[");
    int i = 0;
    while(n != NULL) {
        print_fn(n->value);
        if(i != l->size - 1)
            printf(", ");
        
        n = n->next;

        i++;
    }
    
    printf("]\n");

    l->size++;
}

data_type forward_list_get_recursive(Node *n, int i) {
    if(i == 0)
        return n->value;

    return forward_list_get_recursive(n->next, i - 1);
}

data_type forward_list_get(ForwardList* l, int i) {
    return forward_list_get_recursive(l->head, i);
}

data_type forward_list_pop_front(ForwardList* l) {
    data_type removed = l->head->value;
    l->head = l->head->next;
    l->size--;

    return removed;
}

ForwardList* forward_list_reverse(ForwardList* l) {
    ForwardList *r = forward_list_construct();
    
    Node *curr = l->head;
    while(curr != NULL) {
        forward_list_push_front(r, curr->value);
        curr = curr->next;
    }

    return r;
}

void forward_list_remove(ForwardList* l, data_type val) {
    if(l->head == NULL) return;

    Node *prev = NULL;
    Node *curr = l->head;
    
    while(curr) {
        int remove = 0;
        if(curr->value == val) {
            if(!prev)
                l->head = curr->next;
            else
                prev->next = curr->next;
            remove = 1;
            l->size--;
        }
        else
            prev = curr;
        
        Node *to_remove = curr;
        curr = curr->next;

        if(remove)
            free(to_remove);
    }
}

void forward_list_cat(ForwardList* l, ForwardList* m) {
    Node *curr = m->head;

    while(curr != NULL) {
        forward_list_push_front(l, curr->value);
        curr = curr->next;
    }
}