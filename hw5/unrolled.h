/*
This is a template class header file that creates 2 different classes, both of them are used to aid 
in the UnrolledLL class (a total of 3 classes created). The UnrolledLL class is used to mimic
the uses of the STL list, which supports the push_back, push_front, pop_back, pop_front and 
more similar functions. 

Khang Le
Data Structures
03.12.2021

*/

#ifndef UnrolledLL_h_
#define UnrolledLL_h_

#include <iostream>
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;


// NODE CLASS
template <class T>
class Node {
public:

  //Constructors and Destructors
  Node() : next_(NULL), prev_(NULL), num_elements(0), elements(new T [NUM_ELEMENTS_PER_NODE]) {}
  Node(unsigned int num_el, T* el) : num_elements(num_el), elements(el), next_(NULL), prev_(NULL) {}
  ~Node() { delete [] elements; }

  // REPRESENTATION
  T value_;
  Node<T>* next_;
  Node<T>* prev_;
  unsigned int num_elements;
  T *elements;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL, unsigned int o=0) : ptr_(p), offset(o) {} 

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->elements[offset] ;  }

  //Accessors
  Node<T>*& ptr() {return ptr_;}
  unsigned int getOffset() {return offset; }
  T*& elements() {return ptr_->elements; }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter

    //Checks to see if iterator needs to move onto the next node
    if (offset +1 >= ptr_->num_elements ){
      offset = 0;
      ptr_ = ptr_-> next_;
    }

    //Normal case
    else if (offset +1 < ptr_->num_elements){
      offset += 1;
    }
    return *this;
  }

  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    //Corner check case
    if (ptr_ == NULL){
      return temp;
    }
    //Checks to see if iterator needs to move onto the next node
    if (offset +1 >= ptr_->num_elements ){
      offset = 0;
      ptr_ = ptr_-> next_;
    }
    //Normal case
    else if (offset +1 < ptr_->num_elements){
      offset += 1;
    }
    return temp;
  }

  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    //Check for corner case
    if (ptr_-> prev_ == NULL){
      return *this;
    }

    //Checks to see if iterator needs to move onto the next node
    if (offset -1 < 0){
      ptr_ = ptr_-> prev_;
      offset = ptr_-> num_elements;
      offset -= 1;
    }

    //Normal case
    else if (offset -1 > 0){
      offset -= 1;
    }
    return *this;
  }

  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    //Corner check case
    if (ptr_ == NULL){
      return temp;
    }
    //Checks to see if iterator needs to move onto the next node
    if (offset -1 < 0){
      ptr_ = ptr_-> prev_;
      offset = ptr_-> num_elements;
      offset -= 1;
    }
    //Normal case
    else if (offset -1 > 0){
      offset -= 1;
    }
    return temp;
  }

  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

    //Comparison operators
    bool operator==(const list_iterator<T>& r) const { return (ptr_ == r.ptr_) && (offset == r.offset); }
    bool operator!=(const list_iterator<T>& r) const {
      if (ptr_ == r.ptr_){
        return offset != r.offset;
      }
      return ptr_ != r.ptr_;
      }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  unsigned int offset;
};

// LIST CLASS DECLARATION
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  //Typedef
  typedef list_iterator<T> iterator;

  // Accessors
  unsigned int size() const { return size_; }
  bool empty() const { return head_->next_ == NULL; }

  //Simple modifiers
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->elements[0];  }
  T& front() { return head_->elements[0]; }
  const T& back() const { return tail_->elements[tail_->num_elements -1]; }
  T& back() { return tail_->elements[tail_->num_elements -1]; }

  // modify the linked list structure
  void push_front(const T& v); 
  void pop_front(); 
  void push_back(const T& v); 
  void pop_back(); 

  //Print function to aid in debugging
  void print(std::ostream& output);

  //Functions that return iterators 
  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// LIST CLASS IMPLEMENTATION

