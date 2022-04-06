#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

bool is_number(const string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;

    return !s.empty() && it == s.end();
}

string parse_string(string s){
	string result;
	for (unsigned int i=0; s[i] != '-'; ++i){
		result += s[i];
	}
	return result;
}

/*
antelope
elephantlope

*/
const string match_substr (const string& s1, const string& s2){
	string longest_substr = "";
	for (unsigned int i=0; i<s1.size(); ++i){
		string substr = s1.substr(i, 2);
		std::size_t found = s2.find(substr);
		string match_string = "";
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
int main(){
	
	bool d = false;
	vector<int> x;
	for (unsigned int i=0; i<5; ++i)
		x.push_back(i);
	
	vector<int> v;
	v.push_back(1);
	vector<int>::iterator it = v.begin();
	string khang = "kha";
	cout << sizeof(khang) << endl;
}
