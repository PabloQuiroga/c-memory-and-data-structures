# Specification: Generic Singly Linked List

## 1. Objective
Implement a generic Singly Linked List in C. The implementation must demonstrate proficiency in dynamic memory allocation, pointer manipulation (nodes), and an understanding of the trade-offs between linked structures and contiguous arrays.

## 2. Functional Requirements

### 2.1 Core Operations
The Linked List must provide the following functionality:
- **Initialization**: Create an empty list structure (head pointer initialized to NULL).
- **Insertion at Head (`ll_insert_head`)**: Prepend an element to the list. This must be a constant time $O(1)$ operation.
- **Insertion at Tail (`ll_insert_tail`)**: Append an element to the end of the list.
- **Access/Search (`ll_get`)**: Retrieve a pointer to the element at a specific index by traversing the list.
- **Removal (`ll_remove`)**: Remove a node at a specific index, correctly re-linking the previous node to the subsequent one to avoid breaking the chain.
- **Memory Cleanup (`ll_destroy`)**: Traverse the entire list and free every node and the list container to ensure zero memory leaks.

### 2.2 Genericity
Consistent with the portfolio's architecture, the list must use `void*` pointers to store data, allowing it to be type-agnostic.

## 3. Technical Constraints & Error Handling

### 3.1 Pointer Integrity
- **Null Pointer Protection**: All functions must validate that the list pointer is not NULL before performing operations.
- **Empty List Handling**: Operations like `ll_get` or `ll_remove` on an empty list must be handled gracefully without crashing.

### 3.2 Memory Safety
- **No Memory Leaks**: Every node created via `malloc` must be freed during `ll_destroy`.
- **Allocation Failure**: The system must return an error code if memory allocation for a new node fails.

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