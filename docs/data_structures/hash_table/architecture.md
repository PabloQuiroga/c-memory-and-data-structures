# Architecture: Generic Hash Table

## 1. Data Structure Design
The Hash Table is implemented as an array of `LinkedList` pointers.

### Struct Definitions
```c
typedef struct {
    void *key;
    void *value;
} HashEntry;

typedef struct {
    LinkedList **buckets; // Array of pointers to Linked Lists
    size_t capacity;      // Number of buckets
} HashTable;
```
### Design Justification
- `LinkedList **buckets`: Using an array of lists (Chaining) ensures that the table never "fills up" in a way that prevents insertion, and it leverages the existing `LinkedList` implementation for reliability.
    - `HashEntry`: A separate structure for the entry allows us to store both the key and the value together in each node of the list.

## 2. API Definition
   ### 2.1 Lifecycle
   - `int ht_create(HashTable **table, size_t capacity)`
   - `int ht_destroy(HashTable *table)`
   ### 2.2 Core Operations
   - `int ht_insert(HashTable *table, void *key, void *value)`
   - `int ht_get(HashTable *table, void *key, void **out_value)`
   - `int ht_remove(HashTable *table, void *key)`

## 3. Hashing Logic
   1. **Key Processing**: The key (string) is passed through a hash function (e.g., DJB2).
   2. **Indexing**: The resulting hash is reduced using the modulo operator: `index = hash % capacity`.
   3. **Storage**: `The HashEntry` is inserted into the `LinkedList` at `buckets[index]`.