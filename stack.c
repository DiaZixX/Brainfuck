#include "stack.h"

stack* init_stack(){
    stack* new_stack = (stack *) malloc(sizeof(stack));
    if (new_stack == NULL){
        exit(1);
    }
    new_stack->first = NULL;
    return new_stack;
}

bool is_empty(stack* s){
    return s->first == NULL;
}

void push(stack* s, type_t val){
    elem* new_elem = (elem *) malloc(sizeof(elem));
    if (new_elem == NULL){
        exit(1);
    }
    new_elem->val = val;
    new_elem->next = s->first;
    s->first = new_elem;
}

type_t pop(stack* s){
    assert(!is_empty(s));
    elem* temp = s->first;
    type_t value = s->first->val;
    s->first = s->first->next;
    free(temp);
    return value;
}

type_t peek(stack* s){
    type_t value = pop(s);
    push(s, value);
    return value;
}

void free_stack(stack* s){
    while (!is_empty(s)) {
        pop(s);
    }
    free(s);
}
