//
// Created by Pablo Quiroga on 05/10/2026.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// El Nodo: la unidad básica de la lista
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// La Lista: la estructura que gestiona los nodos
typedef struct {
    Node *head;
    size_t size;
} LinkedList;

// API de la Librería
int ll_create(LinkedList **list);
int ll_destroy(LinkedList *list);
int ll_insert_head(LinkedList *list, void *element);
int ll_insert_tail(LinkedList *list, void *element);
int ll_get(LinkedList *list, size_t index, void **out_element);
int ll_remove(LinkedList *list, size_t index);
size_t ll_get_size(LinkedList *list);

#endif