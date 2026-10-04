//
// Created by Pablo Quiroga on 04/10/2026.
//

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h> // Para size_t

// Estructura del Arreglo Dinámico
typedef struct {
    void **data;       // Puntero al arreglo de punteros (elementos)
    size_t size;      // Cantidad actual de elementos
    size_t capacity;    // Capacidad total asignada
} DynamicArray;

// API de la Librería
// Retornan 0 para éxito y -1 para error

int da_create(DynamicArray **array, size_t initial_capacity);
int da_destroy(DynamicArray *array);
int da_add(DynamicArray *array, void *element);
int da_get(DynamicArray *array, size_t index, void **out_element);
int da_remove(DynamicArray *array, size_t index);

size_t da_get_size(DynamicArray *array);
size_t da_get_capacity(DynamicArray *array);

#endif