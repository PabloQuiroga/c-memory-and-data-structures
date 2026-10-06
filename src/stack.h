//
// Created by Pablo Quiroga on 06/10/2026.
//

#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

// El Stack envuelve una LinkedList
typedef struct {
    LinkedList *internal_list;
} Stack;

// API de la Pila
int stack_create(Stack **stack);
int stack_destroy(Stack *stack);
int stack_push(Stack *stack, void *element);
int stack_pop(Stack *stack, void **out_element);
void* stack_peek(Stack *stack);
int stack_is_empty(Stack *stack);

#endif