// This is a print function that allows user to visualize the internal structure of the UnrolledLL class
template <class T> void UnrolledLL<T>::print(std::ostream& os) {
  os << "UnrolledLL, size: " << size_ << std::endl;

  // Create a current node that starts at the head, and a for loop going all the way
  //to the end whilst printing all the element it passes
  Node<T>* current = head_;
  while (current!= NULL){
    os << "node:[" << current->num_elements << "]";
    for (unsigned int i = 0; i< current->num_elements; ++i){
      os << ' ' << current->elements[i];
    }
    os << std::endl;
    current = current->next_;
  }
}

//Operator '=' that allows an assignment constructor
template <class T> UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
    return *this;
  }
  else {return *this; }
}

//Boolean operator '==' that checks if two UnrolledLL objects are the same or not
template <class T> bool operator== (UnrolledLL<T>& first, UnrolledLL<T>& second) {
  if (first.size() != second.size()) 
    return false;

  //Create a typename that is the iterator of each list objects 
  typename UnrolledLL<T>::iterator first_itr = first.begin();
  typename UnrolledLL<T>::iterator second_itr = second.begin();

  //Goes through entire list of one Unrolled Linked List, and compare it with the other
  unsigned int check = 0;
  while (second_itr != second.end()){
    if (*first_itr != *second_itr){
      check++;
      return false;
    }
    ++first_itr;
    ++second_itr;
  }
  if (check == 0){
    return true;
  }
}

//Returns if the two passed linked lists are equal or not, using the operator '==' above
template <class T> bool operator!= (UnrolledLL<T>& first, UnrolledLL<T>& second) {
  return !(second == first);
}

// This function will pushes whatever value is passed to the front of the list
template <class T> void UnrolledLL<T>::push_front(const T& v) {
  //1st special case: Checks to see if the list is empty
	if (size_ == 0){   // Create a node and set head and tail to that node
		Node<T>* tmp = new Node<T>();
		tmp->elements[0] = v;
		head_ = tail_ = tmp;
		head_->num_elements += 1;
		size_ += 1;
	}

  //2nd special case: Checks to see if head is full
	else if (head_->num_elements == NUM_ELEMENTS_PER_NODE){  //Create a separate node and make that the head
		Node<T>* tmp = new Node<T>();
		tmp->elements[0] = v;
		tmp->prev_ = NULL;
		tmp->next_ = head_;
		head_->prev_ = tmp;
		head_ = head_->prev_;
		size_ += 1;
		tmp->num_elements = 1;
	}

  //Normal case: when head isn't full
	else {
		T* tmp = new T [NUM_ELEMENTS_PER_NODE];

    //Goes through the head and copies all the element into the tmp array
  	for (unsigned int i =0; i<(head_->num_elements); ++i){
   	  tmp[i] = head_->elements[i];
   	}
    //Set the first element of the head as the given value
   	head_->elements[0] = v;

    //For loop then starts at the second index of the head, and copies every value
    //from the tmp array into it
    for (unsigned int i=0; i<head_-> num_elements; ++i){
      head_->elements[i+1] = tmp[i];
    }
    delete[] tmp;
  	size_ += 1;
    head_-> num_elements += 1;
	}
}

// This function will delete the very first element of the linked list
template <class T> void UnrolledLL<T>::pop_front() {
	// 1st special case: If the list is empty
  if (size_ == 0)
    return;

	//2nd special case: If there is only one element, delete everything
	if (size_ == 1) {
		delete head_;
		head_ = tail_ = NULL;
		--size_;
		return;
	}

  else {
    // 3rd special case: If the head only has 1 element
    if(head_->num_elements == 1){
      //Deletes the head and assigns the node after that as the head
      iterator itr(head_);
      head_ = head_->next_;
      head_->prev_ = NULL;
      delete itr.ptr();
      size_ -= 1;
    }

    //Normal case: when there are more than one element in the head
    else{
      T* tmp = new T[NUM_ELEMENTS_PER_NODE];

      //Copies every element in the head to a tmp array
      for (unsigned int i=0; i<NUM_ELEMENTS_PER_NODE; ++i){
        tmp[i] = head_->elements[i];
      }

      //Shift every elements from the head to the left
      for (unsigned int i=0; i<NUM_ELEMENTS_PER_NODE-1; ++i){
        head_->elements[i] = tmp[i+1];
      }

      //Delete the last element in the head
      head_->elements[head_->num_elements -1] = T(NULL);
      head_->num_elements -= 1;
      delete[] tmp;
      size_ -=1;
      }
  }
}

