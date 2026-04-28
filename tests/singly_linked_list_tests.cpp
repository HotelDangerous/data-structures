#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "singly_linked_list.hpp"


void test_empty_list() {
  std::cout << "Testing empty list... ";

  SinglyLinkedList<int> list;

  assert(list.empty());
  assert(list.size() == 0);

  bool front_threw = false;
  try{ list.front(); }
  catch (const std::out_of_range&) { front_threw = true; }
  assert(front_threw);

  bool back_threw = false;
  try { list.back(); }
  catch (const std::out_of_range&) { back_threw = true; }
  assert(back_threw);

  bool pop_front_threw = false;
  try { list.pop_front(); }
  catch (std::out_of_range&) { pop_front_threw = true; }
  assert(pop_front_threw);

  std::cout << "passed\n";
}

void test_push_front() {
  std::cout << "Testing push_front... ";

  SinglyLinkedList<int> list;

  list.push_front(10);
  list.push_front(20);
  list.push_front(30);

  assert(!list.empty());
  assert(list.size() == 3);
  assert(list.front() == 30);
  assert(list.back() == 10);

  assert(list[0] == 30);
  assert(list[1] == 20);
  assert(list[2] == 10);

  std::cout << "passed\n";
}

void test_push_back() {
  std::cout << "Testing push_back... ";

  SinglyLinkedList<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  assert(!list.empty());
  assert(list.size() == 3);
  assert(list.front() == 10);
  assert(list.back() == 30);

  assert(list[0] == 10);
  assert(list[1] == 20);
  assert(list[2] == 30);
  
  std::cout << "passed\n";
}

void test_pop_front() {
	std::cout << "Testing pop_front... ";

	SinglyLinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	list.pop_front();

	assert(list.size() == 2);
	assert(list.front() == 20);
	assert(list.back() == 30);

	list.pop_front();

	assert(list.size() == 1);
	assert(list.front() == 30);
	assert(list.back() == 30);

	list.pop_front();

	assert(list.empty());
	assert(list.size() == 0);

	std::cout << "passed\n";
}

void test_pop_back() {
	std::cout << "Testing pop_back... ";

	SinglyLinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	list.pop_back();

	assert(list.size() == 2);
	assert(list.front() == 10);
	assert(list.back() == 20);

	list.pop_back();

	assert(list.size() == 1);
	assert(list.front() == 10);
	assert(list.back() == 10);

	list.pop_back();

	assert(list.empty());
	assert(list.size() == 0);

	std::cout << "passed\n";
}

void test_at() {
	std::cout << "Testing at... ";

	SinglyLinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	assert(list.at(0) == 10);
	assert(list.at(1) == 20);
	assert(list.at(2) == 30);

	list.at(1) = 99;
	assert(list.at(1) == 99);

	bool threw = false;
	try {
	    list.at(3);
	} catch (const std::out_of_range&) {
	    threw = true;
	}

	assert(threw);

	std::cout << "passed\n";
}

void test_reverse() {
	std::cout << "Testing reverse... ";

	SinglyLinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);

	list.reverse();

	assert(list.size() == 4);
	assert(list.front() == 40);
	assert(list.back() == 10);

	assert(list[0] == 40);
	assert(list[1] == 30);
	assert(list[2] == 20);
	assert(list[3] == 10);

	std::cout << "passed\n";
}

void test_clear() {
	std::cout << "Testing clear... ";

	SinglyLinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	list.clear();

	assert(list.empty());
	assert(list.size() == 0);

	list.push_back(99);

	assert(list.size() == 1);
	assert(list.front() == 99);
	assert(list.back() == 99);

	std::cout << "passed\n";
}

void test_copy_constructor() {
	std::cout << "Testing copy constructor... ";

	SinglyLinkedList<int> original;

	original.push_back(10);
	original.push_back(20);
	original.push_back(30);

	SinglyLinkedList<int> copy = original;

	assert(copy.size() == 3);
	assert(copy[0] == 10);
	assert(copy[1] == 20);
	assert(copy[2] == 30);

	copy.pop_front();
	copy.push_back(99);

	assert(copy[0] == 20);
	assert(copy[1] == 30);
	assert(copy[2] == 99);

	assert(original.size() == 3);
	assert(original[0] == 10);
	assert(original[1] == 20);
	assert(original[2] == 30);

	std::cout << "passed\n";
}

void test_copy_assignment() {
	std::cout << "Testing copy assignment... ";

	SinglyLinkedList<int> original;

	original.push_back(1);
	original.push_back(2);
	original.push_back(3);

	SinglyLinkedList<int> assigned;

	assigned.push_back(100);
	assigned.push_back(200);

	assigned = original;

	assert(assigned.size() == 3);
	assert(assigned[0] == 1);
	assert(assigned[1] == 2);
	assert(assigned[2] == 3);

	assigned.pop_front();
	assigned.push_back(99);

	assert(assigned[0] == 2);
	assert(assigned[1] == 3);
	assert(assigned[2] == 99);

	assert(original.size() == 3);
	assert(original[0] == 1);
	assert(original[1] == 2);
	assert(original[2] == 3);

	std::cout << "passed\n";
}

void test_move_constructor() {
	std::cout << "Testing move constructor... ";

	SinglyLinkedList<int> original;

	original.push_back(10);
	original.push_back(20);
	original.push_back(30);

	SinglyLinkedList<int> moved = std::move(original);

	assert(moved.size() == 3);
	assert(moved[0] == 10);
	assert(moved[1] == 20);
	assert(moved[2] == 30);
	assert(moved.front() == 10);
	assert(moved.back() == 30);

	std::cout << "passed\n";
}

void test_move_assignment() {
	std::cout << "Testing move assignment... ";

	SinglyLinkedList<int> original;

	original.push_back(10);
	original.push_back(20);
	original.push_back(30);

	SinglyLinkedList<int> moved;

	moved.push_back(100);
	moved.push_back(200);

	moved = std::move(original);

	assert(moved.size() == 3);
	assert(moved[0] == 10);
	assert(moved[1] == 20);
	assert(moved[2] == 30);
	assert(moved.front() == 10);
	assert(moved.back() == 30);

	std::cout << "passed\n";
}

int main() {
	test_empty_list();
	test_push_front();
	test_push_back();
	test_pop_front();
	test_pop_back();
	test_at();
	test_reverse();
	test_clear();
	test_copy_constructor();
	test_copy_assignment();
	test_move_constructor();
	test_move_assignment();

	std::cout << "\nAll singly linked list tests passed.\n";

	return 0;
}
