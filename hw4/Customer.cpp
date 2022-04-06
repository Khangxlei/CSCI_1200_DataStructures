/*
This is a implementation file for the Customer class. This file will define the different behaviors
for the different functions that are declared in the Customer.h file. This file will be used to 
contain information on a customer, such as their name, a list of their preferences, and a list 
of the current movies they are holding. These will be used in the main program to acheive its purposes.

03.04.2021
Khang Le
Data Structures
*/

#include <iostream>
#include <list>
#include <string>
#include <iterator>

#include "Customer.h"

using namespace std;

//Class declaration that takes in a name and a list of their preferences. Assigns those to member variables
//and the movies_posessed list will be empty since they're not holding onto any movies right now.
Customer::Customer(const string& n, list<string>& preferences){
	name = n;
	movie_preferences = preferences;
	list<string> movies_posessed;
}

//Function will do corresponding actions when a customer receives a movie. It will
//add the movie into the possession list of the customer, while erasing that movie
//off of their preference list.
void Customer::receives(const string& dvd_name){
	movies_posessed.push_back(dvd_name);
	list<string>::iterator itr;
	for (itr = movie_preferences.begin(); itr!=movie_preferences.end(); ++itr){
		if (*itr == dvd_name) {
			movie_preferences.erase(itr); 
			break;
		}
	}
}

//Accessor function returns the newest movie in their possession list,
//which is the one at the end
const string Customer::getNew(){
	list<string>::iterator itr = movies_posessed.end();
	itr--;
	return *itr;
}

//Function prints out information of a customer with the correct format, such as
//their list of movie possessions, their name and their movie preferences
string Customer::printCustomer(){
	string output; //Create variable to be returned to main program can print it into output file

	//If statements that checks for sizes of list, to print out correct format based on its values
	if (movies_posessed.size() > 0){
		//If customer's possession list is more than one, print 'movies', if it only has 1 then only
		//print 'movie'
		if (movies_posessed.size() > 1){
			output += this-> get_name() + " has " + to_string(movies_posessed.size()) + " movies:";
		}
		else if (movies_posessed.size() == 1){
			output += this-> get_name() + " has " + to_string(movies_posessed.size()) + " movie:";
		}

		//Prints out the movie names in customer's possessions
		list<string>::iterator itr;
		for (itr = movies_posessed.begin(); itr != movies_posessed.end(); ++itr){
			output += "\n    " + *itr;
		}
	}

	//If customer is holding no movies, prints that out
	else if (movies_posessed.size() == 0) {
		output += this-> get_name() + " has no movies";
	}
	if (movie_preferences.size() == 0){
		return output;
	}
	if (movie_preferences.size() > 0){
		output += "\n  preference list:";
		list<string>::iterator itr;
		for (itr = movie_preferences.begin(); itr != movie_preferences.end(); ++itr){
			output += "\n    " + *itr;
		}
	}
	return output;
}
