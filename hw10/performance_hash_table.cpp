#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// defined in performance.cpp
void usage();


//Function sorts through the unordered map and output it
template <class T>
void ht_sort(unordered_map<T, int>& mp, std::ostream &ostr, int &output_count, const int &optional_arg, const string& first_sorted){
	output_count = 0;
	typename unordered_map<T, int>::iterator it;

    //iterator through the map until it is empty
	while (mp.size() > 0 && output_count< optional_arg){
		it = mp.begin();
		T min = it->first;
		typename unordered_map<T, int>::iterator delete_itr = it;
		//go through the current map and find the smallest value
        for (; it!= mp.end(); ++it){
			if (it->first < min){
				min = it->first;
				delete_itr = it;
			}
		}
        //if the smallest value occurs more than one, we print all of it
		for (int i=0; i < (delete_itr->second) && output_count < optional_arg; ++i){
			ostr << min << endl;
			output_count++;
		}
        //erase smallest value in the map
		mp.erase(delete_itr);
	}
}

//Finds the data that occurs the most in the map
template <class T>
void ht_mode(unordered_map<T, int>& mp, ostream& ostr, int& output_count){
	T output_mode;
	int maxOcc = 0;
    //goes through the map and check its second pair value (occurences), and output the one that has the highest value
	typename unordered_map<T, int>::iterator it = mp.begin();
	for (; it!= mp.end(); ++it){
		if (it->second > maxOcc){
			maxOcc = it->second;
			output_mode = it->first;
		}
	}
	ostr << output_mode << endl;
	output_count = 1;
}

//find closest pair in the map
void ht_closest_pair(unordered_map<int, int>& mp, ostream& ostr, int& output_count, const int& closest){
	output_count = 2;
	if (closest != 9999) 
		ostr << closest << '\n' << closest << endl;

	else {
		int smallest_dist = 9999;
		int pair1;
		int pair2;

        // loop through unordered map while having another iterator that loops through it again
		for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it){
			unordered_map<int, int>::iterator it2 = it;
			++it2;
			for (; it2!= mp.end(); ++it2){

                //calculate the distance and set it as the smallest one if it is
				int dist = abs((it2->first) - (it->first));
				if (dist < smallest_dist){
					smallest_dist = dist;
					pair1 = it->first;
					pair2 = it2->first;
				}
			}
		}
		if (pair1 > pair2){
			int tmp = pair1;
			pair1 = pair2;
			pair2 = tmp;
		}
		ostr << pair1 << endl << pair2 << endl;

	}
}

//helper function that finds common substring between 2 strings
const string htmatch_substr (const string& s1, const string& s2){
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

void ht_longest_substring(unordered_map<string, int>& mp, ostream& ostr, int& output_count){
    //go through map and find duplicate values, set that as our longest substring first
    string maxDup = "";
    unordered_map<string, int>::iterator it;
    for (it = mp.begin(); it!= mp.end(); ++it){
        if (it->second > 1 && (it->first).size() > maxDup.size()){
            maxDup = it->first;
        }
    }

    string maxUnique = "";
    //go through map and find longest substring that are unique
    for (it = mp.begin(); it!=mp.end(); ++it){
        unordered_map<string, int>::iterator it2 = it;
        ++it2;
        for (; it2!= mp.end(); ++it2){
            string s1 = it->first;
            string s2 = it2->first;
            //use helper function to find the longest matching substring between two of those strings
            string match = htmatch_substr(s1, s2);
            //if the string we just made from the helper function is longer than the current largest substring,
            // we change that into this
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

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

    // parses input data into hash table
  if (type == "string") {
    // load the data into a vector of strings
    unordered_map<string, int> mp;

    std::string s;
    input_count = 0;
    int tmp_count = 0;

    while (istr >> s) {
    	unordered_map<string, int>::iterator find = mp.find(s);
        //find the input data in the hash table, if not then we output it for
        if (find == mp.end()){
            if (operation == "remove_duplicates") {
                ostr << s << endl;
                tmp_count++;
            }
        }

        mp[s] += 1;

	    input_count++;
    }
    if      (operation == "sort")              	 { ht_sort              	(mp,ostr,output_count, mp.size()*2, "XXX"); }
    else if (operation == "remove_duplicates") 	 { output_count = tmp_count; }
    else if (operation == "mode")                { ht_mode              	(mp,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")        { ht_sort      			(mp,ostr,output_count, optional_arg, "first_sorted"); }
    else if (operation == "longest_substring") 	 { ht_longest_substring 	(mp,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    unordered_map<int, int> mp;
    unordered_set<string> st;


    int v;
    input_count = 0;
    int x = -1;
    int index = 1;
    int closest = 9999;
    int tmp_count = 0;

    while (istr >> v){
    	string str = to_string(v);
    	str+=(to_string(x));

    	unordered_map<int, int>::iterator it = mp.find(v);
        if (it != mp.end()) closest = v;

    	st.insert(str);

        if (it == mp.end()){
            if (operation == "remove_duplicates") {
                ostr << v << endl;
                tmp_count++;
            }
        }

        mp[v] += 1;

    	x--;
    	index++;
     	input_count++;
    }
    if      (operation == "sort")              	 { ht_sort              	(mp,ostr,output_count, mp.size()*2, "XXX"); }
    else if (operation == "remove_duplicates")   { output_count = tmp_count; }
    else if (operation == "mode")                { ht_mode              	(mp,ostr,output_count); }
    else if (operation == "closest_pair")      	 { ht_closest_pair          (mp,ostr,output_count, closest); }
    else if (operation == "first_sorted")        { ht_sort      			(mp,ostr,output_count, optional_arg, "first_sorted"); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
