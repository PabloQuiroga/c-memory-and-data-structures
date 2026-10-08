//
// Created by Pablo Quiroga on 04/10/2026.
//

#include <stdio.h>

#include "hash_table.h"
#include "linked_list.h"
#include "test_framework.h"

// Declaramos los tests que están en tests.c
int test_da_create();
int test_da_add_and_resize();
int test_da_get();
int test_da_remove();
int test_ll_create_destroy();
int test_ll_insertions();
int test_ll_remove();
int test_stack_basic_operations();
int test_stack_edge_cases();

int main() {
    printf("=== RUNNING DYNAMIC ARRAY UNIT TESTS ===\n");

    RUN_TEST(test_da_create);
    RUN_TEST(test_da_add_and_resize);
    RUN_TEST(test_da_get);
    RUN_TEST(test_da_remove);

    printf("========================================\n");

    printf("\n=== RUNNING LINKED LIST UNIT TESTS ===\n");
    RUN_TEST(test_ll_create_destroy);
    RUN_TEST(test_ll_insertions);
    RUN_TEST(test_ll_remove);

    printf("========================================\n");

    printf("\n=== RUNNING STACK UNIT TESTS ===\n");
    RUN_TEST(test_stack_basic_operations);
    RUN_TEST(test_stack_edge_cases);

    printf("================================\n");

    printf("All tests completed.\n");

    printf("\n\n=== TESTING HASH TABLE ===\n");
    HashTable *my_table = NULL;
    ht_create(&my_table, 5);

    char *key1 = "Pablo";
    char *val1 = "Developer";
    char *key2 = "Claude";
    char *val2 = "AI Assistant";

    printf("Inserting Pablo... ");
    ht_insert(my_table, key1, val1);
    printf("Success!\n");

    printf("Inserting Claude... ");
    ht_insert(my_table, key2, val2);
    printf("Success!\n");

    void *res_val = NULL;
    if (ht_get(my_table, key1, &res_val) == 0) {
        printf("Found Pablo: %s\n", (char *)res_val);
    }

    if (ht_get(my_table, key2, &res_val) == 0) {
        printf("Found Claude: %s\n", (char *)res_val);
           }

    printf("Removing Pablo... ");
    ht_remove(my_table, key1);
    if (ht_get(my_table, key1, &res_val) != 0) {
        printf("Success! Pablo is gone.\n");
    }

    ht_destroy(my_table);
    printf("Hash Table destroyed. Memory freed.\n");

    return 0;
}