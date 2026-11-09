//
// Created by Pablo Quiroga on 05/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "data_structures/dynamic_array.h"
#include "data_structures/hash_table.h"
#include "data_structures/linked_list.h"
#include "data_structures/stack.h"
#include "test_framework.h"

// Dynamic Array: Verificar que la creación funciona
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

// Dynamic Array: Verificar que el agregado y el crecimiento funcionan
int test_da_add_and_resize() {
    DynamicArray *array = NULL;

    ASSERT_TRUE(da_create(&array, 2) == 0,
                "da_create should succeed");

    int val1 = 10, val2 = 20, val3 = 30;

    ASSERT_TRUE(da_add(array, &val1) == 0,
                "First insertion should succeed");

    ASSERT_TRUE(da_add(array, &val2) == 0,
                "Second insertion should succeed");

    ASSERT_TRUE(array->size == 2, "Size should be 2");
    ASSERT_TRUE(array->capacity == 2, "Capacity should still be 2");

    // Esto debería disparar la redimensión (capacity 2 -> 4)
    ASSERT_TRUE(da_add(array, &val3) == 0,
                "Third insertion should succeed");

    ASSERT_TRUE(array->size == 3, "Size should be 3");
    ASSERT_TRUE(array->capacity == 4,
                "Capacity should have doubled to 4");

    da_destroy(array);
    return 1;
}

// Dynamic Array: Verificar que el acceso por índice funciona
int test_da_get() {
    DynamicArray *array = NULL;

    ASSERT_TRUE(da_create(&array, 5) == 0,
                "da_create should succeed");

    int val = 100;

    ASSERT_TRUE(da_add(array, &val) == 0,
                "Insertion should succeed");

    void *out = NULL;
    int result = da_get(array, 0, &out);

    ASSERT_TRUE(result == 0, "da_get should return 0");
    ASSERT_TRUE(*(int*)out == 100, "Value should be 100");

    da_destroy(array);
    return 1;
}

// Dynamic Array: Verificar la eliminación y el desplazamiento de elementos
int test_da_remove() {
    DynamicArray *array = NULL;

    ASSERT_TRUE(da_create(&array, 10) == 0,
                "da_create should succeed");

    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(da_add(array, &v1) == 0, "First insertion should succeed");
    ASSERT_TRUE(da_add(array, &v2) == 0, "Second insertion should succeed");
    ASSERT_TRUE(da_add(array, &v3) == 0, "Third insertion should succeed");

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

// Dynamic Array: Verificar que la creación rechaza una capacidad inicial cero
int test_da_create_invalid_capacity() {
    DynamicArray *array = NULL;

    int result = da_create(&array, 0);

    ASSERT_TRUE(result == -1, "da_create should return -1 for zero capacity");
    ASSERT_TRUE(array == NULL, "Array should remain NULL");

    return 1;
}

// Dynamic Array: Verificar que la creación rechaza un puntero de salida NULL
int test_da_create_null_pointer() {
    int result = da_create(NULL, 5);

    ASSERT_TRUE(result == -1, "da_create should return -1 for NULL output pointer");

    return 1;
}

// Dynamic Array: Verificar que da_get rechaza un puntero de salida NULL
int test_da_get_null_output() {
    DynamicArray *array = NULL;

    int create_result = da_create(&array, 5);

    ASSERT_TRUE(create_result == 0, "da_create should return 0");

    int value = 100;
    da_add(array, &value);

    int result = da_get(array, 0, NULL);

    ASSERT_TRUE(result == -1, "da_get should return -1 for NULL output pointer");

    da_destroy(array);
    return 1;
}

// Dynamic Array: Verificar que da_remove limpia la referencia residual
int test_da_remove_clears_reference() {
    DynamicArray *array = NULL;

    int create_result = da_create(&array, 5);

    ASSERT_TRUE(create_result == 0, "da_create should return 0");

    int v1 = 10, v2 = 20, v3 = 30;

    da_add(array, &v1);
    da_add(array, &v2);
    da_add(array, &v3);

    int result = da_remove(array, 1);

    ASSERT_TRUE(result == 0, "da_remove should return 0");
    ASSERT_TRUE(array->size == 2, "Size should decrease to 2");
    ASSERT_TRUE(array->data[2] == NULL, "Last position should be NULL after removal");

    da_destroy(array);
    return 1;
}

// Dynamic Array: Verificar que da_get rechaza índices fuera de rango
int test_da_get_out_of_bounds() {
    DynamicArray *array = NULL;

    int create_result = da_create(&array, 5);

    ASSERT_TRUE(create_result == 0, "da_create should return 0");

    int value = 100;
    da_add(array, &value);

    void *out = NULL;
    int result = da_get(array, 1, &out);

    ASSERT_TRUE(result == -1, "da_get should return -1 for out-of-bounds index");

    da_destroy(array);
    return 1;
}

// Dynamic Array: Verificar que da_remove rechaza operaciones sobre un arreglo vacío
int test_da_remove_empty_array() {
    DynamicArray *array = NULL;

    int create_result = da_create(&array, 5);

    ASSERT_TRUE(create_result == 0, "da_create should return 0");
    ASSERT_TRUE(array->size == 0, "Array should be empty");

    int result = da_remove(array, 0);

    ASSERT_TRUE(result == -1, "da_remove should return -1 for an empty array");
    ASSERT_TRUE(array->size == 0, "Array size should remain 0");

    da_destroy(array);
    return 1;
}

// Linked List: Verificar la creación y destrucción de la lista
int test_ll_create_destroy() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should return 0");
    ASSERT_TRUE(list != NULL,
                "List should not be NULL");
    ASSERT_TRUE(list->head == NULL,
                "Initial head should be NULL");
    ASSERT_TRUE(list->size == 0,
                "Initial size should be 0");

    int values[] = {10, 20, 30};

    ASSERT_TRUE(ll_insert_head(list, &values[0]) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &values[1]) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &values[2]) == 0,
                "Third insertion should succeed");

    ASSERT_TRUE(ll_get_size(list) == 3,
                "List should contain three nodes before destruction");

    ASSERT_TRUE(ll_destroy(list) == 0,
                "ll_destroy should return 0");

    return 1;
}

