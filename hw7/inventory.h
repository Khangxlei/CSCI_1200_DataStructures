/*
This is a header (declaration) file for the Inventory class.
This header file declares functions related to a specific
costume, which the main program will need to access/modify
information of that costume. 
*/

#ifndef inventory_h
#define inventory_h

#include <string>
#include <vector>
#include <ostream>

#include "customer.h"

class Inventory{
public:
	//Constructor
	Inventory(std::string& costume_, int c) : copies(c), costume(costume_){}

	//Accessors
	int getCopies(){return copies;}
	std::string& getCostume(){return costume;}
	std::vector<Customer> getCustomers(){return customers; }

	//Modifiers
	void addCopies(int c){copies += c; }
	void returnCostume(std::string& customer);
	void rentCostume(std::string& customer);

	//Member functions
	void costume_lookup(std::ostream& cout);

private:
	//REPRESENTATIONS
	int copies;
	std::string costume;
	std::vector<Customer> customers;
};

#endif