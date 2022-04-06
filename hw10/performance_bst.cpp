#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

// defined in performance.cpp
void usage();

//Function sorts through STL container
template <class T>
void bst_sort(map<T, int>& mp, std::ostream &ostr, int &output_count, const int &optional_arg, const string& first_sorted){

    // create an iterator to go through bst
    typename map<T, int>::iterator it;
    output_count = 0;

    //the tree is already sorted, we simply go through the bst and print
    for (it = mp.begin(); it != mp.end() && output_count <optional_arg; ++it){
        for (unsigned int i=0; i<it->second && output_count < optional_arg; ++i){
            ostr << it->first << endl;
            output_count++;
        }
    }
}

//Function finds the value with highest occurence
template <class T>
void bst_mode(map<T, int>& mp, ostream& ostr, int& output_count){
    //create iterator for map, map keys are the input data and value is the occurence that data
    typename map<T, int>::iterator it;
    int maxOcc= 0;
    T mode;
    //traverse the map, checking for the highest value
    for (it = mp.begin(); it != mp.end(); ++it){
        if (it->second > maxOcc) {
            maxOcc = it->second;
            mode = it->first;
        }
    }
    ostr << mode << endl;
    output_count = 1;
}

//Function iterates through the map to find the closest pair of integers
void bst_closest_pair(map<int, int>& mp, ostream& ostr, int& output_count, int& closest){
    output_count = 2;

    // when parsing input data, we find if there were any duplicates, if there were they would be 
    // the closest pair
    if (closest != 9999) ostr << closest << '\n' << closest << endl;

    //if there are no duplicates, we go through the map to find the closest pairs
    else {

        //create two iterators that we can compare
        map<int, int>::iterator current = mp.begin();
        map<int, int>::iterator previous = mp.begin();
        ++current;

        //variables declaration
        int dist;
        int smallest_dist = 9999;

        //output values
        int pair1;
        int pair2;

        // traverse map with both iterators, each time comparing both iterators 
        // to find closest pair
        for (; current != mp.end(); ++current, ++previous){
            dist = current->first - previous->first;
            //if current distance is smaller than the current smallest distance
            if (dist < smallest_dist){
                smallest_dist = dist;
                pair1 = previous->first;
                pair2 = current->first;
            }
        }
        //output
        ostr << pair1 << endl;
        ostr << pair2 << endl;
    }
}

//helper function that finds common substring between 2 strings
const string bstmatch_substr (const string& s1, const string& s2){
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

// function finds the longest substring from the map
void bst_longest_substring(map<string, int>& mp, ostream& ostr, int& output_count){
    //go through map and find duplicate values, set that as our longest substring first
    string maxDup = "";
    map<string, int>::iterator it;
    for (it = mp.begin(); it!= mp.end(); ++it){
        if (it->second > 1 && (it->first).size() > maxDup.size()){
            maxDup = it->first;
        }
    }

    string maxUnique = "";
    //go through map and find longest substring that are unique
    for (it = mp.begin(); it!=mp.end(); ++it){
        map<string, int>::iterator it2 = it;
        ++it2;
        //create 2nd iterator based on the first iterator
        for (; it2!= mp.end(); ++it2){
            string s1 = it->first;
            string s2 = it2->first;
            string match = bstmatch_substr(s1, s2);
            if (match.size() > maxUnique.size()){
                maxUnique = match;

            }
        }
    }
    string output_mode;
    (maxUnique.size() > maxDup.size()) ? output_mode = maxUnique : output_mode = maxDup;
    ostr << output_mode << endl;
    output_count = 1;

}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a vector of strings
    map<string, int> mp;

    // load input data into ordered map
    std::string s;
    input_count = 0;
    int tmp_count = 0;

    while (istr >> s) {
        map<string, int>::iterator find = mp.find(s);
        mp[s] += 1;
      
        if (find == mp.end()){
            if (operation == "remove_duplicates") {
                ostr << s << endl;
                tmp_count++;
            }
        }

	    input_count++;
    }

    if      (operation == "sort")            	 { bst_sort              (mp,ostr,output_count, mp.size()*2, "X");    }
    else if (operation == "remove_duplicates")   { output_count = tmp_count; }
    else if (operation == "mode")                { bst_mode              (mp,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")        { bst_sort               (mp,ostr,output_count,optional_arg, "first_sorted"); }
    else if (operation == "longest_substring")   { bst_longest_substring  (mp,ostr,output_count); }
    //else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    map<int, int> mp;

    // load input data into ordered map
    int v;
    input_count = 0;
    int closest = 9999;
    int tmp_count = 0;
    
    while (istr >> v){
        map<int, int>::iterator it = mp.find(v);
        if (it != mp.end()) closest = v;

        mp[v] += 1;
      
        if (it == mp.end()){
            if (operation == "remove_duplicates") {
                ostr << v << endl;
                tmp_count++;
            }
        }

     	input_count++;
    }

    if      (operation == "sort")                { bst_sort              (mp,ostr,output_count, mp.size()*2, "X"); }
    else if (operation == "remove_duplicates")   { output_count = tmp_count; }
    else if (operation == "mode")                { bst_mode              (mp,ostr,output_count); }
    else if (operation == "closest_pair")        { bst_closest_pair      (mp,ostr,output_count, closest); }
    else if (operation == "first_sorted")        { bst_sort              (mp,ostr,output_count, optional_arg, "first_sorted"); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