// Linked List: Verificar la destruccion cuando la lista es NULL
int test_ll_destroy_null() {
    ASSERT_TRUE(ll_destroy(NULL) == -1,
                "ll_destroy should return -1 for NULL pointer");

    return 1;
}

// Linked List:: Verificar que ll_create rechaza un puntero de salida NULL
int test_ll_create_null_pointer() {
    int result = ll_create(NULL);

    ASSERT_TRUE(result == -1,
                "ll_create should return -1 for NULL output pointer");

    return 1;
}

// Linked List:: Verificar inserción en cabeza y cola
int test_ll_insertions() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(ll_insert_head(list, &v1) == 0,
                "First head insertion should succeed");

    ASSERT_TRUE(ll_insert_head(list, &v2) == 0,
                "Second head insertion should succeed");

    ASSERT_TRUE(ll_insert_tail(list, &v3) == 0,
                "Tail insertion should succeed");

    ASSERT_TRUE(list->size == 3, "Size should be 3");

    void *out = NULL;

    ASSERT_TRUE(ll_get(list, 0, &out) == 0,
                "Getting index 0 should succeed");
    ASSERT_TRUE(*(int*)out == 20, "Index 0 should be 20");

    ASSERT_TRUE(ll_get(list, 2, &out) == 0,
                "Getting index 2 should succeed");
    ASSERT_TRUE(*(int*)out == 30, "Index 2 should be 30");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_get limpia el puntero de salida ante un índice inválido
int test_ll_get_clears_output_on_error() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int value = 100;

    ASSERT_TRUE(ll_insert_head(list, &value) == 0,
                "Insertion should succeed");

    void *out = &value;

    ASSERT_TRUE(ll_get(list, 1, &out) == -1,
                "ll_get should fail for out-of-bounds index");

    ASSERT_TRUE(out == NULL,
                "Output pointer should be NULL after failure");

    ll_destroy(list);
    return 1;
}

// Linked List:: Verificar la eliminación y el re-linkeo
int test_ll_remove() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(ll_insert_tail(list, &v1) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v2) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v3) == 0,
                "Third insertion should succeed");

    // Eliminar el nodo del medio
    ASSERT_TRUE(ll_remove(list, 1) == 0,
                "Removing middle node should succeed");

    ASSERT_TRUE(list->size == 2, "Size should be 2");

    void *out = NULL;

    ASSERT_TRUE(ll_get(list, 1, &out) == 0,
                "Getting index 1 should succeed");
    ASSERT_TRUE(*(int*)out == 30,
                "Index 1 should now be 30");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_get rechaza índices fuera de rango
int test_ll_get_out_of_bounds() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int value = 100;

    ASSERT_TRUE(ll_insert_head(list, &value) == 0,
                "Insertion should succeed");

    void *out = NULL;

    ASSERT_TRUE(ll_get(list, 1, &out) == -1,
                "ll_get should return -1 for out-of-bounds index");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_get rechaza un puntero de salida NULL
