/*
A DVD class implementation file that defines the behavior of the different functions
declared in the DVD.h file. The class is used to contain information
regarding the inventory data, which holds the amount of copies that a certain
DVD hold based on its name, all of them which will be used in the 
main program to acheive its purposes.

03.04.2021
Khang Le
Data Structures
*/

#include <iostream>
#include <list>
#include <string>

#include "DVD.h"


using namespace std;

//Class declaration, assigning member variables to input/default arguments
DVD::DVD(const unsigned int c, const string m){
	original_copies = c;
	copies = c;
	movie = m;
	checked_out =0;
}

//When a customer returns a DVD, copies should be increased by one
//and the number of times that this DVD is checked out decrease by one
void DVD::returnDVD(){
	copies += 1; 
	checked_out -= 1;
}

//When DVD is shipped, inventory loses one of its copies and the number
//of times the DVD is checked out increases
void DVD::shipped(){
	checked_out += 1;
	copies -= 1;
}

//Function prints out the information of the DVD, which includes
//how much copies this DVD is currently being chcked out, and 
//how much copies are available
string DVD::printDVD(){
	//Set up a string that will be returned so that the main program
	//will acheive this and print it to the corresponding output file
	string output = "  ";

	//If statements that checks when the value of checked_out and copies
	//are 1 or 0 to modify the output corresponding to its value
	if (checked_out > 1){
		output += to_string(checked_out) + " copies checked out";
	}
	else if (checked_out == 1){
		output += to_string(checked_out) + " copy checked out";
	}
	if (copies >0){
		if (checked_out > 0){
			if (copies > 1){
				output += " and " + to_string(copies) + " copies available";
			}
			else if (copies ==1){
				output += " and " + to_string(copies) + " copy available";
			}
		}
		else if (checked_out == 0){
			if (copies == 1){
				output += "1 copy available";
			}
			else if (copies > 1){
				output += to_string(copies) + " copies available";
			}
		}
	}
	return output;
}
