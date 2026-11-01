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
  - Validates that the output pointer is not `NULL`.
  - Initializes the output pointer to `NULL` before attempting allocation.
  - Allocates the `LinkedList` structure.
  - Initializes `head` to `NULL` and `size` to `0`.
  - Returns `0` on success or `-1` on failure.

- `int ll_destroy(LinkedList *list)`
  - Returns `-1` if the list pointer is `NULL`.
  - Iteratively traverses the list and frees every internal node.
  - Frees the list container after all nodes have been released.
  - Does not free the objects referenced by the nodes' `data` pointers.
  - Returns `0` on success.
  - Receives the list pointer by value, so it cannot set the caller's pointer to `NULL`. After successful destruction, the caller must not access or reuse the original pointer because it becomes dangling.

### 2.2 Element Manipulation

- `int ll_insert_head(LinkedList *list, void *element)`
  - Validates that the list pointer is not `NULL`.
  - Allocates a new node and stores the provided element pointer.
  - Links the new node to the current head and updates the list head.
  - Increments `size` after successful insertion.
  - Returns `0` on success or `-1` if the list pointer is `NULL` or memory allocation fails.
  - Runs in \(O(1)\) time.

- `int ll_insert_tail(LinkedList *list, void *element)`
  - Validates that the list pointer is not `NULL`.
  - Allocates a new node and initializes its `next` pointer to `NULL`.
  - If the list is empty, assigns the new node as the head.
  - Otherwise, traverses the list to find the last node and links the new node.
  - Increments `size` after successful insertion.
  - Returns `0` on success or `-1` if the list pointer is `NULL` or memory allocation fails.
  - Runs in \(O(n)\) time.

- `int ll_get(LinkedList *list, size_t index, void **out_element)`
  - Validates that the output pointer is not `NULL`.
  - Initializes `*out_element` to `NULL` before attempting access.
  - Returns `-1` if the list pointer is `NULL` or the index is invalid.
  - Traverses the list to the requested index and assigns the stored pointer to `*out_element`.
  - Returns `0` on success.
  - Runs in \(O(n)\) time.

- `int ll_remove(LinkedList *list, size_t index)`
  - Returns `-1` if the list pointer is `NULL`, the list is empty, or the index is invalid.
  - Traverses the list while keeping track of the previous node.
  - Updates the head when removing the first node; otherwise, updates the previous node's `next` pointer.
  - Frees the removed node without freeing the object referenced by its `data` pointer.
  - Decrements `size` after successful removal.
  - Returns `0` on success.
  - Runs in \(O(n)\) time.

- **Allocation Failure Guarantee**: If memory allocation fails during either insertion operation, the operation returns `-1` and leaves the list unchanged.

### 2.3 Utility

- `size_t ll_get_size(LinkedList *list)`
  - Returns the current number of elements stored in the list.
  - Returns `0` if the list pointer is `NULL`.
  - Runs in \(O(1)\) time because the list maintains its size as metadata.

## 3. Node Lifecycle Logic

### 3.1 Insertion at Head

When inserting a new element at the head:

1. Allocate memory for a new `Node`.
2. Assign the provided `void *element` to `node->data`.
3. Set `node->next` to the current `list->head`.
4. Update `list->head` to point to the new node.
5. Increment `list->size`.

### 3.2 Insertion at Tail

When inserting a new element at the tail:

1. Allocate memory for a new `Node`.
2. Assign the provided `void *element` to `node->data`.
3. Initialize `node->next` to `NULL`.
4. If the list is empty, assign the new node to `list->head`.
5. Otherwise, traverse the list until reaching the last node.
6. Link the last node to the new node.
7. Increment `list->size`.

### 3.3 Removal

When removing a node at a given index:

1. Traverse the list until reaching the target node, keeping track of the previous node.
2. If the target is the head, update `list->head` to the target's next node.
3. Otherwise, update the previous node's `next` pointer to skip the target.
4. Free the removed node.
5. Decrement `list->size`.

The referenced object stored in `node->data` is not freed.

### 3.4 Destruction

When destroying the list:

1. Start traversal at `list->head`.
2. Store the next node before freeing the current node.
3. Free each node until the end of the list is reached.
4. Free the `LinkedList` container.

The objects referenced by the nodes are not freed.