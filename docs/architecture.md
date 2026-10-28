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

The library exposes the following functions. Functions that return int use 0 for success and -1 for failure. The utility functions da_get_size and da_get_capacity return 0 when passed a NULL pointer.

### 2.1 Lifecycle Management
- `int da_create(DynamicArray **array, size_t initial_capacity)`
    - Allocates the struct and the initial buffer.
- `int da_destroy(DynamicArray *array)`
    - Frees the buffer and the struct.

### 2.2 Element Manipulation
- `int da_add(DynamicArray *array, void *element)`
    - Adds an element. Triggers a resize if `size == capacity`.
- `int da_get(DynamicArray *array, size_t index, void **out_element)`
    - Retrieves the pointer at the given index.
- `int da_remove(DynamicArray *array, size_t index)`
  - Removes the element at the specified index and shifts subsequent elements one position to the left. The function does not free the object pointed to by the removed element.

### 2.3 Utility
- `size_t da_get_size(DynamicArray *array)`
- `size_t da_get_capacity(DynamicArray *array)`

## 3. Growth Strategy
When `size` reaches `capacity`, the array will grow using the following logic:
1. Calculate `new_capacity = capacity * 2`.
2. Allocate a new buffer using `realloc`.
3. If `realloc` fails, return an error code without losing the original data.
