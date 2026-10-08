//
// Created by Pablo Quiroga on 06/10/2026.
//

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

// Función de Hash DJB2: Convierte un string en un número grande
static unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

int ht_create(HashTable **table, size_t capacity) {
    *table = (HashTable *)malloc(sizeof(HashTable));
    if (*table == NULL) return -1;

    // Creamos el arreglo de punteros a listas
    (*table)->buckets = (LinkedList **)malloc(capacity * sizeof(LinkedList *));
    if ((*table)->buckets == NULL) {
        free(*table);
        return -1;
    }

    // Inicializamos cada bucket como una lista vacía
    for (size_t i = 0; i < capacity; i++) {
        if (ll_create(&((*table)->buckets[i])) != 0) {
            // Si falla una, debemos destruir todo lo creado hasta ahora
            for (size_t j = 0; j < i; j++) {
                ll_destroy((*table)->buckets[j]);
            }
            free((*table)->buckets);
            free(*table);
            return -1;
        }
    }

    (*table)->capacity = capacity;
    return 0;
}

int ht_destroy(HashTable *table) {
    if (table == NULL) return -1;

    for (size_t i = 0; i < table->capacity; i++) {
        LinkedList *list = table->buckets[i];
        if (list == NULL) continue;

        // Recorremos la lista manualmente para liberar cada HashEntry
        Node *current = list->head;
        while (current != NULL) {
            Node *next = current->next;
            // IMPORTANTE: Liberamos la entrada antes que el nodo
            free(current->data);
            free(current);
            current = next;
        }

        // Liberamos la estructura de la lista
        free(list);
    }

    free(table->buckets);
    free(table);
    return 0;
}

int ht_insert(HashTable *table, void *key, void *value) {
    if (table == NULL || key == NULL || value == NULL) return -1;

    // 1. Calculamos el índice del bucket
    unsigned long hash = hash_function((const char *)key);
    size_t index = hash % table->capacity;

    // 2. Creamos la entrada (HashEntry) que guarda clave y valor
    HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));
    if (entry == NULL) return -1;
    entry->key = key;
    entry->value = value;

    // 3. Insertamos la entrada en la lista del bucket correspondiente
    // Usamos ll_insert_head porque es O(1)
    return ll_insert_head(table->buckets[index], entry);
}

int ht_get(HashTable *table, void *key, void **out_value) {
    if (table == NULL || key == NULL || out_value == NULL) return -1;

    // 1. Calculamos el índice
    unsigned long hash = hash_function((const char *)key);
    size_t index = hash % table->capacity;

    // 2. Recorremos la lista del bucket buscando la clave
    LinkedList *list = table->buckets[index];
    void *entry_ptr = NULL;

    for (size_t i = 0; i < ll_get_size(list); i++) {
        ll_get(list, i, &entry_ptr);
        HashEntry *entry = (HashEntry *)entry_ptr;
        if (entry->key == key) {
            *out_value = entry->value;
            return 0; // ¡Encontrado!
        }
    }

    return -1; // No se encontró la clave
}

int ht_remove(HashTable *table, void *key) {
    if (table == NULL || key == NULL) return -1;

    // 1. Calculamos el índice del bucket
    unsigned long hash = hash_function((const char *)key);
    size_t index = hash % table->capacity;
    LinkedList *list = table->buckets[index];

    // 2. Buscamos el elemento en la lista
    for (size_t i = 0; i < ll_get_size(list); i++) {
        void *entry_ptr = NULL;
        ll_get(list, i, &entry_ptr);
        HashEntry *entry = (HashEntry *)entry_ptr;

        if (entry->key == key) {
            // 3. Liberamos la memoria de la HashEntry antes de remover el nodo
            free(entry);

            // 4. Removemos el nodo de la lista
            return ll_remove(list, i);
        }
    }

    return -1; // Clave no encontrada
}