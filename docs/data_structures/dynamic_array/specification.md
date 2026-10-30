# Specification: Generic Dynamic Array

## 1. Objective
Implement a generic, dynamically resizable array (Dynamic Array) in C. The implementation must be type-agnostic, allowing the storage of any data type while ensuring strict memory safety and efficiency.

## 2. Functional Requirements

### 2.1 Core Operations

The Dynamic Array must provide the following functionality:

- **Initialization (`create`)**: Create a new array with a specified, non-zero initial capacity. Return `0` on success or `-1` on failure.
- **Insertion (`add`)**: Append an element pointer to the end of the array. If the current capacity is reached, the array must automatically resize by doubling its capacity. Return `0` on success or `-1` on failure.
- **Access (`get`)**: Retrieve the pointer stored at a specific index through a valid output parameter (`void **out_element`). Return `0` on success or `-1` if the array or output parameter is `NULL`, or if the index is out of range.
- **Removal (`remove`)**: Remove the element pointer at a given index and shift subsequent elements one position to the left. The function does not free the object pointed to by the removed element. Return `0` on success or `-1` if the array is `NULL` or the index is out of range.
- **Memory Cleanup (`destroy`)**: Free the array's internal buffer and the `DynamicArray` structure. The function does not free the objects pointed to by stored elements. Return `0` on success or `-1` if the array is `NULL`.

### 2.2 Genericity
To support any data type, the implementation must use `void*` pointers. The array should store pointers to the data rather than the data itself.

## 3. Technical Constraints & Error Handling

### 3.1 Memory Safety
- **No Memory Leaks**: All memory allocated via `malloc` or `realloc` must be explicitly freed.
- **Allocation Failure**: The system must gracefully handle cases where memory allocation fails (e.g., `malloc` returns `NULL`), preventing segmentation faults.

### 3.2 Boundary Validation
- **Out-of-Bounds Access**: Any attempt to access or remove an element outside the current range `[0, size - 1]` must be detected and handled (e.g., returning `NULL` or an error code).

## 4. Complexity Analysis (Big O)

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| Access by Index | $O(1)$ | $O(1)$ |
| Append (Average) | $O(1)$ | $O(1)$ |
| Append (Worst case) | $O(n)$ | $O(n)$ |
| Removal | $O(n)$ | $O(1)$ |

## 5. Edge Case Behavior
- **Empty Array**: `da_get` and `da_remove` must return `-1` when called on an empty array, because no valid element index exists.
- **Out of Bounds**: `da_get` and `da_remove` must return `-1` when `index >= size`.
- **Invalid Pointers**: `da_add`, `da_get`, and `da_remove` must return `-1` if the array pointer is `NULL`. Additionally, `da_get` must return `-1` if `out_element` is `NULL`. `da_destroy` must return `-1` if the array pointer is `NULL`.
- **Allocation Failure**: If memory allocation fails during `da_create`, the function must return `-1`. If `realloc` fails during `da_add`, the function must return `-1` without losing the original allocated buffer or its existing elements.
- **Invalid Initial Capacity**: `da_create` must return `-1` if the output pointer is `NULL` or if `initial_capacity` is zero.