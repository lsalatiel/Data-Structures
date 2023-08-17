#ifndef LIST_H_
#define LIST_H_

#include "Node.h"

#include <stdbool.h>

typedef struct {
    Node *head;
    Node *last;
    int size;
} List;

typedef struct {
    Node *current;
} ListIterator;

// cria uma lista
List* list_construct();

// retorna o número de elementos na lista
int list_size(List* l);

// adiciona um item no início da lista
void list_push_front(List* l, data_type val);

// mostra a lista na tela
void list_print(List* l, void (*print_fn)(data_type));

// retorna o i-ésimo elemento da lista
data_type list_get(List* l, int i);

// remove o primeiro elemento
data_type list_pop_front(List* l);

// retorna uma lista contendo o reverso de outra
List* list_reverse(List* l);

// libera o espaço alocado para a lista
void list_destroy(List* l);

// remove todas as ocorrências de um valor da lista
void list_remove(List* l, data_type val);

// adiciona os itens da lista m no início da lista l
void list_cat(List* l, List* m);

// insere um elemento ao final 
void list_push_back(List *l, data_type data);

// remove e retorna o último elemento
data_type list_pop_back(List *l);

void list_print_reverse(List *l, void (*print_fn)(data_type));

// iterator

// cria um iterador para percorrer a lista do início para o final.
ListIterator *list_front_iterator(List *l);

// cria um iterador para percorrer a lista do final para o início.
ListIterator *list_back_iterator(List *l);

// retorna o elemento do nó atual e move o iterador para o próximo nó.
data_type *list_iterator_next(ListIterator *it);

// retorna o elemento do nó atual e move o iterador para o nó anterior.
data_type *list_iterator_previous(ListIterator *it);

// verifica se o iterador chegou ao final da lista
bool list_iterator_is_over(ListIterator *it);

// libera a memória alocada para o iterador
void list_iterator_destroy(ListIterator *it);


#endif
