//
// Created by Pablo Quiroga on 05/10/2026.
//

#include "linked_list.h"
#include <stdlib.h>

int ll_create(LinkedList **list) {
    // Reservamos memoria para la estructura de gestión de la lista
    *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (*list == NULL) return -1;

    (*list)->head = NULL; // La lista comienza vacía
    (*list)->size = 0;
    return 0;
}

int ll_destroy(LinkedList *list) {
    if (list == NULL) return -1;

    Node *current = list->head;
    Node *next_node = NULL;

    // Liberamos cada nodo uno por uno para evitar memory leaks
    while (current != NULL) {
        next_node = current->next; // Guardamos el siguiente
        free(current);            // Borramos el actual
        current = next_node;       // Avanzamos
    }

    free(list); // Liberamos la estructura contenedora
    return 0;
}

int ll_insert_head(LinkedList *list, void *element) {
    if (list == NULL) return -1;

    // 1. Creamos el nuevo nodo
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return -1; // Error de memoria

    // 2. Asignamos el dato y el puntero al siguiente
    new_node->data = element;
    new_node->next = list->head; // El nuevo nodo apunta al que antes era el primero

    // 3. Actualizamos la cabeza de la lista
    list->head = new_node;
    list->size++;

    return 0;
}