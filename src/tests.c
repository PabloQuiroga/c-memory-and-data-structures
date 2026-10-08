//
// Created by Pablo Quiroga on 05/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "hash_table.h"
#include "linked_list.h"
#include "stack.h"
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

// TEST 4: Verificar la eliminación y el desplazamiento de elementos
int test_da_remove() {
    DynamicArray *array = NULL;
    da_create(&array, 10);

    int v1 = 10, v2 = 20, v3 = 30;
    da_add(array, &v1); // Index 0
    da_add(array, &v2); // Index 1
    da_add(array, &v3); // Index 2

    // Eliminamos el elemento del medio (valor 20 en index 1)
    int result = da_remove(array, 1);

    ASSERT_TRUE(result == 0, "da_remove should return 0");
    ASSERT_TRUE(array->size == 2, "Size should decrease to 2");

    // Verificamos que el elemento en index 1 ahora sea el valor 30 (desplazamiento)
    void *out = NULL;
    da_get(array, 1, &out);
    ASSERT_TRUE(*(int*)out == 30, "Element at index 1 should now be 30");

    // Probar eliminación fuera de rango
    int err_result = da_remove(array, 100);
    ASSERT_TRUE(err_result == -1, "da_remove should return -1 for out-of-bounds");

    da_destroy(array);
    return 1;
}

// TEST 5: Verificar la creación y destrucción de la lista
int test_ll_create_destroy() {
    LinkedList *list = NULL;
    int result = ll_create(&list);

    ASSERT_TRUE(result == 0, "ll_create should return 0");
    ASSERT_TRUE(list != NULL, "List should not be NULL");
    ASSERT_TRUE(list->head == NULL, "Initial head should be NULL");
    ASSERT_TRUE(list->size == 0, "Initial size should be 0");

    int destroy_result = ll_destroy(list);
    ASSERT_TRUE(destroy_result == 0, "ll_destroy should return 0");

    return 1;
}

// TEST 6: Verificar inserción en cabeza y cola
int test_ll_insertions() {
    LinkedList *list = NULL;
    ll_create(&list);

    int v1 = 10, v2 = 20, v3 = 30;

    ll_insert_head(list, &v1); // List: 10
    ll_insert_head(list, &v2); // List: 20 -> 10
    ll_insert_tail(list, &v3); // List: 20 -> 10 -> 30

    ASSERT_TRUE(list->size == 3, "Size should be 3");

    void *out = NULL;
    ll_get(list, 0, &out);
    ASSERT_TRUE(*(int*)out == 20, "Index 0 should be 20");

    ll_get(list, 2, &out);
    ASSERT_TRUE(*(int*)out == 30, "Index 2 should be 30");

    ll_destroy(list);
    return 1;
}

// TEST 7: Verificar la eliminación y el re-linkeo
int test_ll_remove() {
    LinkedList *list = NULL;
    ll_create(&list);

    int v1 = 10, v2 = 20, v3 = 30;
    ll_insert_tail(list, &v1);
    ll_insert_tail(list, &v2);
    ll_insert_tail(list, &v3);

    // Eliminamos el nodo del medio (index 1, valor 20)
    int result = ll_remove(list, 1);

    ASSERT_TRUE(result == 0, "ll_remove should return 0");
    ASSERT_TRUE(list->size == 2, "Size should be 2");

    void *out = NULL;
    ll_get(list, 1, &out);
    ASSERT_TRUE(*(int*)out == 30, "Index 1 should now be 30");

    ll_destroy(list);
    return 1;
}

// TEST 8: Verificar el ciclo de vida y operaciones básicas del Stack
int test_stack_basic_operations() {
    Stack *stack = NULL;
    int v1 = 10, v2 = 20, v3 = 30;

    // 1. Creación
    ASSERT_TRUE(stack_create(&stack) == 0, "stack_create should return 0");
    ASSERT_TRUE(stack_is_empty(stack), "Stack should be empty initially");

    // 2. Push (LIFO: 10 -> 20 -> 30)
    stack_push(stack, &v1);
    stack_push(stack, &v2);
    stack_push(stack, &v3);
    ASSERT_TRUE(!stack_is_empty(stack), "Stack should not be empty after push");

    // 3. Peek (Debe ser el último que entró: 30)
    void *top = stack_peek(stack);
    ASSERT_TRUE(*(int*)top == 30, "Peek should return the last element (30)");

    // 4. Pop (Saca el 30, ahora el tope es 20)
    void *popped = NULL;
    // Nota: En nuestra implementación actual, pop solo remueve.
    // Para obtener el valor, hacemos peek antes de pop.
    top = stack_peek(stack);
    ASSERT_TRUE(*(int*)top == 30, "Top before pop should be 30");

    // Implementamos la eliminación del tope
    int pop_res = stack_pop(stack, &popped);
    // Nota: Revisando stack.c, stack_pop llama a ll_remove(list, 0)
    ASSERT_TRUE(pop_res == 0, "stack_pop should return 0");

    // 5. Verificar nuevo tope (debe ser 20)
    top = stack_peek(stack);
    ASSERT_TRUE(*(int*)top == 20, "Top after pop should be 20");

    stack_destroy(stack);
    return 1;
}

