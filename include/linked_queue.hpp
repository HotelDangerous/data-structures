#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>


template <typename T>
class Queue {
  private:
  struct Node {
    Node* next;
    T data;

    Node(const T& value) : next(nullptr), data(value) {}
    Node(T&& value) : next(nullptr), data(std::move(value)) {}
  };

  Node* head;
  Node* tail;

  std::size_t length;
  
  public:
  Queue() : head(nullptr), tail(nullptr), length(0) {}
  ~Queue() { clear(); }

  void enqueue(const T& value) {
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

  void enqueue(T&& value) {
    Node* temp = new Node(std::move(value));

    if (head == nullptr) {
      head = temp;
      tail = temp;
    } else {
      tail->next = temp;
      tail = temp;
    }

    ++length;
  }

  void dequeue() {
    if (head == nullptr) {
      throw std::out_of_range("dequeue called on an empty queue");
    }

    Node* temp = head;
    head = head->next;

    if (head == nullptr) { tail == nullptr; }
    
    delete temp;
    --length;
  }

  const T& front() const { 
    if (head == nullptr) {
      throw std::out_of_range("front called on an empty queue");
    }

    return head->data; 
  }

  T& front() {
    if (head == nullptr) {
      throw std::out_of_range("front called on an empty queue");
    }

    return head->data;
  }
  
  const T& peek() const { 
    if (head == nullptr) {
      throw std::out_of_range("peek called on an empty queue");
    }

    return head->data; 
  }

  T& peek() {
    if (head == nullptr) {
      throw std::out_of_range("peek called on an empty queue");
    }

    return head->data;
  }

  const T& back() const { 
    if (tail == nullptr) {
      throw std::out_of_range("back called on an empty queue");
    }

    return tail->data; 
  }

  T& back() {
    if (tail == nullptr) {
      throw std::out_of_range("back called on an empty queue");
    }

    return tail->data;
  }

  std::size_t size() const { return length; }
  
  bool empty() const { return length == 0; }

  void clear() {
    while (head) { dequeue(); }
  }
};


int main() {
  Queue<char> my_queue;
  
  my_queue.enqueue('h');
  my_queue.enqueue('e');
  my_queue.enqueue('l');
  my_queue.enqueue('l');
  my_queue.enqueue('o');

  while (!my_queue.empty()) {
    std::cout << my_queue.peek();
    my_queue.dequeue();
  }

  std::cout << std::endl;

  my_queue.clear();
}
