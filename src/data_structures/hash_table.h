#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "linked_list.h"
#include <stddef.h>

typedef struct {
    char *key;
    void *value;
} HashEntry;

typedef struct {
    LinkedList **buckets;
    size_t capacity;
} HashTable;

int ht_create(HashTable **table, size_t capacity);
int ht_destroy(HashTable *table);
int ht_insert(HashTable *table, const char *key, void *value);
int ht_get(HashTable *table, const char *key, void **out_value);
int ht_remove(HashTable *table, const char *key, void **out_value);

#endif