// TEST 9: Verificar stack vacío y errores
int test_stack_edge_cases() {
    Stack *stack = NULL;
    stack_create(&stack);

    // Intentar hacer peek en stack vacío
    ASSERT_TRUE(stack_peek(stack) == NULL, "Peek on empty stack should return NULL");

    // Intentar hacer pop en stack vacío
    ASSERT_TRUE(stack_pop(stack, NULL) == -1, "Pop on empty stack should return -1");

    stack_destroy(stack);
    return 1;
}

// TEST 10: Verificar inserción y recuperación básica
int test_ht_basic_operations() {
    HashTable *table = NULL;
    ht_create(&table, 10);

    char *key = "Pablo";
    char *val = "Developer";

    ht_insert(table, key, val);

    void *out = NULL;
    int result = ht_get(table, key, &out);

    // COMPARACIÓN CORRECTA: Comparar el puntero recuperado con el puntero original
    ASSERT_TRUE(result == 0, "ht_get should return 0");
    ASSERT_TRUE(out == val, "The pointer retrieved should be the same as the pointer inserted");

    ht_destroy(table);
    return 1;
}

// TEST 11: Verificar el manejo de colisiones (Chaining)
int test_ht_collisions() {
    HashTable *table = NULL;
    ht_create(&table, 1); // Capacidad 1 para forzar colisiones

    char *k1 = "Key1";
    char *v1 = "Val1";
    char *k2 = "Key2";
    char *v2 = "Val2";

    ht_insert(table, k1, v1);
    ht_insert(table, k2, v2);

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 2, "Bucket 0 should have 2 elements");

    void *out = NULL;
    ht_get(table, k1, &out);
    ASSERT_TRUE(out == v1, "Should retrieve Val1 for Key1");

    ht_get(table, k2, &out);
    ASSERT_TRUE(out == v2, "Should retrieve Val2 for Key2");

    ht_destroy(table);
    return 1;
}

// TEST 12: Verificar la eliminación y limpieza
int test_ht_remove() {
    HashTable *table = NULL;
    ht_create(&table, 10);

    char *k = "TestKey";
    char *v = "TestVal";
    ht_insert(table, k, v);

    ASSERT_TRUE(ht_remove(table, k) == 0, "ht_remove should return 0");

    void *out = NULL;
    ASSERT_TRUE(ht_get(table, k, &out) == -1, "Key should no longer exist");

    ht_destroy(table);
    return 1;
}

// TEST 13: Edge Cases - Dynamic Array
int test_da_edge_cases() {
    DynamicArray *array = NULL;
    da_create(&array, 5);

    void *out = NULL;
    // Acceso fuera de rango
    ASSERT_TRUE(da_get(array, 10, &out) == -1, "da_get should fail for out-of-bounds");
    ASSERT_TRUE(da_remove(array, 0) == -1, "da_remove should fail for empty array");

    da_destroy(array);
    return 1;
}

// TEST 14: Edge Cases - Linked List
int test_ll_edge_cases() {
    LinkedList *list = NULL;
    ll_create(&list);

    int val = 10;
    ll_insert_head(list, &val);

    // Eliminar el único elemento
    ASSERT_TRUE(ll_remove(list, 0) == 0, "ll_remove should work for single element");
    ASSERT_TRUE(list->head == NULL, "Head should be NULL after removing only element");
    ASSERT_TRUE(list->size == 0, "Size should be 0");

    // Intentar borrar en lista vacía
    ASSERT_TRUE(ll_remove(list, 0) == -1, "ll_remove should fail for empty list");

    ll_destroy(list);
    return 1;
}

// TEST 15: Edge Cases - Hash Table
int test_ht_edge_cases() {
    HashTable *table = NULL;
    ht_create(&table, 5);

    void *out = NULL;
    // Buscar en tabla vacía
    ASSERT_TRUE(ht_get(table, "NonExistent", &out) == -1, "ht_get should fail for empty table");

    char *k = "Key";
    char *v = "Val";
    ht_insert(table, k, v);

    // Eliminar clave que no existe
    ASSERT_TRUE(ht_remove(table, "WrongKey") == -1, "ht_remove should fail for non-existent key");

    ht_destroy(table);
    return 1;
}