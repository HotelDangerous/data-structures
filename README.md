# C++ Data Structures

A collection of data structures implemented in C++ for practice.

The goal of this project is to improve my understanding of C++ fundamentals, including:

- templates
- dynamic memory management
- copy and move semantics
- the Rule of 3/5
- basic testing
- CMake/project organization
- common data structure behavior

These implementations are for learning purposes and are not intended to replace the C++ Standard Library.

## Implemented

- Array-backed stack

## In Progress

- Singly linked list
- Linked-list queue

## Project Structure

```text
cpp-data-structures/
├── include/
│   └── array_stack.hpp
├── tests/
│   └── array_stack_tests.cpp
├── examples/
└── README.md
```

## Building Tests

Example compile command:

```bash
g++ tests/array_stack_tests.cpp -Iinclude -std=c++20 -Wall -Wextra -pedantic -o array_stack_tests
```

Run the tests:

```bash
./array_stack_tests
```

## Notes

This project is intentionally written using manual memory management in some places so I can practice ownership, destructors, copy constructors, copy assignment, move constructors, and move assignment.

In real C++ code, I would usually prefer standard containers such as `std::vector`, `std::stack`, `std::queue`, and smart pointers where appropriate.
