#include <iostream>
#include <stdexcept>
#include <string>


template <typename T>
class LinkedList {
  private:

    struct Node {
      T data;
      Node* next;

      Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    std::size_t length;

  public:

    LinkedList() : head(nullptr), tail(nullptr), length(0) {} 
    ~LinkedList() { clear(); }  

    void push_front(const T& value) {
      Node* new_node = new Node(value);

      new_node->next = head;
      head = new_node;

      if (tail == nullptr) { tail = head; }

      ++length;
    }

    void push_back(const T& value) {
      Node* new_node = new Node(value);

      if (tail == nullptr) {
        head = new_node;
        tail = new_node;
      } else {
        tail->next = new_node;
        tail = new_node; 
      }

      ++length;
    }

    void pop_front() {
      if (head == nullptr) {
        return;
      }

      Node* temp = head;
      head = head->next;
      delete temp;

      if (head == nullptr) {
        tail = nullptr;
      }

      --length;
    }

    T& operator[](std::size_t idx) {
      Node* node = head;

      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    const T& operator[](std::size_t idx) const {
      Node* node = head;
      
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    T& at(std::size_t idx) {
      if (idx >= length) {
        throw std::out_of_range("LinkedList index out of range");
      }

      Node* node = head;
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    const T& at(std::size_t idx) const {
      if (idx >= length) {
        throw std::out_of_range("LinkedList index out of range");
      }

      Node* node = head;
      for (std::size_t i = 0; i < idx; ++i) {
        node = node->next;
      }

      return node->data;
    }

    void reverse() {
      if (head == nullptr || head->next == nullptr) { return; }

      Node* previous = nullptr;
      Node* current = head;
      tail = head;

      while (current) {
        Node* next = current->next;
        current->next = previous;
        
        previous = current;
        current = next;
      }

      head = previous;
    }

    std::size_t size() const {
      return length;
    }

    bool empty() const {
      return head == nullptr;
    }

    void clear() {
      while(head) { pop_front(); }
    }
};


int main() {
  LinkedList<char> my_list;

  std::string name = "Keenan@Keenan-MS-7D97:";
  
  for (const auto& character : name) {
    my_list.push_back(character);
  }

  my_list.reverse();

  while(my_list.size() != 0) {
    std::cout << my_list[0];
    my_list.pop_front();
  }

  std::cout << std::endl;

  return 0;
}
