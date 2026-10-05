# Specification: Generic Stack (LIFO)

## 1. Objective
Implement a generic Stack (Last-In, First-Out) by leveraging the existing Linked List implementation. The goal is to demonstrate code reuse and the Adapter design pattern.

## 2. Functional Requirements

### 2.1 Core Operations
- **Initialization**: Create an empty stack.
- **Push**: Add an element to the top of the stack. This must be an $O(1)$ operation.
- **Pop**: Remove and return the element from the top of the stack. This must be an $O(1)$ operation.
- **Peek**: Return the top element without removing it.
- **IsEmpty**: Check if the stack contains any elements.
- **Memory Cleanup**: Destroy the stack and all internal elements.

### 2.2 Implementation Constraint
The Stack must not implement its own node logic. It must use the `LinkedList` API for all internal storage and memory management.

## 3. Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| Push | $O(1)$ | $O(1)$ |
| Pop | $O(1)$ | $O(1)$ |
| Peek | $O(1)$ | $O(1)$ |
| IsEmpty | $O(1)$ | $O(1)$ |