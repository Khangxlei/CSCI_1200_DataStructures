#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(){
	std::string s = "sam smith";
	int pos = s.find(" ");
	string last_name = s.substr(pos+1, s.size()-(pos+1));
	cout << last_name << endl;
}