# Specification: Generic Singly Linked List

## 1. Objective
Implement a generic Singly Linked List in C. The implementation must demonstrate proficiency in dynamic memory allocation, pointer manipulation (nodes), and an understanding of the trade-offs between linked structures and contiguous arrays.

## 2. Functional Requirements

### 2.1 Core Operations

The Linked List must provide the following functionality:

- **Initialization (`ll_create`)**: Create an empty list structure, initializing `head` to `NULL` and `size` to `0`. Returns `0` on success or `-1` if the output pointer is `NULL` or memory allocation fails. The output pointer is initialized to `NULL` before allocation.
- **Insertion at Head (`ll_insert_head`)**: Prepend an element to the list. Returns `0` on success or `-1` if the list pointer is `NULL` or memory allocation fails. This is an \(O(1)\) operation.
- **Insertion at Tail (`ll_insert_tail`)**: Append an element to the end of the list. Returns `0` on success or `-1` if the list pointer is `NULL` or memory allocation fails. This is an \(O(n)\) operation.
- **Access (`ll_get`)**: Retrieve the pointer stored at a specific index through `void **out_element`. Returns `0` on success or `-1` if the list or output pointer is `NULL`, or the index is invalid. When the output pointer is valid, it is initialized to `NULL` before attempting access.
- **Removal (`ll_remove`)**: Remove the node at a specific index, correctly updating links and decrementing the list size. Returns `0` on success or `-1` if the list is `NULL`, empty, or the index is invalid.
- **Size (`ll_get_size`)**: Return the current number of elements. Returns `0` if the list pointer is `NULL`.
- **Memory Cleanup (`ll_destroy`)**: Free every node and the list container. Returns `0` on success or `-1` if the list pointer is `NULL`.

### 2.2 Genericity
Consistent with the portfolio's architecture, the list must use `void*` pointers to store data, allowing it to be type-agnostic.

### 2.3 NULL Elements

- The list allows `NULL` values as valid elements.
- Both `ll_insert_head` and `ll_insert_tail` must accept a `NULL` element pointer.
- When `ll_get` retrieves a node containing `NULL`, it must return `0` and set `*out_element` to `NULL`.
- A successful lookup is determined by the return code, not by the value of the retrieved pointer.

## 3. Technical Constraints & Error Handling

### 3.1 Pointer Integrity
- **Null Pointer Protection**: All functions must validate that the list pointer is not NULL before performing operations.
- **Empty List Handling**: Operations like `ll_get` or `ll_remove` on an empty list must be handled gracefully without crashing.

### 3.2 Memory Safety

- **Node Ownership**: The list owns the memory allocated for its internal nodes. Each node must be freed when removed or when the list is destroyed.
- **Element Ownership**: The list does not own the objects referenced by its `void *data` pointers. Removing a node or destroying the list must not free the referenced objects. Their lifetime remains the caller's responsibility.
- **No Memory Leaks**: Every node successfully allocated through `malloc` must eventually be freed by `ll_remove` or `ll_destroy`.
- **Allocation Failure**: If memory allocation for a new node or the list structure fails, the corresponding operation must return `-1` without leaving partially initialized structures or modifying the existing list.
- **Pointer Safety**: Functions must validate required pointers before dereferencing them. Since `ll_destroy` receives the list pointer by value, it does not set the caller's pointer to `NULL`. The caller must discard the pointer after a successful destruction and must not access or reuse it.

## 4. Complexity Analysis (Big O)

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| Insert at Head | $O(1)$ | $O(1)$ |
| Insert at Tail | $O(n)$ | $O(1)$ |
| Access by Index | $O(n)$ | $O(1)$ |
| Removal | $O(n)$ | $O(1)$ |

## 5. Edge Case Behavior
- **Empty List**: `ll_get` and `ll_remove` must return `-1` if the head is `NULL`.
- **Single Element**: Removing the only element must result in `head = NULL` and `size = 0`.
- **Tail Removal**: Removing the last element must correctly update the second-to-last node's `next` pointer to `NULL`.