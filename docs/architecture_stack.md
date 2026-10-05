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
- `Interface Restriction`: The Stack only exposes push, pop, and peek, hiding the rest of the list's functionality to ensure the LIFO property is never violated.

## 2. API Definition

### 2.1 Lifecycle
- `int stack_create(Stack **stack)`
    - Internally calls `ll_create`.
- `int stack_destroy(Stack *stack)`
    - Internally calls `ll_destroy`.

### 2.2 Stack Operations
- `int stack_push(Stack *stack, void *element)`
    - Internally calls `ll_insert_head`.
- `int stack_pop(Stack *stack, void **out_element)`
    - Internally calls `ll_remove` at index 0.
- `void* stack_peek(Stack *stack)`
    - Internally calls `ll_get` at index 0.
- `int stack_is_empty(Stack *stack)`
    - Checks if `ll_get_size` is 0.