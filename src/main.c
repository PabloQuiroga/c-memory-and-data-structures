//
// Created by Pablo Quiroga on 04/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

int main() {
    DynamicArray *my_array = NULL;

    // 1. Creamos el arreglo con una capacidad pequeña (2) para forzar el crecimiento rápido
    printf("--- Initializing array with capacity 2 ---\n");
    if (da_create(&my_array, 2) != 0) {
        printf("Error creating array\n");
        return 1;
    }

    // 2. Agregamos algunos números (usando punteros a enteros)
    int val1 = 10, val2 = 20, val3 = 30, val4 = 40;
    void *elements[] = { &val1, &val2, &val3, &val4 };

    for (int i = 0; i < 4; i++) {
        printf("Adding element %d... ", i + 1);
        if (da_add(my_array, elements[i]) == 0) {
            printf("Success! (Size: %zu, Capacity: %zu)\n",
                   da_get_size(my_array), da_get_capacity(my_array));
        } else {
            printf("Failed!\n");
        }
    }

    // 3. Verificación final
    printf("\nFinal Results:\n");
    printf("Total elements: %zu\n", da_get_size(my_array));
    printf("Final capacity: %zu\n", da_get_capacity(my_array));//Llamamos a la función de capacidad

    printf("\n--- Verifying elements ---\n");
    void *element_ptr = NULL;
    for (int i = 0; i < 4; i++) {
        if (da_get(my_array, i, &element_ptr) == 0) {
            // Como sabemos que guardamos enteros, hacemos un cast a (int*)
            printf("Element at index %d: %d\n", i, *(int *)element_ptr);
        } else {
            printf("Error getting element at index %d\n", i);
        }
    }

    // Intentar obtener un elemento fuera de rango para probar el error
    if (da_get(my_array, 100, &element_ptr) != 0) { //Llamamos con indice 100
        printf("Correctly handled out-of-bounds access at index 100\n");
    }

    printf("\n--- Testing Removal ---\n");
    printf("Removing element at index 1 (value 20)...\n");
    if (da_remove(my_array, 1) == 0) {
        printf("Success! New size: %zu\n", da_get_size(my_array));//Llamamos a la función de tamaño
    }

    printf("Verifying elements after removal:\n");
    for (int i = 0; i < da_get_size(my_array); i++) {
        if (da_get(my_array, i, &element_ptr) == 0) {
            printf("Index %d: %d\n", i, *(int *)element_ptr);
        }
    }// Deberías ver: Index 0: 10, Index 1: 30, Index 2: 40 (el 20 desapareció)

    // 4. Limpieza de memoria
    da_destroy(my_array);
    printf("\nMemory freed. Program finished successfully.\n");

    return 0;
}