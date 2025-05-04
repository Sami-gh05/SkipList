# 🎯 Skip List Implementation

A C++ implementation of a Skip List data structure with support for various operations including insertion, deletion, searching, and rank-based queries.

## 📋 Overview

A Skip List is a probabilistic data structure that allows for efficient search, insertion, and deletion operations with an average time complexity of O(log n). This implementation provides a robust set of features while maintaining simplicity and clarity.

## ✨ Features

- **Basic Operations** 🔧
  - Insert elements with automatic height determination
  - Delete elements
  - Search for elements
  - Find elements by rank
  - Print the entire skip list

- **Advanced Operations** 🚀
  - Truncate the skip list at a specific index
  - Absorb another skip list
  - Handle duplicate elements
  - Maintain length information for efficient rank-based queries

## 🔍 Implementation Details

### Node Structure
Each node contains:
- Value
- Height (determined probabilistically)
- Array of next pointers
- Array of next lengths (for rank-based operations)
- Duplicate flag

### Key Methods

- `add(int x)`: Inserts a new element into the skip list
- `remove(int x)`: Removes an element from the skip list
- `find(int x)`: Searches for an element
- `find_by_rank(int index)`: Finds an element by its rank
- `truncate(int index)`: Creates a new skip list containing elements after the given index
- `absorb(skipList sl)`: Merges another skip list into the current one

## 💻 Usage Example

```cpp
skipList SL;
SL.add(1);
SL.add(2);
SL.add(5);
SL.add(4);
SL.add(3);
SL.add(6);

SL.print_SkipList();

SL.remove(2);

cout << SL.find_by_rank(2) << endl;

skipList newSL = SL.truncate(3);
newSL.print_SkipList();

SL.absorb(newSL);
SL.print_SkipList();
```

## ⏱️ Time Complexities

- Search: O(log n) average case
- Insertion: O(log n) average case
- Deletion: O(log n) average case
- Find by rank: O(log n) average case

## 🛠️ Building and Running

This is a header-only implementation. Simply include the `skipList.cpp` file in your project and compile with a C++ compiler that supports C++11 or later.

## 📝 Notes

- The implementation uses a probabilistic approach to determine node heights
- Duplicate elements are handled gracefully
- The skip list maintains length information for efficient rank-based operations
- The implementation includes a dummy head node for easier edge case handling

## 📄 License

This project is open source and available under the MIT License.
