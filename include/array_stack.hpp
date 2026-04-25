#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
  private:
    std::size_t length;
    std::size_t capacity;

    T* data;
    
    // Doubles the backing array when capacity is exhausted.
    void resize() {
      std::size_t new_capacity = capacity * 2;
      T* temp = new T[new_capacity];

      for (std::size_t idx = 0; idx < length; ++idx) {
        temp[idx] = std::move(data[idx]);
      }

      delete[] data;
      
      capacity = new_capacity;
      data = temp;
    }

    // Shrinks the backing array when usage drops low.
    // Never shrinks below initial capacity.
    void shrink() {
      std::size_t new_capacity = capacity / 4;
      T* temp = new T[new_capacity];

      for (std::size_t idx = 0; idx < length; ++idx) {
        temp[idx] = std::move(data[idx]);
      }

      delete[] data;
      
      capacity = new_capacity;
      data = temp;
    }

  public:
    // Default constructor: stack with length 0 and capacity 2.
    Stack() : length(0), capacity(2), data(new T[2]) {}

    // Destructor
    ~Stack() { delete[] data; }

    // Copy constructor deep copies other.
    Stack(const Stack& other) : 
      length (other.length), 
      capacity(other.capacity),
      data(new T[other.capacity]) {
        for (std::size_t idx = 0; idx < length; ++idx) {
          data[idx] = other.data[idx];
        }
      }
    
    // Copy assignment deep copies other.
    Stack& operator=(const Stack& other) {
      if (this == &other) { return *this; }
      
      T* temp = new T[other.capacity];
      
      for (std::size_t idx = 0; idx < other.length; ++idx) {
        temp[idx] = other.data[idx];
      }

      delete[] data;

      length = other.length;
      capacity = other.capacity;
      data = temp;

      return *this;
    }
    
    // Move constructor steals the backing array from other.
    // Leaves other in empty destructible state.
    Stack(Stack&& other) noexcept :
      length(other.length), 
      capacity(other.capacity),
      data(other.data) {
        other.length = 0;
        other.capacity = 0;
        other.data = nullptr;
      }
    
    // Move assignment steals the backing array from other.
    // Leaves other in empty destructible state.
    Stack& operator=(Stack&& other) noexcept {
      if (this == &other) { return *this; }

      delete[] data;

      length = other.length;
      capacity = other.capacity;
      data = other.data;

      other.data = nullptr;
      other.length = 0;
      other.capacity = 0;

      return *this;
    }

    // Adds value to the top of the stack
    void push(const T& value) {
      if (length == capacity) { resize(); }

      data[length] = value;
      ++length;
    }

    // Adds value to the top of the stack.
    void push(T&& value) {
      if (length == capacity) { resize(); }

      data[length] = std::move(value);
      ++length;
    }

    // Removes the element at the top of the stack.
    // Throws std::out_of_range if the stack is empty
    void pop() {
      if (length == 0) {
        throw std::out_of_range("pop called on an empty stack");
      }

      --length;

      if (length < capacity / 4 && capacity > 2) { shrink(); }
    }

    // Returns the element at the top of the stack.
    // Throws std::out_of_range if the stack is empty
    T& top() {
      if (length == 0) {
        throw std::out_of_range("top called on an empty stack");
      }

      return data[length-1];
    }
    
    // Returns the element at the top of the stack.
    // Throws std::out_of_range if the stack is empty
    const T& top () const {
      if (length == 0) {
        throw std::out_of_range("top called on an empty stack");
      }

      return data[length-1];
    }
    
    // Resets backing array: empty with capacity of two.
    void clear() {
      delete[] data;
      data = new T[2];

      length = 0;
      capacity = 2;
    }
    
    // Returns the number of elements in the stack.
    std::size_t size() const { return length; }
    
    // Returns true if length is zero.
    bool empty() const { return length == 0; }
};
