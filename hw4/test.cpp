#include <iostream>
#include <list>
#include <iterator>
#include "Customer.h"

using namespace std;
 

int main() {
	list<Customer> customers;
	list<string> movies;
	movies.push_back("unfriended");
	movies.push_back("scary movie");
	movies.push_back("ted");
	Customer a("khang" , movies);
	Customer b("bob", movies);
	customers.push_back(a);
	customers.push_back(b);
	list<Customer>::iterator itr;
	for (itr = customers.begin(); itr != customers.end(); ++itr){
		cout << itr-> get_name() << endl;
	}
}
