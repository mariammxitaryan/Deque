# Block-Based Deque Implementation

A modern C++ implementation of a double-ended queue (deque) utilizing block-based memory management. This design offers efficient insertions and deletions at both ends while maintaining random access and iterator support.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Design & Implementation](#design--implementation)
- [Usage](#usage)
- [Compilation](#compilation)

---

## Overview

This project implements a deque using a block-based memory allocation strategy. Data is segmented into fixed-size blocks, managed by a dynamically growing map. With custom iterator classes supporting a full range of arithmetic operations, this deque provides:

- **Efficient front and back insertions/removals:** `push_front()` and `push_back()` manage memory seamlessly.
- **Random Access:** Overloaded `operator[]` and `at()` allow safe, direct access to elements.
- **Robust Iterators:** Both mutable and constant iterators support pre/post-increment, decrement, and arithmetic operations.

---

## Features

- **Block-Based Storage:** Organizes data in blocks to reduce memory reallocation overhead.
- **Dynamic Map Growth:** Automatically expands the internal map when capacity is exceeded.
- **Custom Iterators:** Provides forward and backward iteration with support for pointer arithmetic.
- **Bounds Checking:** The `at()` method throws an exception on invalid access.
- **Template Flexibility:** Generic implementation supports any data type and customizable block size.

---

## Design & Implementation

The implementation is divided into two main parts:

1. **Deque Class:**  
   Manages the overall data structure including memory allocation, element access, and size management.
   - **Memory Management:**  
     - `initializeMap()`: Allocates and initializes the internal pointer array.
     - `allocateBlock()` / `deallocateBlock()`: Handles block-level memory allocation.
     - `growMap()`: Expands the map when additional blocks are needed.
   - **Element Operations:**  
     - `push_front()`: Inserts an element at the front.
     - `push_back()`: Inserts an element at the back.
     - `operator[]` / `at()`: Provide random and bounds-checked access.

2. **Iterator Classes:**  
   Custom iterator and const_iterator classes allow seamless traversal.
   - **Iterator Arithmetic:**  
     Supports operations like `++`, `--`, `+`, and `-`.
   - **Comparisons:**  
     Enables equality, inequality, and relational comparisons for sorting and algorithm compatibility.

---

## Usage

Include the header file in your project:

```cpp
#include "dequeHeader.hpp"
```

### Creating a Deque

Instantiate a deque with a specific block size and initial map size:

```cpp
// Create a deque for integers with a block size of 64 and an initial map size of 10 blocks
Deque<int, 64> myDeque(10);
```

### Inserting Elements

Add elements to either end:

```cpp
myDeque.push_front(42);   // Inserts 42 at the front
myDeque.push_back(99);    // Inserts 99 at the back
```

### Accessing Elements

Use random access or bounds-checked methods:

```cpp
int first = myDeque[0];   // Random access using operator[]
int safe  = myDeque.at(1); // Access with bounds checking (throws exception if out of range)
```

### Iteration

Traverse the deque using iterators:

```cpp
for (auto it = myDeque.begin(); it != myDeque.end(); ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl;
```

---

## Compilation

Ensure your compiler supports C++11 or later. Compile your project using:

```bash
g++ -std=c++20 -o dequeExample main.cpp
```

Replace `main.cpp` with your source file that includes `dequeHeader.hpp`.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create your feature branch: `git checkout -b feature/my-feature`
3. Commit your changes: `git commit -am 'Add new feature'`
4. Push to the branch: `git push origin feature/my-feature`
5. Open a pull request.

Please ensure that your changes are well documented and follow the existing code style.

---

Enjoy using this block-based deque implementation, and feel free to contribute to make it even better!