// This function will add whatever given value to the back of the linked list
template <class T> void UnrolledLL<T>::push_back(const T& v) {
  // 1st special case: If the list is empty
  	if (size_ == 0){
    //Create a node that is both the head and the tail
		Node<T>* tmp = new Node<T>();
		tmp->elements[0] = v;
		head_ = tail_ = tmp;
		head_->num_elements = 1;
		size_ += 1;
	}
  //2nd special case: If tail is full
	else if (tail_->num_elements == NUM_ELEMENTS_PER_NODE){  //Create a new node and set that as the tail
		Node<T>* tmp = new Node<T>();
		tmp->elements[0] = v;
		tmp->next_ = NULL;
		tail_->next_ = tmp;
		tmp->prev_ = tail_;
		tail_ = tmp;
		size_ += 1;
		tail_->num_elements += 1;
	}
  //Normal case: when tail is not full
	else {
    //Assign the value to the rightmost index of the elements array
    tail_->elements[tail_->num_elements] = v;
    size_ += 1;
    tail_->num_elements += 1;
  }
}

// This function will delete the very last element of the linked list
template <class T> void UnrolledLL<T>::pop_back() {
	// 1st special case: If list is empty
	if (size_ == 0)
		return;

	//2nd special case: If list only has 1 element
	else if (size_ == 1) {   //Deletes everything
		delete head_;
		head_ = tail_ = NULL;
		--size_;
		head_->num_elements =0;
		return;
	}

	else if (size_!= 0 && size_!=1) {

    //3rd special case: If there are only 1 element in the tail
		if (tail_-> num_elements == 0 || tail_->num_elements == 1){ 
      //Sets the tail to its previous node and delete that tail
			Node<T>* tmp = tail_;
			tail_ = tail_->prev_;
			tail_->next_ = NULL;
			delete tmp;
			size_ -=1;
		}
		else {    //Normal case: More than 2 elements in the tail
			tail_->elements[tail_->num_elements -1] = T(NULL);
			size_ -=1;
			tail_-> num_elements -=1;
		}
	}
}

//This function will takes in an iterator and will erase whatever element that iterator is on,
//and returns the iterator
template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  //Error check
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_->next_);

  // One node left in the list with only one element
  if (itr.ptr()->num_elements == 1 && size_ == 1) {
    head_ = tail_ = NULL;   //Sets everything to null
  }

  //When there is only one element in the node that's not a head or tail
  else if (itr.ptr() != head_ && itr.ptr() != tail_ && itr.ptr()->num_elements == 1){
    //Deletes the node and connect the nodes after and before it together
    itr.ptr()->next_->prev_ = itr.ptr()->prev_;
    itr.ptr()->prev_->next_ = itr.ptr()->next_;
  }

  // Removing the head in a list with at least two nodes
  else if (itr.ptr()->num_elements == 1 && itr.ptr() == head_ && head_ != tail_) {
    //Sets head to the next one
    head_ = head_->next_;
    head_->prev_ = NULL;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr() == tail_ && itr.ptr()->num_elements == 1 && head_ != tail_) {
    //Sets tail to its previous one
    tail_ = tail_->prev_;
    tail_->next_ = NULL;
  }
  // Normal remove
  else {
    T* tmp = new T[NUM_ELEMENTS_PER_NODE];

    //For loop copies the values of the exisiting array into the temporary array
    for (unsigned int i=0; i< NUM_ELEMENTS_PER_NODE; ++i){
      tmp[i] = itr.ptr()->elements[i];
    }

    //Starting from the offset, which is the position where are deleting, we will shift every elements
    //to the left, therefore deleting it
    for (unsigned int i= itr.getOffset(); i< itr.ptr()->num_elements -1; ++i){
      itr.ptr()->elements[i] = tmp[i+1];
    }

    //Delete the last element in the array
    itr.ptr()->elements[itr.ptr()->num_elements -1] = T(NULL);
    itr.ptr()->num_elements -= 1;

    //Check if offset is pointing to an empty value in the array
    if (itr.ptr()->num_elements == itr.getOffset()){
      delete[] tmp;
      return result;
    }
    else {
      delete[] tmp;
      return itr;
    }

  }
  delete itr.ptr();
  return result;
}

