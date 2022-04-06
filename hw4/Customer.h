/*
This is a header file that is used to declare the DVD class, as well as its
member functions and variables. 

03.04.2021
Khang Le
Data Structures
*/

#ifndef __Customer_h_
#define __Customer_h_

#include <iostream>

using namespace std;

class Customer {
public: 
	//Constructor
	Customer(const string& n, list<string>& preferences);

	//Accessors
	const string get_name() {return name;}
	const list<string>& get_preferences() {return movie_preferences; }
	const string getOld() {return *(movies_posessed.begin()); } //Simply return the oldest movie in the customer's possession list without modifying it
	const string getNew(); //Simply return the oldest movie in the customer's possession list without modifying it
	bool has_max_num_movies() const {return movies_posessed.size() ==3; }
	bool preference_list_empty() const {return movie_preferences.size() == 0; }
	bool posessed_list_empty() const {return movies_posessed.size() == 0; }
	const list<string>& get_possession()  {return movies_posessed; }

	//Modifiers
	void receives(const string& dvd_name); //Function runs when a customer receives a DVD
	void returnOld(){movies_posessed.pop_front(); } //Function runs when customer returns their oldest movie
	void returnNew(){ movies_posessed.pop_back(); } //Function simply remove the newest movie off of customer's preference list
	string printCustomer(); //Function prints out information regarding the customer
	void addPreference(const string& dvd){movie_preferences.push_back(dvd); } //Function adds a movie into their preference list

private:
	//Representation private member variables
	string name;
	list<string> movie_preferences;
	list<string> movies_posessed;
};

#endif