int test_ll_get_null_output() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int value = 100;

    ASSERT_TRUE(ll_insert_head(list, &value) == 0,
                "Insertion should succeed");

    ASSERT_TRUE(ll_get(list, 0, NULL) == -1,
                "ll_get should return -1 for NULL output pointer");

    ll_destroy(list);
    return 1;
}

// Linked List:Verificar que la lista permite almacenar elementos NULL
int test_ll_null_elements() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    ASSERT_TRUE(ll_insert_head(list, NULL) == 0,
                "ll_insert_head should accept NULL");

    ASSERT_TRUE(ll_insert_tail(list, NULL) == 0,
                "ll_insert_tail should accept NULL");

    ASSERT_TRUE(ll_get_size(list) == 2,
                "List size should be 2");

    void *out = (void *)1;

    ASSERT_TRUE(ll_get(list, 0, &out) == 0,
                "ll_get should succeed for NULL element");
    ASSERT_TRUE(out == NULL,
                "Retrieved element should be NULL");

    out = (void *)1;

    ASSERT_TRUE(ll_get(list, 1, &out) == 0,
                "ll_get should succeed for second NULL element");
    ASSERT_TRUE(out == NULL,
                "Retrieved element should be NULL");

    ll_destroy(list);
    return 1;
}

int test_ll_size_consistency() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int values[] = {10, 20, 30};

    ASSERT_TRUE(ll_insert_head(list, &values[0]) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ll_get_size(list) == 1,
                "Size should be 1");

    ASSERT_TRUE(ll_insert_tail(list, &values[1]) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ll_get_size(list) == 2,
                "Size should be 2");

    ASSERT_TRUE(ll_insert_tail(list, &values[2]) == 0,
                "Third insertion should succeed");
    ASSERT_TRUE(ll_get_size(list) == 3,
                "Size should be 3");

    ASSERT_TRUE(ll_remove(list, 1) == 0,
                "Removal should succeed");
    ASSERT_TRUE(ll_get_size(list) == 2,
                "Size should be 2 after removal");

    ASSERT_TRUE(ll_remove(list, 0) == 0,
                "Head removal should succeed");
    ASSERT_TRUE(ll_get_size(list) == 1,
                "Size should be 1 after head removal");

    ASSERT_TRUE(ll_remove(list, 0) == 0,
                "Last removal should succeed");
    ASSERT_TRUE(ll_get_size(list) == 0,
                "Size should be 0 after removing all elements");

    ASSERT_TRUE(list->head == NULL,
                "Head should be NULL when list is empty");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_remove elimina correctamente la cabeza
int test_ll_remove_head() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(ll_insert_tail(list, &v1) == 0, "First insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v2) == 0, "Second insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v3) == 0, "Third insertion should succeed");

    ASSERT_TRUE(ll_remove(list, 0) == 0,
                "Removing head should succeed");

    ASSERT_TRUE(list->size == 2, "Size should be 2");
    ASSERT_TRUE(list->head->data == &v2,
                "New head should contain the second element");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_remove elimina correctamente la cola
int test_ll_remove_tail() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(ll_insert_tail(list, &v1) == 0, "First insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v2) == 0, "Second insertion should succeed");
    ASSERT_TRUE(ll_insert_tail(list, &v3) == 0, "Third insertion should succeed");

    ASSERT_TRUE(ll_remove(list, 2) == 0,
                "Removing tail should succeed");

    ASSERT_TRUE(list->size == 2, "Size should be 2");

    void *out = NULL;

    ASSERT_TRUE(ll_get(list, 1, &out) == 0,
                "Getting last element should succeed");
    ASSERT_TRUE(*(int*)out == 20,
                "New tail should contain the second element");
    ASSERT_TRUE(list->head->next->next == NULL,
                "New tail next pointer should be NULL");

    ll_destroy(list);
    return 1;
}

// Linked List: Verificar que ll_remove rechaza índices fuera de rango
int test_ll_remove_out_of_bounds() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int value = 100;

    ASSERT_TRUE(ll_insert_head(list, &value) == 0,
                "Insertion should succeed");

    ASSERT_TRUE(ll_remove(list, 1) == -1,
                "ll_remove should return -1 for out-of-bounds index");

    ASSERT_TRUE(list->size == 1,
                "List size should remain unchanged");

    ll_destroy(list);
    return 1;
}

