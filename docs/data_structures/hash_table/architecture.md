## 1. Data Structure Design

The Hash Table is implemented as an array of `LinkedList` pointers, using separate chaining to handle collisions.

### Struct Definitions

```c
typedef struct {
    char *key;
    void *value;
} HashEntry;

typedef struct {
    LinkedList **buckets;
    size_t capacity;
} HashTable;
```

### Design Justification
- `LinkedList **buckets`: An array of LinkedList pointers provides separate chaining for collision resolution.
- `Lazy Initialization`: Buckets are initialized to NULL and their LinkedLists are created only when the first entry is inserted.
- `HashEntry`: Stores a copied string key and a generic value pointer in each list node.
- `Composition`: The Hash Table reuses the existing LinkedList implementation instead of implementing its own node management.
- `Fixed Capacity`: The number of buckets remains unchanged after creation. Automatic resizing is not supported.

## 2. API Definition

### 2.1 Lifecycle
- `int ht_create(HashTable **table, size_t capacity)`
- `int ht_destroy(HashTable *table)`

### 2.2 Core Operations
- `int ht_insert(HashTable *table, const char *key, void *value)`
- `int ht_get(HashTable *table, const char *key, void **out_value)`
- `int ht_remove(HashTable *table, const char *key, void **out_value)`

## 3. Hashing Logic

The Hash Table uses the DJB2 hash algorithm to calculate the bucket index for each string key.

1. **Hash Calculation**:
  - Initialize the hash value to `5381`.
  - Process each character using `hash = hash * 33 + character`.
  - Interpret each character as `unsigned char` to ensure consistent byte values.

2. **Bucket Index**:
  - Calculate the bucket index using `index = hash % capacity`.

3. **Collision Resolution**:
  - Use separate chaining: entries with the same bucket index are stored in the same LinkedList.
  - Compare keys using `strcmp`, which performs case-sensitive string comparison.

4. **Insertion and Lookup**:
  - Create a LinkedList lazily when inserting the first entry into an empty bucket.
  - Search only the LinkedList associated with the calculated bucket index.
  - Destroy the LinkedList and reset its bucket pointer to NULL when its last entry is removed.