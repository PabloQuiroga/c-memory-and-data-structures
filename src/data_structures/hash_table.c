//
// Created by Pablo Quiroga on 06/10/2026.
//

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Función de Hash DJB2: Convierte un string en un número grande
static unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    unsigned char c;

    while ((c = (unsigned char)*str++) != '\0') {
        hash = hash * 33 + c;
    }

    return hash;
}

int ht_create(HashTable **table, size_t capacity) {
    if (table == NULL || capacity == 0) return -1;

    *table = NULL;

    if (capacity > SIZE_MAX / sizeof(LinkedList *)) return -1;

    HashTable *new_table = malloc(sizeof(HashTable));
    if (new_table == NULL) return -1;

    new_table->buckets = calloc(capacity, sizeof(LinkedList *));
    if (new_table->buckets == NULL) {
        free(new_table);
        return -1;
    }

    new_table->capacity = capacity;
    *table = new_table;

    return 0;
}

int ht_destroy(HashTable *table) {
    if (table == NULL) return -1;

    for (size_t i = 0; i < table->capacity; i++) {
        LinkedList *list = table->buckets[i];

        if (list == NULL) continue;

        Node *current = list->head;

        while (current != NULL) {
            HashEntry *entry = current->data;

            free(entry->key);
            free(entry);

            current = current->next;
        }

        if (ll_destroy(list) != 0) return -1;
    }

    free(table->buckets);
    free(table);

    return 0;
}

int ht_insert(HashTable *table, const char *key, void *value) {
    if (table == NULL || key == NULL) return -1;

    unsigned long hash = hash_function(key);
    size_t index = hash % table->capacity;

    LinkedList *list = table->buckets[index];

    // Update an existing entry.
    if (list != NULL) {
        for (size_t i = 0; i < ll_get_size(list); i++) {
            void *entry_ptr = NULL;

            if (ll_get(list, i, &entry_ptr) != 0) return -1;

            HashEntry *entry = entry_ptr;

            if (strcmp(entry->key, key) == 0) {
                entry->value = value;
                return 0;
            }
        }
    }

    // Allocate the new entry and copy its key.
    HashEntry *entry = malloc(sizeof(HashEntry));
    if (entry == NULL) return -1;

    size_t key_length = strlen(key) + 1;
    entry->key = malloc(key_length);

    if (entry->key == NULL) {
        free(entry);
        return -1;
    }

    memcpy(entry->key, key, key_length);
    entry->value = value;

    // Create the bucket list only when needed.
    if (list == NULL) {
        if (ll_create(&list) != 0) {
            free(entry->key);
            free(entry);
            return -1;
        }

        table->buckets[index] = list;
    }

    if (ll_insert_head(list, entry) != 0) {
        free(entry->key);
        free(entry);

        if (ll_get_size(list) == 0) {
            ll_destroy(list);
            table->buckets[index] = NULL;
        }

        return -1;
    }

    return 0;
}

int ht_get(HashTable *table, const char *key, void **out_value) {
    if (out_value == NULL) return -1;

    *out_value = NULL;

    if (table == NULL || key == NULL) return -1;

    unsigned long hash = hash_function(key);
    size_t index = hash % table->capacity;

    LinkedList *list = table->buckets[index];

    if (list == NULL) return -1;

    for (size_t i = 0; i < ll_get_size(list); i++) {
        void *entry_ptr = NULL;

        if (ll_get(list, i, &entry_ptr) != 0) return -1;

        HashEntry *entry = entry_ptr;

        if (strcmp(entry->key, key) == 0) {
            *out_value = entry->value;
            return 0;
        }
    }

    return -1;
}

int ht_remove(HashTable *table, const char *key, void **out_value) {
    if (out_value == NULL) return -1;

    *out_value = NULL;

    if (table == NULL || key == NULL) return -1;

    unsigned long hash = hash_function(key);
    size_t index = hash % table->capacity;

    LinkedList *list = table->buckets[index];

    if (list == NULL) return -1;

    for (size_t i = 0; i < ll_get_size(list); i++) {
        void *entry_ptr = NULL;

        if (ll_get(list, i, &entry_ptr) != 0) return -1;

        HashEntry *entry = entry_ptr;

        if (strcmp(entry->key, key) == 0) {
            void *value = entry->value;

            if (ll_remove(list, i) != 0) return -1;

            free(entry->key);
            free(entry);

            if (ll_get_size(list) == 0) {
                if (ll_destroy(list) != 0) return -1;
                table->buckets[index] = NULL;
            }

            *out_value = value;
            return 0;
        }
    }

    return -1;
}