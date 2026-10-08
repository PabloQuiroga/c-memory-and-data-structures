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
int test_ht_basic_operations();
int test_ht_collisions();
int test_ht_remove();

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

    printf("\n=== RUNNING HASH TABLE UNIT TESTS ===\n");
    RUN_TEST(test_ht_basic_operations);
    RUN_TEST(test_ht_collisions);
    RUN_TEST(test_ht_remove);

    printf("======================================\n");

    printf("All tests completed.\n");
}