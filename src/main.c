//
// Created by Pablo Quiroga on 04/10/2026.
//

#include "test_framework.h"

// Declaramos los tests que están en tests.c
int test_da_create();
int test_da_add_and_resize();
int test_da_get();
int test_da_remove();
int test_da_create_invalid_capacity();
int test_da_create_null_pointer();
int test_da_get_null_output();
int test_da_remove_clears_reference();
int test_da_get_out_of_bounds();
int test_da_remove_empty_array();
int test_da_edge_cases();

int test_ll_create_destroy();
int test_ll_destroy_null();
int test_ll_create_null_pointer();
int test_ll_insertions();
int test_ll_remove();
int test_ll_edge_cases();
int test_ll_get_out_of_bounds();
int test_ll_get_null_output();
int test_ll_null_elements();
int test_ll_size_consistency();
int test_ll_remove_head();
int test_ll_remove_tail();
int test_ll_remove_out_of_bounds();
int test_ll_get_clears_output_on_error();

int test_stack_basic_operations();
int test_stack_edge_cases();
int test_stack_null_elements();
int test_stack_create_null_pointer();
int test_stack_push_null_stack();
int test_stack_pop_null_stack();
int test_stack_peek_null_stack();
int test_stack_peek_null_output();
int test_stack_pop_null_output();
int test_stack_destroy_null();
int test_stack_is_empty_null();

int test_ht_basic_operations();
int test_ht_collisions();
int test_ht_remove();
int test_ht_edge_cases();


int main() {
    printf("=== RUNNING DYNAMIC ARRAY UNIT TESTS ===\n");

    RUN_TEST(test_da_create);
    RUN_TEST(test_da_add_and_resize);
    RUN_TEST(test_da_get);
    RUN_TEST(test_da_remove);
    RUN_TEST(test_da_create_invalid_capacity);
    RUN_TEST(test_da_create_null_pointer);
    RUN_TEST(test_da_get_null_output);
    RUN_TEST(test_da_remove_clears_reference);
    RUN_TEST(test_da_get_out_of_bounds);
    RUN_TEST(test_da_remove_empty_array);
    RUN_TEST(test_da_edge_cases);

    printf("========================================\n");

    printf("\n=== RUNNING LINKED LIST UNIT TESTS ===\n");
    RUN_TEST(test_ll_create_destroy);
    RUN_TEST(test_ll_destroy_null);
    RUN_TEST(test_ll_insertions);
    RUN_TEST(test_ll_remove);
    RUN_TEST(test_ll_create_null_pointer);
    RUN_TEST(test_ll_edge_cases);
    RUN_TEST(test_ll_get_out_of_bounds);
    RUN_TEST(test_ll_get_null_output);
    RUN_TEST(test_ll_null_elements);
    RUN_TEST(test_ll_size_consistency);
    RUN_TEST(test_ll_remove_head);
    RUN_TEST(test_ll_remove_tail);
    RUN_TEST(test_ll_remove_out_of_bounds);
    RUN_TEST(test_ll_get_clears_output_on_error);

    printf("========================================\n");

    printf("\n=== RUNNING STACK UNIT TESTS ===\n");
    RUN_TEST(test_stack_basic_operations);
    RUN_TEST(test_stack_edge_cases);
    RUN_TEST(test_stack_null_elements);
    RUN_TEST(test_stack_create_null_pointer);
    RUN_TEST(test_stack_push_null_stack);
    RUN_TEST(test_stack_pop_null_stack);
    RUN_TEST(test_stack_peek_null_stack);
    RUN_TEST(test_stack_peek_null_output);
    RUN_TEST(test_stack_pop_null_output);
    RUN_TEST(test_stack_destroy_null);
    RUN_TEST(test_stack_is_empty_null);

    printf("================================\n");

    printf("\n=== RUNNING HASH TABLE UNIT TESTS ===\n");
    RUN_TEST(test_ht_basic_operations);
    RUN_TEST(test_ht_collisions);
    RUN_TEST(test_ht_remove);
    RUN_TEST(test_ht_edge_cases);

    printf("======================================\n");

    printf("All tests completed.\n");
}