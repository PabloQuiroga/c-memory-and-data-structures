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

int ll_insert_tail(LinkedList *list, void *element) {
    if (list == NULL) return -1;

    // 1. Crear el nuevo nodo
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return -1;

    new_node->data = element;
    new_node->next = NULL; // Como será el último, no apunta a nadie

    // 2. Caso especial: si la lista está vacía
    if (list->head == NULL) {
        list->head = new_node;
        list->size++;
        return 0;
    }

    // 3. Recorrer la lista hasta encontrar el último nodo
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    // 4. Enganchar el nuevo nodo al final
    current->next = new_node;
    list->size++;

    return 0;
}

size_t ll_get_size(LinkedList *list) {
    if (list == NULL) return 0;
    return list->size;
}

int ll_get(LinkedList *list, size_t index, void **out_element) {
    if (list == NULL || out_element == NULL) return -1;

    Node *current = list->head;
    size_t current_index = 0;

    // Caminamos por la lista hasta llegar al índice deseado
    while (current != NULL) {
        if (current_index == index) {
            *out_element = current->data;
            return 0; // Éxito: encontramos el elemento
        }
        current = current->next;
        current_index++;
    }

    return -1; // Error: El índice está fuera de rango (llegamos al final de la lista)
}

int ll_remove(LinkedList *list, size_t index) {
    if (list == NULL || list->head == NULL) return -1;

    Node *current = list->head;
    Node *previous = NULL;
    size_t current_index = 0;

    // 1. Buscar el nodo a eliminar y mantener el rastro del anterior
    while (current != NULL && current_index < index) {
        previous = current;
        current = current->next;
        current_index++;
    }

    // Si current es NULL, el índice estaba fuera de rango
    if (current == NULL) return -1;

    // 2. Caso Especial: Eliminar la cabeza (head)
    if (previous == NULL) {
        list->head = current->next;
    } else {
        // Caso General: Saltamos el nodo actual conectando el anterior con el siguiente
        previous->next = current->next;
    }

    // 3. Liberar la memoria del nodo eliminado y actualizar tamaño
    free(current);
    list->size--;

    return 0;
}