// Stack: Verificar el ciclo de vida y las operaciones LIFO
int test_stack_basic_operations() {
    Stack *stack = NULL;
    int v1 = 10, v2 = 20, v3 = 30;

    // Creación
    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");
    ASSERT_TRUE(stack_is_empty(stack) == 1,
                "Stack should be empty initially");

    // Push
    ASSERT_TRUE(stack_push(stack, &v1) == 0,
                "First push should succeed");
    ASSERT_TRUE(stack_push(stack, &v2) == 0,
                "Second push should succeed");
    ASSERT_TRUE(stack_push(stack, &v3) == 0,
                "Third push should succeed");

    ASSERT_TRUE(stack_is_empty(stack) == 0,
                "Stack should not be empty after push");

    // Peek
    void *top = NULL;

    ASSERT_TRUE(stack_peek(stack, &top) == 0,
                "stack_peek should succeed");
    ASSERT_TRUE(top == &v3,
                "Peek should return the last inserted element");

    // Pop
    void *popped = NULL;

    ASSERT_TRUE(stack_pop(stack, &popped) == 0,
                "stack_pop should succeed");
    ASSERT_TRUE(popped == &v3,
                "Pop should return the last inserted element");

    // Verificar nuevo tope
    top = NULL;

    ASSERT_TRUE(stack_peek(stack, &top) == 0,
                "stack_peek should succeed after pop");
    ASSERT_TRUE(top == &v2,
                "Top after pop should be the second element");

    // Completar extracción LIFO
    ASSERT_TRUE(stack_pop(stack, &popped) == 0,
                "Second pop should succeed");
    ASSERT_TRUE(popped == &v2,
                "Second pop should return the second element");

    ASSERT_TRUE(stack_pop(stack, &popped) == 0,
                "Third pop should succeed");
    ASSERT_TRUE(popped == &v1,
                "Third pop should return the first element");

    ASSERT_TRUE(stack_is_empty(stack) == 1,
                "Stack should be empty after all elements are popped");

    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed");

    return 1;
}

// Stack: Verificar stack vacío y condiciones de error
int test_stack_edge_cases() {
    Stack *stack = NULL;

    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");

    // Peek sobre stack vacío
    void *out = (void *)1;

    ASSERT_TRUE(stack_peek(stack, &out) == -1,
                "Peek on empty stack should return -1");
    ASSERT_TRUE(out == NULL,
                "Peek output should be NULL after failure");

    // Pop sobre stack vacío
    out = (void *)1;

    ASSERT_TRUE(stack_pop(stack, &out) == -1,
                "Pop on empty stack should return -1");
    ASSERT_TRUE(out == NULL,
                "Pop output should be NULL after failure");

    ASSERT_TRUE(stack_is_empty(stack) == 1,
                "Stack should remain empty");

    // Destrucción
    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed");

    return 1;
}

// Stack: Verificar el almacenamiento y recuperación de elementos NULL
int test_stack_null_elements() {
    Stack *stack = NULL;

    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");

    ASSERT_TRUE(stack_push(stack, NULL) == 0,
                "stack_push should accept NULL");

    ASSERT_TRUE(stack_is_empty(stack) == 0,
                "Stack should not be empty");

    void *out = (void *)1;

    ASSERT_TRUE(stack_peek(stack, &out) == 0,
                "stack_peek should succeed for NULL element");
    ASSERT_TRUE(out == NULL,
                "Peek should return NULL element");

    out = (void *)1;

    ASSERT_TRUE(stack_pop(stack, &out) == 0,
                "stack_pop should succeed for NULL element");
    ASSERT_TRUE(out == NULL,
                "Pop should return NULL element");

    ASSERT_TRUE(stack_is_empty(stack) == 1,
                "Stack should be empty after pop");

    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed");

    return 1;
}

// Stack: Verificar creación con puntero de salida NULL
int test_stack_create_null_pointer() {
    ASSERT_TRUE(stack_create(NULL) == -1,
                "stack_create should reject NULL output pointer");

    return 1;
}

// Stack: Verificar el rechazo de un Stack NULL
int test_stack_push_null_stack() {
    int value = 10;

    ASSERT_TRUE(stack_push(NULL, &value) == -1,
                "stack_push should reject NULL stack");

    return 1;
}

// Stack: Verificar el rechazo de un Stack NULL en pop
int test_stack_pop_null_stack() {
    void *out = (void *)1;

    ASSERT_TRUE(stack_pop(NULL, &out) == -1,
                "stack_pop should reject NULL stack");
    ASSERT_TRUE(out == NULL,
                "Pop output should be NULL after failure");

    return 1;
}

// Stack: Verificar el rechazo de un Stack NULL en peek
int test_stack_peek_null_stack() {
    void *out = (void *)1;

    ASSERT_TRUE(stack_peek(NULL, &out) == -1,
                "stack_peek should reject NULL stack");
    ASSERT_TRUE(out == NULL,
                "Peek output should be NULL after failure");

    return 1;
}

