/*
This is the main.cpp program to the template class header file "unrolled.h"
This program is used to test the Unrolled Linked List class, to see if it matches
the STL list class. BasicTests() was given to us, MoreTests() adds some corner cases
and different values types

Khang Le
Data Structures
03.12.2021
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

using namespace std;

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);               //Print function should print out each node, with the corresponding num_elements in each node and their values
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }

  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
///*
void MoreTests() {

  //Different type tests
  UnrolledLL<char> c;
  std::list<char> d;
  for (int i = 'a'; i < 'h'; ++i) {
    c.push_back(i);
    d.push_back(i);
  }  


  UnrolledLL<char> a;
  std::list<char> b;
  a.push_back('a');
  a.push_back('b');
  a.push_back('c');
  a.push_back('d');
  a.push_back('e');
  a.push_back('f');
  a.push_back('g');

  b.push_back('a');
  b.push_back('b');
  b.push_back('c');
  b.push_back('d');
  b.push_back('e');
  b.push_back('f');
  b.push_back('g');

  assert (SAME(a,b));
  cout << "the characters from a to g" << endl;

  //prints out every elements from unrolled linked list
  //test for pre-increment iterator
  for (UnrolledLL<char>::iterator itr = c.begin(); itr != c.end(); ++itr){
    cout << *itr << ' ';
  }
  cout << endl;
  cout << endl;

  //Prints the UnrolledLL representation using print function
  cout << "Intinial UnrolledLL" << endl;
  a.print(cout);
  cout << endl;

  //Testing push and pop functions
  cout << "Testing push and pop functions" << endl;
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 6);
  assert (a.front() == 'b');
  assert (a.back() == 'g');
  a.pop_back();
  b.pop_back();
  assert (a.size() == 5);
  assert (a.front() = 'b');
  assert (a.back() == 'f');
  assert (SAME(a,b));
  cout << "After basic functions" << endl;
  a.print(cout);
  cout << endl;

  // c= [b,c,d,e,f]

  // More editing with corner cases
  std::cout << "more editing with corner cases" << std::endl;
  a.pop_back();
  a.pop_back();
  a.pop_back();

  b.pop_back();
  b.pop_back();
  b.pop_back();

  
  a.pop_front();
  b.pop_front();
  a.print(cout);

  assert (a.size() == 1);
  assert (a.front() == 'c');
  assert (a.back() == 'c');
  a.push_front('B');
  a.push_front('A');
  a.push_back('D');
  a.push_back('E');
  a.push_back('F');

  b.push_front('B');
  b.push_front('A');
  b.push_back('D');
  b.push_back('E');
  b.push_back('F');

  a.print(cout);
  assert (a.size() == 6);
  assert (a.front() == 'A');
  assert (a.back() == 'F');
  assert (SAME(a,b));

  int count = 0;
  //test for post-increment iterator
  for (list<char>::iterator itr = b.begin(); itr != b.end(); itr++){
    if (count == 1 || count == 3 || count == 5){
      itr = b.insert(itr, 'K');
      itr++;
    }
    count++;
  }

  count = 0;
  for (UnrolledLL<char>::iterator itr = a.begin(); itr != a.end(); itr++){
    if (count == 1 || count == 3 || count == 5){
      itr = a.insert(itr, 'K');
      itr++;
    }
    count++;
  }

  assert (SAME(a,b));
  assert (a.size() == 9);
  a.print(cout);
  cout << endl;

  cout << "Testing erase function" << endl;

  for (list<char>::iterator list_itr = b.begin(); list_itr != b.end(); ++list_itr){
    if (*list_itr == 'K'){
      list_itr = b.erase(list_itr);
      list_itr--;
    }
  }

  for (UnrolledLL<char>::iterator unrolled_itr = a.begin(); unrolled_itr != a.end(); ++unrolled_itr){
    if (*unrolled_itr == 'K'){
      unrolled_itr = a.erase(unrolled_itr);
      unrolled_itr--;
    }
  }

  assert (SAME(a,b));
  assert (a.size() == 6);
  assert (a.front() == 'A');
  assert (a.back() == 'F');
  a.print(cout);

}
