# Specification: Generic Dynamic Array

## 1. Objective
Implement a generic, dynamically resizable array (Dynamic Array) in C. The implementation must be type-agnostic, allowing the storage of any data type while ensuring strict memory safety and efficiency.

## 2. Functional Requirements

### 2.1 Core Operations
The Dynamic Array must provide the following functionality:
- **Initialization**: Create a new array with a specified initial capacity.
- **Insertion (`add`)**: Append an element to the end of the array. If the current capacity is reached, the array must automatically resize (double its size).
- **Access (`get`)**: Retrieve a pointer to the element at a specific index.
- **Removal (`remove`)**: Remove an element at a given index and shift subsequent elements to maintain continuity.
- **Memory Cleanup (`destroy`)**: Free all allocated memory associated with the array and its internal buffer.

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