// Stack: Verificar el rechazo de un puntero de salida NULL en peek
int test_stack_peek_null_output() {
    Stack *stack = NULL;

    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");
    ASSERT_TRUE(stack_peek(stack, NULL) == -1,
                "stack_peek should reject NULL output pointer");
    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed");

    return 1;
}

// Stack: Verificar el rechazo de un puntero de salida NULL en pop
int test_stack_pop_null_output() {
    Stack *stack = NULL;

    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");
    ASSERT_TRUE(stack_pop(stack, NULL) == -1,
                "stack_pop should reject NULL output pointer");
    ASSERT_TRUE(stack_is_empty(stack) == 1,
                "Stack should remain empty after failed pop");
    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed");

    return 1;
}

// Stack: Verificar el rechazo de un Stack NULL en destroy
int test_stack_destroy_null() {
    ASSERT_TRUE(stack_destroy(NULL) == -1,
                "stack_destroy should reject NULL stack");

    return 1;
}

// Stack: Verify destruction with stored elements
int test_stack_destroy_with_elements() {
    Stack *stack = NULL;
    int v1 = 10, v2 = 20, v3 = 30;

    ASSERT_TRUE(stack_create(&stack) == 0,
                "stack_create should succeed");

    ASSERT_TRUE(stack_push(stack, &v1) == 0,
                "First push should succeed");
    ASSERT_TRUE(stack_push(stack, &v2) == 0,
                "Second push should succeed");
    ASSERT_TRUE(stack_push(stack, &v3) == 0,
                "Third push should succeed");

    ASSERT_TRUE(stack_destroy(stack) == 0,
                "stack_destroy should succeed with stored elements");

    ASSERT_TRUE(v1 == 10 && v2 == 20 && v3 == 30,
                "Stored objects should remain unchanged after destruction");

    return 1;
}

// Stack: Verificar el rechazo de un Stack NULL en is_empty
int test_stack_is_empty_null() {
    ASSERT_TRUE(stack_is_empty(NULL) == -1,
                "stack_is_empty should reject NULL stack");

    return 1;
}

