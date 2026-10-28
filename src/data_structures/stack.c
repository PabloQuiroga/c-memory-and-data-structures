//
// Created by Pablo Quiroga on 06/10/2026.
//

#include "stack.h"
#include <stdlib.h>

int stack_create(Stack **stack) {
    // 1. Reservamos memoria para la estructura Stack
    *stack = (Stack *)malloc(sizeof(Stack));
    if (*stack == NULL) return -1;

    // 2. Delegamos la creación de la lista interna a ll_create
    if (ll_create(&((*stack)->internal_list)) != 0) {
        free(*stack);
        return -1;
    }

    return 0;
}

int stack_destroy(Stack *stack) {
    if (stack == NULL) return -1;

    // Delegamos la destrucción de la lista interna
    ll_destroy(stack->internal_list);
    free(stack);
    return 0;
}

int stack_push(Stack *stack, void *element) {
    if (stack == NULL) return -1;
    // El TOP de la pila es la CABEZA de la lista
    return ll_insert_head(stack->internal_list, element);
}

int stack_pop(Stack *stack, void **out_element) {
    if (stack == NULL) return -1;
    // El POP elimina el elemento en la posición 0
    return ll_remove(stack->internal_list, 0);
}

void* stack_peek(Stack *stack) {
    if (stack == NULL) return NULL;
    void *element = NULL;
    if (ll_get(stack->internal_list, 0, &element) == 0) {
        return element;
    }
    return NULL;
}

int stack_is_empty(Stack *stack) {
    if (stack == NULL) return -1;
    return ll_get_size(stack->internal_list) == 0;
}