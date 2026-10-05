//
// Created by Pablo Quiroga on 04/10/2026.
//

#include <stdio.h>

#include "linked_list.h"
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

    // return 0;

    printf("\n\n=== TESTING LINKED LIST ===\n");
    LinkedList *my_list = NULL;
    if (ll_create(&my_list) != 0) {
        printf("Error creating list\n");
        return 1;
    }

    int v1 = 100, v2 = 200, v3 = 300;

    printf("Inserting 100 at head... ");
    ll_insert_head(my_list, &v1);
    printf("Success! Size: %zu\n", ll_get_size(my_list));

    printf("Inserting 200 at head... ");
    ll_insert_head(my_list, &v2);
    printf("Success! Size: %zu\n", ll_get_size(my_list));

    printf("Inserting 300 at tail... ");
    ll_insert_tail(my_list, &v3);
    printf("Success! Size: %zu\n", ll_get_size(my_list));

    // El orden debería ser: 200 -> 100 -> 300
    printf("Final list size: %zu\n", ll_get_size(my_list));

    printf("\n--- Verifying Linked List elements ---\n");
    void *element_ptr = NULL;
    for (size_t i = 0; i < ll_get_size(my_list); i++) {
        if (ll_get(my_list, i, &element_ptr) == 0) {
            printf("Index %zu: %d\n", i, *(int *)element_ptr);
               }
    }

    printf("\nRemoving element at index 1...\n");
    if (ll_remove(my_list, 1) == 0) {
        printf("Success! New size: %zu\n", ll_get_size(my_list));
    }

    printf("Verifying after removal:\n");
    for (size_t i = 0; i < ll_get_size(my_list); i++) {
        if (ll_get(my_list, i, &element_ptr) == 0) {
            printf("Index %zu: %d\n", i, *(int *)element_ptr);
               }
    }

    ll_destroy(my_list);
    printf("List destroyed. Memory freed.\n");
}