# Specification: Generic Stack (LIFO)

## 1. Objective
Implement a generic Stack (Last-In, First-Out) by leveraging the existing Linked List implementation. The goal is to demonstrate code reuse and the Adapter design pattern.

## 2. Functional Requirements

### 2.1 Core Operations

- **Initialization (`stack_create`)**: Create an empty stack. Returns `0` on success or `-1` if the output pointer is `NULL` or memory allocation fails. The output pointer must be initialized to `NULL` before allocation.
- **Push (`stack_push`)**: Add an element to the top of the stack. Accepts `NULL` elements. Returns `0` on success or `-1` if the stack pointer is `NULL` or memory allocation fails. Time complexity: O(1).
- **Pop (`stack_pop`)**: Remove and return the top element. Returns `0` on success or `-1` if the stack pointer is `NULL`, the output pointer is `NULL`, or the stack is empty. The output pointer must be initialized to `NULL` before accessing the stack. The stored object is not freed. Time complexity: O(1).
- **Peek (`stack_peek`)**: Return the top element without removing it. Returns `0` on success or `-1` if the stack pointer is `NULL`, the output pointer is `NULL`, or the stack is empty. The output pointer must be initialized to `NULL` before accessing the stack. Time complexity: O(1).
- **IsEmpty (`stack_is_empty`)**: Check whether the stack contains any elements. Returns `1` if empty, `0` if not empty, and `-1` if the stack pointer is `NULL`. Time complexity: O(1).
- **Memory Cleanup (`stack_destroy`)**: Release the Stack and its internal Linked List structure. Returns `0` on success or `-1` if the stack pointer is `NULL` or the internal Linked List cannot be destroyed. Stored objects must not be freed.

### 2.2 Implementation Constraint

- The Stack must not implement its own node logic.
- All internal storage operations must use the public Linked List API.
- The Stack must not access or modify Linked List internal structures directly.
- The Stack must use the head of the Linked List as the top of the Stack to guarantee O(1) complexity for push, pop, and peek.
- The Stack must manage the Linked List lifecycle through `ll_create()` and `ll_destroy()`.

### 2.3 Memory Ownership

- The Stack owns and manages its internal Linked List structure.
- The Stack does not own the objects stored in it.
- `stack_pop()` returns the stored pointer without freeing the object.
- `stack_destroy()` releases the Stack and its internal structures, but does not free stored objects.
- The caller is responsible for managing the lifetime of stored objects.

## 3. Complexity Analysis

| Operation | Time Complexity | Auxiliary Space Complexity |
| :--- | :--- | :--- |
| Create | O(1) | O(1) |
| Push | O(1) | O(1) |
| Pop | O(1) | O(1) |
| Peek | O(1) | O(1) |
| IsEmpty | O(1) | O(1) |
| Destroy | O(n) | O(1) |

Where `n` represents the number of elements stored in the Stack.

The Stack uses the head of the underlying Linked List as its top, allowing all top-level operations to execute in constant time.