// Hash Table: Verificar inserción y recuperación básica
int test_ht_basic_operations() {
    HashTable *table = NULL;
    ASSERT_TRUE(ht_create(&table, 10) == 0,
            "ht_create should succeed");

    char *key = "Pablo";
    char *val = "Developer";

    ASSERT_TRUE(ht_insert(table, key, val) == 0,
            "ht_insert should succeed");

    void *out = NULL;
    int result = ht_get(table, key, &out);

    // COMPARACIÓN CORRECTA: Comparar el puntero recuperado con el puntero original
    ASSERT_TRUE(result == 0, "ht_get should return 0");
    ASSERT_TRUE(out == val, "The pointer retrieved should be the same as the pointer inserted");

    ASSERT_TRUE(ht_destroy(table) == 0, "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verificar el manejo de colisiones (Chaining)
int test_ht_collisions() {
    HashTable *table = NULL;
    ASSERT_TRUE(ht_create(&table, 1) == 0,
            "ht_create should succeed"); // Capacidad 1 para forzar colisiones

    char *k1 = "Key1";
    char *v1 = "Val1";
    char *k2 = "Key2";
    char *v2 = "Val2";

    ASSERT_TRUE(ht_insert(table, k1, v1) == 0,
            "ht_insert should succeed for Key1");
    ASSERT_TRUE(ht_insert(table, k2, v2) == 0,
            "ht_insert should succeed for Key2");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 2, "Bucket 0 should have 2 elements");

    void *out = NULL;
    ASSERT_TRUE(ht_get(table, k1, &out) == 0,
            "ht_get should succeed for Key1");
    ASSERT_TRUE(out == v1, "Should retrieve Val1 for Key1");

    ASSERT_TRUE(ht_get(table, k2, &out) == 0,
            "ht_get should succeed for Key2");
    ASSERT_TRUE(out == v2, "Should retrieve Val2 for Key2");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verificar la eliminación y limpieza
int test_ht_remove() {
    HashTable *table = NULL;
    ASSERT_TRUE(ht_create(&table, 10) == 0,
            "ht_create should succeed");

    char *k = "TestKey";
    char *v = "TestVal";
    ASSERT_TRUE(ht_insert(table, k, v) == 0,
            "ht_insert should succeed");

    void *removed_value = NULL;
    ASSERT_TRUE(ht_remove(table, k, &removed_value) == 0, "ht_remove should return 0");
    ASSERT_TRUE(removed_value == v, "ht_remove should return the removed value");

    void *out = NULL;
    ASSERT_TRUE(ht_get(table, k, &out) == -1, "Key should no longer exist");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Dynamic Array: Edge Cases
int test_da_edge_cases() {
    DynamicArray *array = NULL;

    ASSERT_TRUE(da_create(NULL, 5) == -1,
                "da_create should fail when output pointer is NULL");

    ASSERT_TRUE(da_create(&array, 0) == -1,
                "da_create should fail when initial capacity is zero");

    da_create(&array, 5);

    void *out = NULL;
    // Acceso fuera de rango
    ASSERT_TRUE(da_get(array, 10, &out) == -1, "da_get should fail for out-of-bounds");
    ASSERT_TRUE(da_remove(array, 0) == -1, "da_remove should fail for empty array");

    da_destroy(array);
    return 1;
}

// Linked List: Edge Cases
int test_ll_edge_cases() {
    LinkedList *list = NULL;

    ASSERT_TRUE(ll_create(&list) == 0,
                "ll_create should succeed");

    int val = 10;

    // Insertar al inicio de una lista vacía
    ASSERT_TRUE(ll_insert_head(list, &val) == 0,
                "ll_insert_head should work on empty list");

    ASSERT_TRUE(list->head != NULL,
                "Head should not be NULL after insertion");
    ASSERT_TRUE(list->size == 1,
                "Size should be 1");

    // Eliminar el único elemento
    ASSERT_TRUE(ll_remove(list, 0) == 0,
                "ll_remove should work for single element");

    ASSERT_TRUE(list->head == NULL,
                "Head should be NULL after removing only element");
    ASSERT_TRUE(list->size == 0,
                "Size should be 0");

    // Insertar al final de una lista vacía
    ASSERT_TRUE(ll_insert_tail(list, &val) == 0,
                "ll_insert_tail should work on empty list");

    ASSERT_TRUE(list->head != NULL,
                "Head should not be NULL after tail insertion");
    ASSERT_TRUE(list->head->data == &val,
                "Inserted element should be stored correctly");
    ASSERT_TRUE(list->size == 1,
                "Size should be 1");

    // Eliminar el único elemento
    ASSERT_TRUE(ll_remove(list, 0) == 0,
                "ll_remove should work after tail insertion");

    ASSERT_TRUE(list->head == NULL,
                "Head should be NULL after removing only element");
    ASSERT_TRUE(list->size == 0,
                "Size should be 0");

    // Intentar borrar en lista vacía
    ASSERT_TRUE(ll_remove(list, 0) == -1,
                "ll_remove should fail for empty list");

    ll_destroy(list);
    return 1;
}

// Hash Table: Edge Cases
int test_ht_edge_cases() {
    HashTable *table = NULL;
    ASSERT_TRUE(ht_create(&table, 5) == 0,
                "ht_create should succeed");
    void *out = NULL;
    // Buscar en tabla vacía
    ASSERT_TRUE(ht_get(table, "NonExistent", &out) == -1, "ht_get should fail for empty table");

    char *k = "Key";
    char *v = "Val";
    ASSERT_TRUE(ht_insert(table, k, v) == 0,
                "ht_insert should succeed");
    // Eliminar clave que no existe
    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, "WrongKey", &removed_value) == -1,
                "ht_remove should fail for non-existent key");

    ASSERT_TRUE(removed_value == NULL,
                "Output value should remain NULL when key is not found");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify duplicate key updates
int test_ht_duplicate_keys() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    char *key = "Language";
    char *value1 = "Java";
    char *value2 = "Kotlin";

    ASSERT_TRUE(ht_insert(table, key, value1) == 0,
                "First insertion should succeed");

    ASSERT_TRUE(ht_insert(table, key, value2) == 0,
                "Duplicate key insertion should update the value");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 1,
            "Duplicate key should not create a new entry");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, key, &out) == 0,
                "ht_get should find the updated key");

    ASSERT_TRUE(out == value2,
                "ht_get should return the updated value");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify NULL value handling
int test_ht_null_values() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    const char *key = "NullValue";

    ASSERT_TRUE(ht_insert(table, key, NULL) == 0,
                "ht_insert should accept NULL values");

    void *out = (void *) 1;

    ASSERT_TRUE(ht_get(table, key, &out) == 0,
                "ht_get should find a key with NULL value");

    ASSERT_TRUE(out == NULL,
                "Retrieved value should be NULL");

    void *removed_value = (void *) 1;

    ASSERT_TRUE(ht_remove(table, key, &removed_value) == 0,
                "ht_remove should remove a key with NULL value");

    ASSERT_TRUE(removed_value == NULL,
                "Removed value should be NULL");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify empty string key handling
