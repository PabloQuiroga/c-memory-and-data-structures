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

int da_add(DynamicArray *array, void *element) {
    if (array == NULL) return -1;

    // 1. Verificar si el arreglo está lleno
    if (array->size == array->capacity) {
        // Calculamos la nueva capacidad (el doble)
        size_t new_capacity = array->capacity * 2;

        // Intentamos redimensionar el buffer de punteros
        void **new_data = (void **)realloc(array->data, new_capacity * sizeof(void *));

        if (new_data == NULL) {
            return -1; // Error: No hay memoria suficiente para crecer
        }

        // Actualizamos el puntero y la capacidad
        array->data = new_data;
        array->capacity = new_capacity;
    }

    // 2. Agregar el elemento al final y aumentar el tamaño
    array->data[array->size] = element;
    array->size++;

    return 0; // Éxito
}

size_t da_get_size(DynamicArray *array) {
    return array ? array->size : 0;
}
size_t da_get_capacity(DynamicArray *array) {
    return array ? array->capacity : 0;
}

int da_get(DynamicArray *array, size_t index, void **out_element) {
    if (array == NULL || out_element == NULL) return -1;

    // 1. Validación de límites (Boundary Check)
    // Si el índice es mayor o igual al tamaño actual, es un error
    if (index >= array->size) {
        return -1; // Error: Índice fuera de rango
    }

    // 2. Asignar la dirección del elemento al puntero de salida
    *out_element = array->data[index];

    return 0; // Éxito
}

int da_destroy(DynamicArray *array) {
    if (array == NULL) return -1;

    // Liberamos primero el buffer interno y luego la estructura
    free(array->data);
    free(array);
    return 0;
}