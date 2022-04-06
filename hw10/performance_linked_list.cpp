#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

using namespace std;

// defined in performance.cpp
void usage();

//sorts the STL list class
template <class T>
void list_sort(std::list<T>& lst, std::ostream& ostr, int& output_count){
	// use the list sort algorithm
	lst.sort();
	output_count = lst.size();
	typename std::list<T>::iterator itr;

	//go through list and print it
	for (itr = lst.begin(); itr != lst.end(); ++itr){
		ostr << *itr << endl;
	}
}

//remove duplicates while keeping original order
template <class T>
void list_remove_duplicates(list<T>& lst, ostream& ostr, int& output_count){
	//create 2 iterators to go through the list 
	typename list<T>::iterator it;
	typename list<T>::iterator itr2;

	//for loop checks for duplicates, if so then delete it
	for (it = lst.begin(); it!= lst.end(); ++it){
		for (itr2 = lst.begin(); itr2 != it; ++itr2){
			if (*itr2 == *it) { 
				it = lst.erase(it); 
				--it;
				break;
			}
		}
	}

	//print the list
	for (it = lst.begin(); it!= lst.end(); ++it){
		ostr << *it <<endl;
	}
	output_count = lst.size();
}

//function finds the value that occurs the most
template <class T>
void list_mode(list<T>& lst, ostream& ostr, int& output_count){
	//sorts the list to make it easier
	lst.sort();

	//set a current and previous iterator and are always next to each other
	typename list<T>::iterator current;
	current = lst.begin();
	++current;
	typename list<T>::iterator previous;
	previous = lst.begin();

	//variable declaration to find mode
	int current_count = 1;
	int mode = 0;
	T str_mode = *current;

	//goes through sorted list and find duplicates
	for (; current != lst.end(); ++current, ++previous){
		//if there are duplicates, we have a while loop that keeps on counting the duplicates to see how much there are 
		// of one word/number
		if (*current == *previous){
			current_count++;
			if (current_count > mode) {
				mode = current_count;
				str_mode = *current;
			}
			++current;
			++previous;
			//count total number of duplicates
			while (*current == *previous){
				current_count++;
				if (current_count > mode){
					mode = current_count;
					str_mode = *current;
				}
				++current;
				++previous;
			}
		}
		//set current_count back to 1
		current_count = 1;
	}
	output_count = 1;
	ostr << str_mode << endl;
}

//finds the closest pair of integers
void list_closest_pair(list<int>& lst, ostream& ostr, int& output_count){
	assert (lst.size() >= 2);
	// sort the list to make algorithm simpler
	lst.sort();

	// create a current and previous list iterator, they are always next to each other
	list<int>::iterator current = lst.begin();
	list<int>::iterator previous = lst.begin();
	++current;
	unsigned int smallest_dist = 9999;

	//output variable
	unsigned int pair1;
	unsigned int pair2;

	//go through sorted list
	for (; current != lst.end(); ++current, ++previous){
		//calculate distance between the two iterator values
		unsigned int dist = *current - *previous;
		//change values if the current distance is less than the current smallest distance
		if (dist < smallest_dist){
			smallest_dist = dist;
			pair1 = *previous;
			pair2 = *current;
		}
	}
	ostr << pair1 << endl;
	ostr << pair2 << endl;
	output_count = 2;

}

//helper function that finds common substring between 2 strings
const string match_substr (const string& s1, const string& s2){
    string longest_substr = "";
    //goes through first string 
    for (unsigned int i=0; i<s1.size(); ++i){
        //create all possible substrings of length 2 for first string
        string substr = s1.substr(i, 2);
        std::size_t found = s2.find(substr);
        string match_string = "";
        // we find the substring created from string 1 in string 2 and if it exists
        // we further it to find the longest substring
        if (found != string::npos){
            int tmp = 0;
            for (unsigned int j=found; j<s2.size() && tmp+i < s1.size(); ++j, ++tmp){
                if (s2[j] == s1[tmp+i]){
                    match_string += s2[j];
                }
            }

            if(match_string.size() > longest_substr.size()) longest_substr = match_string;
        }

    }
    return longest_substr;   
		
}

//function finds the longest substring
void list_longest_substring(list<string>& lst, ostream& ostr, int& output_count){
	string longest_substr = "";
	//goes through the list
	for (list<string>::iterator it = lst.begin(); it!= lst.end(); ++it){
		list<string>::iterator it2 = it;
		++it2;
		//another for loop that goes through the list starting and the current iterator position
		for (; it2!= lst.end(); ++it2){
			string s1 = *it;
			string s2 = *it2;
			//use helper function to find the longest substring between the two strings
			string match = match_substr(s1, s2);
			if (match.size() > longest_substr.size()) longest_substr = match;
		}
	}
	ostr << longest_substr << endl;
	output_count = 1;
}

// function outputs a portion of sorted list based on optional_arg
template <class T> 
void list_first_sorted(list<T>& lst, ostream& ostr, int& output_count, int& size){
	assert (size >= 1);
	//sort the list
	lst.sort();
	int count = 0;
	typename list<T>::iterator it;
	//print contents of the list in order until we reach the optional_arg count
	for (it = lst.begin(); it != lst.end(); ++it){
		ostr << *it << endl;
		count++;
		if (count >= size) break;
	}
	output_count = size;
}


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

	if (type == "string") {
	    // load the data into a vector of strings
	    list<string> lst;
	    std::string s;
	    input_count = 0;
	    while (istr >> s) {
	      lst.push_back(s);
	      input_count++;
	    }
	    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
	    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
	    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
	    // "closest_pair" not available for strings
	   	else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
	    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  	}

	else {
	    assert (type == "integer");
	    // load the data into a vector of integers
	    std::list<int> lst;
	    int v;
	    input_count = 0;
	    while (istr >> v) {
	      lst.push_back(v);
	      input_count++;
	    }
	    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
	    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
	    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
	    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
	    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
	    // "longest_substring" not available for integers
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  	}
	
  //std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  //exit(0);
}