int test_ht_empty_keys() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    const char *key = "";
    char *value = "EmptyKeyValue";

    ASSERT_TRUE(ht_insert(table, key, value) == 0,
                "ht_insert should accept empty string keys");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, key, &out) == 0,
                "ht_get should find an empty string key");

    ASSERT_TRUE(out == value,
                "Retrieved value should match inserted value");

    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, key, &removed_value) == 0,
                "ht_remove should remove an empty string key");

    ASSERT_TRUE(removed_value == value,
                "Removed value should match inserted value");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify case-sensitive key comparison
int test_ht_case_sensitive_keys() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    char *value1 = "Java";
    char *value2 = "java";

    ASSERT_TRUE(ht_insert(table, "Java", value1) == 0,
                "First key insertion should succeed");

    ASSERT_TRUE(ht_insert(table, "java", value2) == 0,
                "Second key insertion should succeed");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, "Java", &out) == 0 && out == value1,
                "Java should retrieve its own value");

    ASSERT_TRUE(ht_get(table, "java", &out) == 0 && out == value2,
                "java should retrieve its own value");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify that keys are copied on insertion
int test_ht_key_copy() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    char key[] = "Original";
    char *value = "StoredValue";

    ASSERT_TRUE(ht_insert(table, key, value) == 0,
                "ht_insert should succeed");

    key[0] = 'X';

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, "Original", &out) == 0,
                "Original key should still be retrievable");

    ASSERT_TRUE(out == value,
                "Retrieved value should match inserted value");

    ASSERT_TRUE(ht_get(table, key, &out) == -1,
                "Modified key should not be found");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify bucket cleanup after removing the last entry
int test_ht_bucket_cleanup() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    ASSERT_TRUE(ht_insert(table, "Key", "Value") == 0,
                "ht_insert should succeed");

    ASSERT_TRUE(table->buckets[0] != NULL,
                "Bucket should contain a list after insertion");

    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, "Key", &removed_value) == 0,
                "ht_remove should succeed");

    ASSERT_TRUE(removed_value != NULL,
                "Removed value should not be NULL");

    ASSERT_TRUE(table->buckets[0] == NULL,
                "Bucket should be NULL after removing its last entry");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify ht_create invalid arguments
int test_ht_create_invalid_arguments() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(NULL, 10) == -1,
                "ht_create should fail when table is NULL");

    ASSERT_TRUE(ht_create(&table, 0) == -1,
                "ht_create should fail when capacity is zero");

    ASSERT_TRUE(table == NULL,
                "Table should remain NULL after failed creation");

    return 1;
}

// Hash Table: Verify ht_insert invalid arguments
int test_ht_insert_invalid_arguments() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    ASSERT_TRUE(ht_insert(NULL, "Key", "Value") == -1,
                "ht_insert should fail when table is NULL");

    ASSERT_TRUE(ht_insert(table, NULL, "Value") == -1,
                "ht_insert should fail when key is NULL");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify ht_get invalid arguments
int test_ht_get_invalid_arguments() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    int sentinel = 0;
    void *out = &sentinel;

    ASSERT_TRUE(ht_get(NULL, "Key", &out) == -1,
                "ht_get should fail when table is NULL");

    ASSERT_TRUE(out == NULL,
                "Output value should be reset when table is NULL");

    out = &sentinel;

    ASSERT_TRUE(ht_get(table, NULL, &out) == -1,
                "ht_get should fail when key is NULL");

    ASSERT_TRUE(out == NULL,
                "Output value should be reset when key is NULL");

    ASSERT_TRUE(ht_get(table, "Key", NULL) == -1,
                "ht_get should fail when out_value is NULL");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");

    return 1;
}

// Hash Table: Verify ht_remove invalid arguments
int test_ht_remove_invalid_arguments() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "ht_create should succeed");

    int sentinel = 0;
    void *out = &sentinel;

    ASSERT_TRUE(ht_remove(NULL, "Key", &out) == -1,
                "ht_remove should fail when table is NULL");

    ASSERT_TRUE(out == NULL,
                "Output value should be reset when table is NULL");

    out = &sentinel;

    ASSERT_TRUE(ht_remove(table, NULL, &out) == -1,
                "ht_remove should fail when key is NULL");

    ASSERT_TRUE(out == NULL,
                "Output value should be reset when key is NULL");

    ASSERT_TRUE(ht_remove(table, "Key", NULL) == -1,
                "ht_remove should fail when out_value is NULL");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");

    return 1;
}

