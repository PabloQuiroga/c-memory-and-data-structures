# Specification: Generic Hash Table (Chaining)

## 1. Objective
Implement a generic Hash Table in C using the "Separate Chaining" technique to handle collisions. The implementation must demonstrate a deep understanding of hash functions, collision resolution, and the integration of multiple data structures.

## 2. Functional Requirements

### 2.1 Core Operations
- **Initialization (`ht_create`)**:
    - Signature: `int ht_create(HashTable **table, size_t capacity)`.
    - Creates a hash table with a fixed number of buckets.
    - Rejects a NULL output pointer or zero capacity.
    - Initializes `*table` to NULL before memory allocation.
    - Returns 0 on success and -1 on failure.
    - Releases partially allocated resources if initialization fails.

- **Insertion (`ht_insert`)**:
    - Signature: `int ht_insert(HashTable *table, const char *key, void *value)`.
    - Rejects a NULL table or key.
    - Allows empty string keys and NULL values.
    - Copies the key into table-owned memory.
    - Updates the value if the key already exists.
    - Creates a LinkedList for a bucket only when its first entry is inserted.
    - Returns 0 on success and -1 on failure.
    - Failed insertions must not modify the table.

- **Retrieval (`ht_get`)**:
    - Signature: `int ht_get(HashTable *table, const char *key, void **out_value)`.
    - Rejects NULL table, key, or output pointer.
    - Initializes `*out_value` to NULL before performing the lookup.
    - Returns 0 when the key is found, including when its value is NULL.
    - Returns -1 when the key is not found or an error occurs.
    - Does not modify the table.

- **Removal (`ht_remove`)**:
    - Signature: `int ht_remove(HashTable *table, const char *key, void **out_value)`.
    - Rejects NULL table, key, or output pointer.
    - Initializes `*out_value` to NULL before performing the operation.
    - Returns 0 when the key is found and removed.
    - Returns -1 when the key is not found or an error occurs.
    - Returns the removed value through `out_value`.
    - Frees the copied key and its HashEntry, but does not free the stored value.
    - Destroys the bucket's LinkedList when its last entry is removed.

- **Memory Cleanup (`ht_destroy`)**:
    - Signature: `int ht_destroy(HashTable *table)`.
    - Rejects a NULL table.
    - Iterates through all buckets.
    - Destroys only LinkedLists associated with non-NULL buckets.
    - Frees every stored key and HashEntry before destroying its LinkedList.
    - Frees the bucket array and the table structure.
    - Does not free stored values.
    - Returns 0 on success and -1 on failure.

### 2.2 Technical Constraints
- **Key Type**: Keys must be strings (`const char *`). NULL keys are rejected, while empty strings are allowed.
- **Value Type**: Values use `void *` to support generic data storage. NULL values are allowed.
- **Hash Function**: Implement the classic djb2 algorithm:
    - Initial hash value: `5381`.
    - For each character: multiply the current hash by `33` and add the character value.
    - Use `unsigned long` for the hash calculation.
    - Interpret each character as `unsigned char`.
    - Calculate the bucket index using the hash modulo the table capacity.
- **Key Comparison**: Use `strcmp` for exact, case-sensitive string comparison.
- **Collision Handling**: Use the previously implemented LinkedList with separate chaining.
- **Bucket Initialization**: Allocate LinkedLists lazily. Empty buckets are represented by NULL pointers.
- **Capacity**: The number of buckets is fixed at creation. Automatic resizing is not supported.
- **Memory Ownership**:
    - The Hash Table owns and manages copies of inserted keys.
    - The Hash Table owns its HashEntry structures and internal LinkedLists.
    - Stored values are non-owning references. Their lifetime is managed by the caller.

## 3. Complexity Analysis

Let:
- `n` be the number of stored entries.
- `m` be the fixed number of buckets.
- `α = n / m` be the load factor.
- `L` be the length of the input key.

| Operation | Average Time Complexity | Worst-case Time Complexity |
| :--- | :--- | :--- |
| Insertion | O(L + α · L) | O(n · L) |
| Retrieval | O(L + α · L) | O(n · L) |
| Removal | O(L + α · L) | O(n · L) |

The expected average complexity assumes a reasonably uniform hash distribution.

The worst case occurs when all entries are stored in the same bucket.

The hash calculation requires O(L) time because it processes every character in the key.

**Space Complexity:**
- Total space: O(m + n + K), where K is the total number of characters stored in copied keys.
- Auxiliary space per operation: O(1).

## 4. Edge Case Behavior

- **Invalid Initialization**:
    - A NULL output pointer or zero capacity must cause `ht_create` to return -1.
    - The output pointer must remain NULL after initialization failure.

- **Invalid Parameters**:
    - Operations must reject NULL table pointers.
    - Insertion, retrieval, and removal must reject NULL keys.
    - Retrieval and removal must reject NULL output pointers.
    - Output pointers must be initialized to NULL before performing an operation.

- **Empty Table**:
    - `ht_get` and `ht_remove` must return -1 when the requested key is not found.
    - Failed operations must not modify the table.

- **Empty String Keys**:
    - Empty strings are valid keys and must be handled consistently.

- **NULL Values**:
    - NULL values are valid.
    - Successful retrieval or removal of a NULL value must return 0.

- **Duplicate Keys**:
    - Inserting an existing key must update its value without creating another entry.

- **Collision Handling**:
    - Multiple keys mapping to the same bucket must be stored and retrieved correctly.
    - Removing one entry must not affect other entries in the same bucket.

- **Non-existent Keys**:
    - Removing a key that does not exist must return -1.
    - The table must remain unchanged and the output value must remain NULL.

- **Bucket Cleanup**:
    - Removing the last entry from a bucket must destroy its LinkedList and restore the bucket to NULL.

- **Memory Allocation Failure**:
    - Failed insertions must not leave partially inserted entries or inconsistent bucket state.
    - Failed initialization must release all partially allocated resources.