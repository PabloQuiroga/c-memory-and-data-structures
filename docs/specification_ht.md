# Specification: Generic Hash Table (Chaining)

## 1. Objective
Implement a generic Hash Table in C using the "Separate Chaining" technique to handle collisions. The implementation must demonstrate a deep understanding of hash functions, collision resolution, and the integration of multiple data structures.

## 2. Functional Requirements

### 2.1 Core Operations
- **Initialization**: Create a hash table with a fixed number of buckets (slots).
- **Insertion (`ht_insert`)**: Map a key to a bucket using a hash function and store the key-value pair. If a collision occurs, the element is added to a linked list at that bucket.
- **Retrieval (`ht_get`)**: Compute the hash of the key and search for the value in the corresponding bucket's linked list.
- **Removal (`ht_remove`)**: Locate the key in the appropriate bucket and remove the node from the linked list.
- **Memory Cleanup (`ht_destroy`)**: Free all buckets, all nodes in every linked list, and the table structure.

### 2.2 Technical Constraints
- **Hash Function**: Implement a simple but effective hash function for strings.
- **Genericity**: Use `void*` for both keys and values to maintain the portfolio's generic pattern.
- **Collision Handling**: Must use the previously implemented `LinkedList` to handle collisions.

## 3. Complexity Analysis (Average Case)

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| Insertion | $O(1)$ | $O(1)$ |
| Retrieval | $O(1)$ | $O(1)$ |
| Removal | $O(1)$ | $O(1)$ |