// Hash Table: Verify removal preserves other colliding entries
int test_ht_remove_with_collisions() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    char *value1 = "Value1";
    char *value2 = "Value2";
    char *value3 = "Value3";

    ASSERT_TRUE(ht_insert(table, "Key1", value1) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key2", value2) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key3", value3) == 0,
                "Third insertion should succeed");

    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, "Key2", &removed_value) == 0,
                "Removing the middle entry should succeed");
    ASSERT_TRUE(removed_value == value2,
                "Removed value should match Key2 value");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, "Key1", &out) == 0 && out == value1,
                "Key1 should remain accessible");
    ASSERT_TRUE(ht_get(table, "Key3", &out) == 0 && out == value3,
                "Key3 should remain accessible");
    ASSERT_TRUE(ht_get(table, "Key2", &out) == -1,
                "Key2 should no longer exist");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 2,
                "Bucket should contain two remaining entries");

    ASSERT_TRUE(ht_destroy(table) == 0,
            "ht_destroy should succeed");
    return 1;
}

// Hash Table: Verify updating a key with a previous NULL value
int test_ht_update_null_value() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    char *key = "Language";
    char *value = "Kotlin";

    ASSERT_TRUE(ht_insert(table, key, NULL) == 0,
                "Insertion with NULL value should succeed");

    ASSERT_TRUE(ht_insert(table, key, value) == 0,
                "Updating a NULL value should succeed");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 1,
            "Updating a key should not create a duplicate entry");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, key, &out) == 0,
                "ht_get should find the key");

    ASSERT_TRUE(out == value,
                "ht_get should return the updated value");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");

    return 1;
}

// Hash Table: Verify removing the head entry from a collision bucket
int test_ht_remove_collision_head() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    char *value1 = "Value1";
    char *value2 = "Value2";
    char *value3 = "Value3";

    ASSERT_TRUE(ht_insert(table, "Key1", value1) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key2", value2) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key3", value3) == 0,
                "Third insertion should succeed");

    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, "Key3", &removed_value) == 0,
                "Removing the head entry should succeed");

    ASSERT_TRUE(removed_value == value3,
                "Removed value should match Key3 value");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 2,
                "Bucket should contain two remaining entries");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, "Key1", &out) == 0 && out == value1,
                "Key1 should remain accessible");
    ASSERT_TRUE(ht_get(table, "Key2", &out) == 0 && out == value2,
                "Key2 should remain accessible");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");

    return 1;
}

// Hash Table: Verify removing the tail entry from a collision bucket
int test_ht_remove_collision_tail() {
    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 1) == 0,
                "ht_create should succeed");

    char *value1 = "Value1";
    char *value2 = "Value2";
    char *value3 = "Value3";

    ASSERT_TRUE(ht_insert(table, "Key1", value1) == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key2", value2) == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key3", value3) == 0,
                "Third insertion should succeed");

    void *removed_value = NULL;

    ASSERT_TRUE(ht_remove(table, "Key1", &removed_value) == 0,
                "Removing the tail entry should succeed");

    ASSERT_TRUE(removed_value == value1,
                "Removed value should match Key1 value");

    ASSERT_TRUE(ll_get_size(table->buckets[0]) == 2,
                "Bucket should contain two remaining entries");

    void *out = NULL;

    ASSERT_TRUE(ht_get(table, "Key2", &out) == 0 && out == value2,
                "Key2 should remain accessible");
    ASSERT_TRUE(ht_get(table, "Key3", &out) == 0 && out == value3,
                "Key3 should remain accessible");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "ht_destroy should succeed");

    return 1;
}

// Hash Table: Verify destruction of empty and populated tables
int test_ht_destroy() {
    HashTable *empty_table = NULL;

    ASSERT_TRUE(ht_create(&empty_table, 10) == 0,
                "Empty table creation should succeed");

    ASSERT_TRUE(ht_destroy(empty_table) == 0,
                "Destroying an empty table should succeed");

    HashTable *table = NULL;

    ASSERT_TRUE(ht_create(&table, 10) == 0,
                "Populated table creation should succeed");

    ASSERT_TRUE(ht_insert(table, "Key1", "Value1") == 0,
                "First insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key2", "Value2") == 0,
                "Second insertion should succeed");
    ASSERT_TRUE(ht_insert(table, "Key3", "Value3") == 0,
                "Third insertion should succeed");

    ASSERT_TRUE(ht_destroy(table) == 0,
                "Destroying a populated table should succeed");

    return 1;
}