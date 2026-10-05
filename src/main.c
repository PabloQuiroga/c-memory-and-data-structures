//
// Created by Pablo Quiroga on 04/10/2026.
//

#include <stdio.h>
#include "test_framework.h"

// Declaramos los tests que están en tests.c
int test_da_create();
int test_da_add_and_resize();
int test_da_get();
int test_da_remove();

int main() {
    printf("=== RUNNING DYNAMIC ARRAY UNIT TESTS ===\n");

    RUN_TEST(test_da_create);
    RUN_TEST(test_da_add_and_resize);
    RUN_TEST(test_da_get);
    RUN_TEST(test_da_remove);

    printf("========================================\n");
    printf("All tests completed.\n");

    return 0;
}