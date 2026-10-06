//
// Created by Pablo Quiroga on 06/10/2026.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "linked_list.h"
#include <stddef.h>

// La entrada de la tabla: guarda la clave y el valor juntos
typedef struct {
    void *key;
    void *value;
} HashEntry;

// La Tabla de Hash: un arreglo de listas enlazadas
typedef struct {
    LinkedList **buckets; // Arreglo de punteros a LinkedList
    size_t capacity;       // Número de cubetas (buckets)
} HashTable;

// API de la Librería
int ht_create(HashTable **table, size_t capacity);
int ht_destroy(HashTable *table);
int ht_insert(HashTable *table, void *key, void *value);
int ht_get(HashTable *table, void *key, void **out_value);
int ht_remove(HashTable *table, void *key);

#endif
