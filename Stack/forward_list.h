#ifndef FORWARD_LIST_H_
#define FORWARD_LIST_H_

#include "Node.h"

typedef struct {
    int size;
    Node *head;
} ForwardList;

// cria uma lista
ForwardList* forward_list_construct();

// retorna o número de elementos na lista
int forward_list_size(ForwardList* l);

// adiciona um item no início da lista
void forward_list_push_front(ForwardList* l, data_type val);

// mostra a lista na tela
void forward_list_print(ForwardList* l, void (*print_fn)(data_type));

// retorna o i-ésimo elemento da lista
data_type forward_list_get(ForwardList* l, int i);

// remove o primeiro elemento
data_type forward_list_pop_front(ForwardList* l);

// retorna uma lista contendo o reverso de outra
ForwardList* forward_list_reverse(ForwardList* l);

// libera o espaço alocado para a lista
void forward_list_destroy(ForwardList* l);

// remove todas as ocorrências de um valor da lista
void forward_list_remove(ForwardList* l, data_type val);

// adiciona os itens da lista m no início da lista l
void forward_list_cat(ForwardList* l, ForwardList* m);

#endif
