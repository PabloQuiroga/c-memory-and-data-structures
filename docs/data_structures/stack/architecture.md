# Architecture: Generic Stack

## 1. Data Structure Design
The Stack is implemented as a wrapper around a `LinkedList`.

### Struct Definition
```c
typedef struct {
    LinkedList *internal_list;
} Stack;
```
### Design Justification
- `Composition over Inheritance`: By containing a LinkedList, the Stack inherits all its memory safety and genericity without duplicating code.
- `Interface Restriction`: The Stack exposes only its own public API, hiding the underlying Linked List operations to ensure the LIFO property is never violated.

## 2. API Definition

### 2.1 Lifecycle

- `int stack_create(Stack **stack)`
  - Validates that the output pointer is not `NULL`.
  - Initializes `*stack` to `NULL` before allocation.
  - Allocates the Stack structure.
  - Creates the internal Linked List using `ll_create`.
  - If Linked List creation fails, releases the allocated Stack structure and returns `-1`.
  - Returns `0` on success or `-1` on failure.

- `int stack_destroy(Stack *stack)`
  - Returns `-1` if the Stack pointer is `NULL`.
  - Destroys the internal Linked List using `ll_destroy`.
  - If Linked List destruction fails, returns `-1` without releasing the Stack structure.
  - Releases the Stack structure after successful Linked List destruction.
  - Does not free stored objects.
  - Returns `0` on success.

### 2.2 Stack Operations

- `int stack_push(Stack *stack, void *element)`
  - Accepts `NULL` elements.
  - Internally calls `ll_insert_head`.
  - Returns `0` on success or `-1` if the Stack pointer is `NULL` or insertion fails.
  - If insertion fails, the Stack remains unchanged.

- `int stack_pop(Stack *stack, void **out_element)`
  - Rejects a `NULL` output pointer or Stack pointer.
  - Initializes `*out_element` to `NULL` before accessing the stack.
  - Retrieves the top element using `ll_get` at index `0`.
  - Removes the top node using `ll_remove` at index `0`.
  - Accepts `NULL` elements.
  - Returns `0` on success or `-1` if the Stack is empty or an operation fails.
  - Does not free the stored object.

- `int stack_peek(Stack *stack, void **out_element)`
  - Rejects a `NULL` output pointer or Stack pointer.
  - Initializes `*out_element` to `NULL` before accessing the stack.
  - Retrieves the top element using `ll_get` at index `0`.
  - Accepts `NULL` elements.
  - Does not modify the stack.
  - Returns `0` on success or `-1` if the Stack is empty or an operation fails.

- `int stack_is_empty(Stack *stack)`
  - Returns `-1` if the Stack pointer or its internal Linked List pointer is `NULL`.
  - Checks whether `ll_get_size` returns `0`.
  - Returns `1` if empty or `0` if not empty.

## 3. Memory Management and Ownership

- The Stack owns its internal Linked List structure.
- The Stack does not own the objects stored in the Linked List.
- `stack_pop()` returns the stored pointer without freeing the object.
- `stack_destroy()` releases the internal Linked List and the Stack structure, but does not free stored objects.
- The caller is responsible for managing the lifetime of stored objects.
- If `stack_push()` fails, the Stack must remain unchanged.
- If `stack_pop()` or `stack_peek()` fails, the output pointer must remain `NULL`.
- A successful `stack_pop()` or `stack_peek()` may return `NULL` when the stored element is `NULL`.
- The Stack must not access Linked List internals directly.