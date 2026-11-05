//
// Created by Pablo Quiroga on 06/10/2026.
//

#include "stack.h"
#include <stdlib.h>

int stack_create(Stack **stack) {
    if (stack == NULL) return -1;

    *stack = NULL;

    *stack = (Stack *)malloc(sizeof(Stack));
    if (*stack == NULL) return -1;

    if (ll_create(&((*stack)->internal_list)) != 0) {
        free(*stack);
        *stack = NULL;
        return -1;
    }

    return 0;
}

int stack_destroy(Stack *stack) {
    if (stack == NULL) return -1;

    int result = ll_destroy(stack->internal_list);
    if (result != 0) return -1;

    free(stack);
    return 0;
}

int stack_push(Stack *stack, void *element) {
    if (stack == NULL) return -1;
    // El TOP de la pila es la CABEZA de la lista
    return ll_insert_head(stack->internal_list, element);
}

int stack_pop(Stack *stack, void **out_element) {
    if (out_element == NULL) return -1;

    *out_element = NULL;

    if (stack == NULL) return -1;

    if (ll_get(stack->internal_list, 0, out_element) != 0) {
        return -1;
    }

    if (ll_remove(stack->internal_list, 0) != 0) {
        *out_element = NULL;
        return -1;
    }

    return 0;
}

int stack_peek(Stack *stack, void **out_element) {
    if (out_element == NULL) return -1;

    *out_element = NULL;

    if (stack == NULL) return -1;

    return ll_get(stack->internal_list, 0, out_element);
}

int stack_is_empty(Stack *stack) {
    if (stack == NULL || stack->internal_list == NULL) {
        return -1;
    }

    return ll_get_size(stack->internal_list) == 0;
}