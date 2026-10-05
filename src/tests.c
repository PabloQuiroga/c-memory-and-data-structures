//
// Created by Pablo Quiroga on 05/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "test_framework.h"

// TEST 1: Verificar que la creación funciona
int test_da_create() {
    DynamicArray *array = NULL;
    int result = da_create(&array, 5);

    ASSERT_TRUE(result == 0, "da_create should return 0");
    ASSERT_TRUE(array != NULL, "Array should not be NULL");
    ASSERT_TRUE(array->capacity == 5, "Capacity should be 5");
    ASSERT_TRUE(array->size == 0, "Initial size should be 0");

    da_destroy(array);
    return 1;
}

// TEST 2: Verificar que el agregado y el crecimiento funcionan
int test_da_add_and_resize() {
    DynamicArray *array = NULL;
    da_create(&array, 2);

    int val1 = 10, val2 = 20, val3 = 30;

    da_add(array, &val1);
    da_add(array, &val2);
    ASSERT_TRUE(array->size == 2, "Size should be 2");
    ASSERT_TRUE(array->capacity == 2, "Capacity should still be 2");

    // Esto debería disparar la redimensión (capacity 2 -> 4)
    da_add(array, &val3);
    ASSERT_TRUE(array->size == 3, "Size should be 3");
    ASSERT_TRUE(array->capacity == 4, "Capacity should have doubled to 4");

    da_destroy(array);
    return 1;
}

// TEST 3: Verificar que el acceso por índice funciona
int test_da_get() {
    DynamicArray *array = NULL;
    da_create(&array, 5);

    int val = 100;
    da_add(array, &val);

    void *out = NULL;
    int result = da_get(array, 0, &out);

    ASSERT_TRUE(result == 0, "da_get should return 0");
    ASSERT_TRUE(*(int*)out == 100, "Value should be 100");

    da_destroy(array);
    return 1;
}