#include "stack.h"
#include "forward_list.h"
#include <stdlib.h>

struct Stack {
    ForwardList *list;
};

Stack *stack_construct() {
    Stack *stack = malloc(sizeof(Stack));
    stack->list = forward_list_construct();
    return stack;
}

void stack_destroy(Stack *s) {
    forward_list_destroy(s->list);
    free(s);
}

void stack_push(Stack *stack, data_type data) {
    forward_list_push_front(stack->list, data);
}

data_type stack_pop(Stack *stack) {
    data_type data = forward_list_pop_front(stack->list);
    return data;
}

int stack_empty(Stack *s) {
    if(forward_list_size(s->list) == 0) 
        return 1;

    return 0;
}