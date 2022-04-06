/*
This is the header file for the Customer class. This Customer
class is used to store information of a customer in the program
and allow the main program to access/modify informations
related to the customer. 

There are no long functions (all of them are one-liners),
so this will be the only file
*/

#ifndef customer_h
#define customer_h

#include <string>

class Customer{
public:
	//Constructor
	Customer(const std::string& name) : full_name(name), costume("") {}

	//Accessors
	std::string getCostume(){return costume;}
	std::string getName(){return full_name; }

	//Modifiers
	void setCostume(std::string& c){costume = c; }

private:
	//REPRESENTATIONS
	std::string full_name;
	std::string costume;

};

#endif