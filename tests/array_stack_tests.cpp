#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "array_stack.hpp"

int main() {
  std::cout << "Testing basic stack behavior: ";

  Stack<int> s;

  assert(s.empty());
  assert(s.size() == 0);
  
  s.push(10);
  s.push(20);

  assert(!s.empty());
  assert(s.size() == 2);
  assert(s.top() == 20);

  s.pop();
  assert(s.top() == 10);
  assert(s.size() == 1);
  
  std::cout << "passed\n";
  std::cout << "Testing copy constructor: ";

  Stack<int> copy = s;
  assert(copy.top() == 10);
  assert(copy.size() == 1);

  copy.push(99);
  assert(copy.top() == 99);
  assert(s.top() == 10);
  
  std::cout << "passed\n";
  std::cout << "Testing copy assignment: ";

  Stack<int> assigned;
  assigned = copy;
  assert(assigned.size() == 2);
  assert(assigned.top() == 99);

  std::cout << "passed\n";
  std::cout << "Testing move constructor: ";
  
  Stack<int> moved = std::move(assigned);
  assert(moved.size() == 2);
  assert(moved.top() == 99);

  Stack<int> move_assigned;
  move_assigned = std::move(moved);
  assert(move_assigned.size() == 2);
  assert(move_assigned.top() == 99);

  std::cout << "passed\n";
  std::cout << "Testing move assignment: ";
  
  move_assigned.clear();
  assert(move_assigned.empty());
  assert(move_assigned.size() == 0);
  
  std::cout << "passed\n";
  std::cout << "Testing empty stack error: ";


  bool threw = false;
  try {
    move_assigned.pop();
  } catch (const std::out_of_range&) {
    threw = true;
  }

  assert(threw);
  std::cout << "passed" << std::endl;

  return 0;
}
