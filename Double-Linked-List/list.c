#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* list_construct() {
    List *l = malloc(sizeof(List));
    l->size = 0;
    l->head = NULL;
    l->last = NULL;

    return l;
}

void node_destroy_recursive(Node *n) {
    if(n == NULL) return;

    node_destroy_recursive(n->next);
    free(n);
}

void list_destroy(List* l) {
    node_destroy_recursive(l->head);
    free(l);
}

int list_size(List* l) {
    return l->size;
}

void list_push_front(List* l, data_type val) {
    Node *n = node_construct(val, NULL, l->head);
    
    if (l->head != NULL) {
        l->head->prev = n;
    }
    l->head = n;
    if (l->last == NULL) {
        l->last = n;
    }

    l->size++;
}

void list_print(List* l, void (*print_fn)(data_type)) {
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

data_type list_get_recursive(Node *n, int i) {
    if(i == 0)
        return n->value;

    return list_get_recursive(n->next, i - 1);
}

data_type list_get(List* l, int i) {
    return list_get_recursive(l->head, i);
}

data_type list_pop_front(List* l) {
    Node *n = l->head;
    l->head = l->head->next;
    data_type removed = n->value;
    node_destroy(n);

    l->size--;

    if(l->size == 1)
        l->last = l->head;

    return removed;
}

List* list_reverse(List* l) {
    List *r = list_construct();
    
    Node *curr = l->head;
    while(curr != NULL) {
        list_push_front(r, curr->value);
        curr = curr->next;
    }

    return r;
}

void list_remove(List* l, data_type val) {
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

void list_cat(List* l, List* m) {
    Node *curr = m->head;

    while(curr != NULL) {
        list_push_front(l, curr->value);
        curr = curr->next;
    }
}

void list_push_back(List *l, data_type data) {
    Node *n = node_construct(data, l->last, NULL);
    
    if(l->last == NULL)
        l->head = l->last = n;
    else
        l->last = l->last->next = n;

    l->size++;
}

data_type list_pop_back(List *l) {
    Node *n = l->last;
    l->last = l->last->prev;
    data_type removed = n->value;
    node_destroy(n);

    l->size--;

    if(l->size == 1)
        l->head = l->last;

    return removed;
}

void list_print_reverse(List *l, void (*print_fn)(data_type)) {
    Node *n = l->last;

    int i = 0;

    printf("[");
    while (n != NULL) {
        print_fn(n->value);
        if(i != l->size - 1)
            printf(", ");
        n = n->prev;

        i++;
    }
    printf("]\n");
}

ListIterator *list_front_iterator(List *l) {
    ListIterator *it = malloc(sizeof(ListIterator));
    it->current = l->head;
    
    return it;
}

ListIterator *list_back_iterator(List *l) {
    ListIterator *it = malloc(sizeof(ListIterator));
    it->current = l->last;
    
    return it;
}

data_type *list_iterator_next(ListIterator *it) {
    data_type* value = &it->current->value;
    it->current = it->current->next;

    return value;
}

data_type *list_iterator_previous(ListIterator *it) {
    data_type* value = &it->current->value;
    it->current = it->current->prev;

    return value;
}

bool list_iterator_is_over(ListIterator *it) {
    return (it->current == NULL);
}

void list_iterator_destroy(ListIterator *it) {
    free(it->current);
    free(it);
}