//This function will take in an iterator, insert a given value at that position and returns back the iterator
template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  T* tempArr = new T[NUM_ELEMENTS_PER_NODE];
  
  //If the node is full
  if (itr.ptr()->num_elements == NUM_ELEMENTS_PER_NODE) {

    //Starting from the iterator offset, we copy every elements after it into 
    //the tempArr.
    Node<T>* newNode = new Node<T>();
    for (unsigned int i = itr.getOffset(); i< NUM_ELEMENTS_PER_NODE; ++i){
      tempArr[i - itr.getOffset()] = itr.ptr()->elements[i];
    }

    //We then copy everything from the tempArr into the new node
    for (unsigned int i = 0; i < (NUM_ELEMENTS_PER_NODE - itr.getOffset()); ++i){
      newNode->elements[i] = tempArr[i];
      newNode->num_elements += 1;
    }

    //Set the element we want to insert to the current node
    itr.ptr()->elements[itr.getOffset()] = v;

    //Delete every elements after the added element in the node
    for (unsigned int i = itr.getOffset()+1; i< NUM_ELEMENTS_PER_NODE; ++i){
      itr.ptr()->elements[i] = T(NULL);
      itr.ptr()->num_elements -= 1;
    }

    //If the array is full and there is only one node, we set the newly created node as a tail and connect it with
    //the head
    if (head_ == tail_){
      tail_ = newNode;
      head_->next_ = newNode;
      tail_->next_ = NULL;
      tail_->prev_ = head_;
    }

    //If the node is full and there is more than 1 node, we connect the newly created node with its corresponding
    //nodes
    else {
      newNode-> prev_ = itr.ptr();
      newNode->next_ = itr.ptr()->next_;
      if (itr.ptr()->next_ == NULL){
        tail_ = newNode;
        tail_->next_ = NULL;
      }
      if (itr.ptr()->next_ != NULL)
        itr.ptr()->next_->prev_ = newNode;
      itr.ptr()->next_ = newNode;
    }
  }

  //Regular operations
  else {

    //Starting from the given offset of the iterator, we copy every elements AFTER it
    //into a temporary array: tempARR
    for (unsigned int i= itr.getOffset(); i < itr.ptr()->num_elements; ++i){
      tempArr[i - itr.getOffset()] = itr.ptr()->elements[i];
    }

    //We then asssign the given value to its corresponding position based on the iterator's position
    itr.ptr()->elements[itr.getOffset()] = v;

    //We then copy every elements from the tempArr into the corresponding positions after
    //the added element 
    for (unsigned int i = 0; i<(itr.ptr()->num_elements - itr.getOffset()); ++i){
      itr.ptr()->elements[i + itr.getOffset() + 1] = tempArr[i];
    }
    itr.ptr()->num_elements += 1;
  }
  delete[] tempArr;
  return itr;
}

//This function will copies a given linked list into the current one here
template <class T> void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Special case of empty list
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node
  head_ = new Node<T>(old.head_->num_elements, old.head_->elements);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p){
    //We create a node that is the same as the current tail,
    //Then we increment the tail until we reach the final one
    tail_->next_ = new Node<T> (old_p-> num_elements, old_p->elements);
    tail_->next_->prev = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}

//Class destructor, helper function for the destructor operator
template <class T> void UnrolledLL<T>::destroy_list(){
  //Create a current node that starts as the head
  Node<T>* current = head_;
  //A while loop that makes the current node goes through all the nodes in the list
  while (current != NULL){
    //Deletes the current node
    Node<T>* nextNode = current->next_;
    delete current;
    current = nextNode;
  }
  //Sets all value to NULL
  head_= NULL;
  size_ = 0;
}

#endif











