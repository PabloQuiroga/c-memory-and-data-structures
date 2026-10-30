# Architecture: Generic Dynamic Array

## 1. Data Structure Design
The Dynamic Array is implemented using a `struct that manages a contiguous block of memory.

### Struct Definition
```c
typedef struct {
    void **data;       // Pointer to an array of void pointers (the elements)
    size_t size;      // Current number of elements stored
    size_t capacity;    // Total allocated capacity
} DynamicArray;
```
### Design Justification
- `void **data`: Allows the array to store pointers to objects of different data types. The array manages the storage of these pointers, but it does not allocate, copy, or free the objects they point to.
- `size_t`: Used instead of `int` to ensure compatibility with large memory addresses and to avoid negative values.

## 2. API Definition (Interface)

The library exposes the following functions. Functions that return `int` use `0` for success and `-1` for failure. The utility functions `da_get_size` and `da_get_capacity` return `0` when passed a `NULL` pointer.

### 2.1 Lifecycle Management

- `int da_create(DynamicArray **array, size_t initial_capacity)`
  - Creates a new dynamic array by allocating the structure and its internal buffer.
  - Returns `-1` if `array` is `NULL`, `initial_capacity` is zero, or a memory allocation fails.
- `int da_destroy(DynamicArray *array)`
  - Frees the internal buffer and the DynamicArray structure.
  - Does not free the objects pointed to by the stored elements.
  - Returns -1 if array is NULL.
  - The function receives the array pointer by value. Therefore, it cannot set the caller's pointer to NULL after releasing the memory.
  - After a successful call, the caller must not access or reuse the original pointer, as it becomes a dangling pointer.
  - The caller is responsible for managing the lifetime of the pointer and avoiding subsequent use after destruction.

### 2.2 Element Manipulation

- `int da_add(DynamicArray *array, void *element)`
  - Appends an element pointer to the end of the array.
  - Doubles the capacity when `size == capacity`.
  - Returns `-1` if `array` is `NULL` or if growing the buffer fails. If `realloc` fails, the original buffer and its existing elements remain intact.
- `int da_get(DynamicArray *array, size_t index, void **out_element)`
  - Retrieves the pointer stored at the specified index through `out_element`.
  - Returns `-1` if `array` or `out_element` is `NULL`, or if `index >= size`.
- `int da_remove(DynamicArray *array, size_t index)`
  - Removes the element pointer at the specified index and shifts subsequent elements one position to the left.
  - Does not free the object pointed to by the removed element.
  - Returns `-1` if `array` is `NULL` or if `index >= size`.

### 2.3 Utility

- `size_t da_get_size(DynamicArray *array)`
  - Returns the current number of elements, or `0` if `array` is `NULL`.
- `size_t da_get_capacity(DynamicArray *array)`
  - Returns the current allocated capacity, or `0` if `array` is `NULL`.

## 3. Growth Strategy
When `size` reaches `capacity`, the array will grow using the following logic:
1. Calculate `new_capacity = capacity * 2`.
2. Allocate a new buffer using `realloc`.
3. If `realloc` fails, return an error code without losing the original data.

### 3.1 Growth Limitations and Risks

The current growth strategy has two potential integer overflow risks:
- **Capacity Doubling**: Calculating `new_capacity = capacity * 2` may overflow `size_t` if the current capacity is too large. This can produce an incorrect capacity value.
- **Allocation Size Calculation**: Calculating `new_capacity * sizeof(void *)` may also overflow `size_t`, causing the requested allocation size to be smaller than intended.

These risks must be addressed in the implementation before the Dynamic Array can be considered robust against extreme capacity values.

The implementation should validate both calculations before calling `realloc`. If either calculation would overflow, `da_add` must return `-1` without modifying the existing array or losing its allocated buffer and stored elements.

The exact validation strategy will be determined during the implementation review.