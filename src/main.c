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

    // 4. Limpieza de memoria
    da_destroy(my_array);
    printf("\nMemory freed. Program finished successfully.\n");

    return 0;
}