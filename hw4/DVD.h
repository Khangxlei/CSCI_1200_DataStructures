/*
This is a header file that is used to declare the DVD class, as well as its
member functions and variables. 

03.04.2021
Khang Le
Data Structures
*/
#ifndef __DVD_h_
#define __DVD_h_

#include <iostream>

using namespace std;

class DVD {
public: 

	//Simple class declaration
	DVD(const unsigned int c, const string m);

	//Accessors
	const string get_name(){return movie;}
	bool available() const {return copies>0;}
	
	//Modifiers
	void shipped(); //Does corresponding actions when a DVD is shipped to a customer
	string printDVD(); //Prints out the information about the DVD
	void returnDVD(); //Modify variables when a customer returns a DVD
	void addCopies(const unsigned int cop){copies += cop; } //Simply add more copies to an exisiting DVD

private:
	//Representation private member variables
	unsigned int copies;
	unsigned int original_copies;
	string movie;
	unsigned int checked_out;
};

#endif

