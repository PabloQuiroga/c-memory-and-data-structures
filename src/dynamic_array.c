//
// Created by Pablo Quiroga on 04/10/2026.
//

#include "dynamic_array.h"
#include <stdlib.h> // Para malloc, realloc y free

int da_create(DynamicArray **array, size_t initial_capacity) {
    // 1. Reservar memoria para la estructura DynamicArray
    *array = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (*array == NULL) {
        return -1; // Error: No hay memoria para la estructura
    }

    // 2. Reservar memoria para el buffer de punteros (los datos)
    (*array)->data = (void **)malloc(initial_capacity * sizeof(void *));
    if ((*array)->data == NULL) {
        free(*array); // Liberamos la estructura para no dejar basura
        return -1; // Error: No hay memoria para el buffer
    }

    // 3. Inicializar valores
    (*array)->size = 0;
    (*array)->capacity = initial_capacity;

    return 0; // Éxito
}

int da_destroy(DynamicArray *array) {
    if (array == NULL) return -1;

    // Liberamos primero el buffer interno y luego la estructura
    free(array->data);
    free(array);
    return 0;
}