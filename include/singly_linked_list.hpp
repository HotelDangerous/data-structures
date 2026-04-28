# pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class SinglyLinkedList {
  private:
    // Each link in the list is a Node.
    struct Node {
      Node* next;
      T data;

      Node(const T& value) : next(nullptr), data(value) {}
    };
    
    // SinglyLinkedList: Class attributes
    Node* head;
    Node* tail;

    std::size_t length;

  public:
    // Default constructor and destrtuctor.
    SinglyLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~SinglyLinkedList() { clear(); }

    // Copy constructor deep copies other
    SinglyLinkedList(const SinglyLinkedList& other) :
      head(nullptr), tail(nullptr), length(0) {
        Node* current = other.head;

        while (current != nullptr) {
          push_back(current->data);
          current = current->next;
        }
      }

    // Copy assignment deep copies other 
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
      if (this == &other) { return *this; }

      SinglyLinkedList temp(other);

      clear();

      head = temp.head;
      tail = temp.tail;
      length = temp.length;

      temp.head = nullptr;
      temp.tail = nullptr;
      temp.length = 0;

      return *this;
    }
    
    // Move constructor steals nodes from other.
    SinglyLinkedList(SinglyLinkedList&& other) noexcept :
      head(other.head),
      tail(other.tail),
      length(other.length) {
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
      }
    
    // Move assignment steals nodes from other.
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
      if (this == &other) { return *this; }

      clear();

      head = other.head;
      tail = other.tail;
      length = other.length;

      other.head = nullptr;
      other.tail = nullptr;
      other.length = 0;

      return *this;
    }

    // Add new element at the front of the list.
    // Increments length.
    void push_front(const T& value) {
      Node* temp = new Node(value);

      if (tail == nullptr) {
        head = temp;
        tail = temp;
      } else {
        temp->next = head;
        head = temp;
      }

      ++length;
    }

    // Add new element at the back of the list.
    // Increments length.
    void push_back(const T& value) {
      Node* temp = new Node(value);
      
      if (head == nullptr) {
        head = temp;
        tail = temp;
      } else {
        tail->next = temp;
        tail = temp;
      }

      ++length;
    }
    
    // Remove element from the front of the list.
    // Decrements length.
    void pop_front() {
      if (head == nullptr) {
        throw std::out_of_range("pop_front on an empty list");
      }

      Node* temp = head;
      head = head->next;
      delete temp;

      --length;
    }

    // Remove element from the back of the list.
    // Decrements length
    void pop_back() {
			if (tail == nullptr) {
			    throw std::out_of_range("pop_back on an empty list");
			}

			if (head == tail) {
			    delete head;
			    head = nullptr;
			    tail = nullptr;
			    length = 0;
			    return;
			}

			Node* current = head;

			while (current->next != tail) {
			    current = current->next;
			}

			delete tail;
			tail = current;
			tail->next = nullptr;

			--length;
    }

    // Return the value stored at head.
    const T& front() const {
      if (head == nullptr) {
        throw std::out_of_range("front called on an empty list");
      }

      return head->data;
    }

    // Return the value stored at head.
    T front() {
      if (head == nullptr) {
        throw std::out_of_range("front called on an empty list");
      }

      return head->data;
    }

    // Return the value stored at tail.
    const T& back() const {
      if (tail == nullptr) {
        throw std::out_of_range("back called on an empty list");
      }

      return tail->data;
    }

    // Return the value stored at tail.
    T back() {
      if (tail == nullptr) {
        throw std::out_of_range("back called on an empty list");
      }

      return tail->data;
    }
    
    // Get data stored at the given index.
    // No bounds checking.
    T operator[](std::size_t idx) {
      Node* node = head;
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    // Get data stored at the given index.
    // No bounds checking.
    const T& operator[](std::size_t idx) const {
      Node* node = head;
      for(std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    // Get data stored at the given index.
    // With bounds checking.
    T& at(std::size_t idx) {
      if (idx >= length) {
        throw std::out_of_range("SinglyLinkedList: index out of range");
      }

      Node* node = head;
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }
    
    // Get data stored at the given index.
    // With bounds checking.
    const T& at(std::size_t idx) const {
      if (idx >= length) {
        throw std::out_of_range("SinglyLinkedList: index out of range");
      }

      Node* node = head;
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    // Reverses the direction of the list.
    // Head becomes tail and vice-of-versa.
    void reverse() {
      if (head == nullptr or head->next == nullptr) { return; }

      tail = head;
      Node* prev = nullptr;
      Node* current = head;

      while (current) {
        Node* next = current->next;
        current->next = prev;

        prev = current;
        current = next;
      }

      head = prev;
    }

    // Removes all elements from the list; sets length back to zero.
    void clear() { 
      while (head) { pop_front(); }
    }

    std::size_t size() const { return length; }
    bool empty() const { return length == 0; }
};

