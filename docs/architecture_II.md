# Architecture: Generic Singly Linked List

## 1. Data Structure Design
The Linked List is implemented as a series of connected nodes, where each node contains a data pointer and a pointer to the next node.

### Struct Definitions
```c
typedef struct Node {
    void *data;            // Pointer to the actual data
    struct Node *next;     // Pointer to the next node in the sequence
} Node;

typedef struct {
    Node *head;            // Pointer to the first node in the list
    size_t size;           // Current number of elements
} LinkedList;
```
### Design Justification
- `struct Node`: Essential for creating the linked structure. The next pointer allows the list to grow dynamically without needing a contiguous block of memory.
- `LinkedList Wrapper`: By using a separate structure for the list, we can store metadata (like the current size) without having to traverse the entire list every time we need to know its length.
- `void *data: Ensures the list remains generic, allowing it to store any data type.

## 2. API Definition (Interface)

The library follows the same error-handling pattern as the Dynamic Array, returning an integer error code (`0` for success, `-1` for failure).

### 2.1 Lifecycle Management
- `int ll_create(LinkedList **list)`
    - Initializes the list structure and sets head to NULL.
- `int ll_destroy(LinkedList *list)`
    - Iteratively frees all nodes in the list and then the list structure itself.

### 2.2 Element Manipulation
- `int ll_insert_head(LinkedList *list, void *element)`
    - Creates a new node and places it at the front. $O(1)$ complexity.
- `int ll_insert_tail(LinkedList *list, void *element)`
    - Traverses to the end of the list and appends a new node. $O(n)$ complexity.
- `int ll_get(LinkedList *list, size_t index, void **out_element)`
    - Traverses the list to the given index and retrieves the data.
- `int ll_remove(LinkedList *list, size_t index)`
    - Unlinks the node at the given index and frees its memory.

### 2.3 Utility
- `size_t ll_get_size(LinkedList *list)`

## 3. Node Lifecycle Logic
When adding a new element:
1. Allocate memory for a `Node`.
2. Assign the `void *element` to `node->data`.
3. Set `node->next` to the current head (for head insertion).
4. Update `list->head` to the new node.