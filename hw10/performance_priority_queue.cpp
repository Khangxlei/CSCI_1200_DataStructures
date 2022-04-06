#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;


// defined in performance.cpp
void usage();

//print contents of priority queue in sorted order
template <class T> 
void pq_sort(priority_queue<T, vector<T>, greater<T>>& pq, ostream& ostr, int& output_count, int optional_arg, const string& first_sorted){
  output_count = 0;

  //while priority queue is empty
  while (!pq.empty() && output_count<optional_arg){
    //top() function outputs the value at the top of priority queue
    ostr << pq.top() << endl;
    output_count++;
    //we delete the top element to print the priority queue in order
    pq.pop();
  } 
}

//function finds the value that occurs the most in priority queue
template<class T>
void pq_mode(priority_queue<T, vector<T>, greater<T>>& pq, ostream& ostr, int& output_count){
  int mode = 1;
  //variable that will be used to print
  T str_mode;

  //create two variables to keep track of its occurences
  T current;
  T previous;

  //go through priority queue
  while (!pq.empty()){
    //set current as the top element of queue
    current = pq.top();
    int count = 1;
    //if the previous top element is the same as the current, it means they are duplicates
    if (current == previous){
      //iterate previous and current 
      count++;
      previous = current;
      pq.pop();
      current = pq.top();

      //while loop that goes as long as the two iterating variables are duplicates
      while(current == previous && !pq.empty()){
        count++;
        previous = current;
        pq.pop();
        current = pq.top();
      }
      //while finding duplicates, if count exceed the current highest count
      if (count > mode){
        mode = count;
        str_mode = previous;
      }
      continue;
    }
    previous = current;
    pq.pop();
    current = pq.top();
  }

  //print the value that is the mode
  ostr << str_mode << endl;
  output_count = 1;
}


//find the closest pair of integers in the queue
void pq_closest_pair(priority_queue<int, vector<int>, greater<int>>& pq, ostream& ostr, int& output_count){
  //set current and previous variable
  output_count = 2;
  int prev;
  int current;

  //variable declaration
  int smallest_dist = 9999;
  int pair1;
  int pair2;

  int i=0;
  current = pq.top();
  //goes through priority queue
  while (!pq.empty() && pq.size() >1){
    //find the distance of the top 2 values in the queue
    prev = current;
    pq.pop();
    current = pq.top();
    int dist = abs(current - prev);
    //set values to its correct positions
    if (dist < smallest_dist){
      smallest_dist = dist;
      pair1 = prev;
      pair2 = current;
    }
    
  }
  ostr << pair1 << endl << pair2 << endl;
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a vector of strings
    priority_queue<string, vector<string>, greater<string>> pq;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }
    if      (operation == "sort")              { pq_sort                  (pq,ostr,output_count, pq.size()+3, "XXX"); }
    // I believe the operation remove_duplicates with a priority queue.
    //else if (operation == "remove_duplicates")   { pq_remove_duplicates     (pq,ostr,output_count); }

    else if (operation == "mode")              { pq_mode                  (pq,ostr,output_count); }
    // "closest_pair" not available for strings 
    else if (operation == "first_sorted")      { pq_sort                  (pq,ostr,output_count,optional_arg, "first_sorted" ); }
    
    // I believe the longest_substring operation is unfeasible if we are trying to do with a single instance of the priority queue.
    //else if (operation == "longest_substring") { vector_longest_substring (vec,ostr,output_count); }
    
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    priority_queue<int, vector<int>, greater<int>> pq;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }
    if      (operation == "sort")                { pq_sort                  (pq,ostr,output_count, pq.size()+3, "XXX"); }

    // I believe remove_duplicates is not possible using a priority_queue as the STL container has an order that it keeps the elements that cannot be altered
    //else if (operation == "remove_duplicates")   { pq_remove_duplicates     (pq,ostr,output_count); }

    else if (operation == "mode")                { pq_mode                  (pq,ostr,output_count); }
    else if (operation == "closest_pair")        { pq_closest_pair          (pq,ostr,output_count); }
    else if (operation == "first_sorted")        { pq_sort                  (pq,ostr,output_count,optional_arg, "first_sorted" ); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
