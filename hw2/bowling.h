/*
This is simply a class header declaration file, used to declare member functions, outside functions, and member variables.
The use of the functions are not in this file, just the function name and its arguments.

02.12.2021
Khang Le
Data Structures
*/

#ifndef __bowling_h_
#define __bowling_h_

#include <iostream>
#include <vector>
#include <string>
#include <sstream> 

using namespace std;

class Bowling{
public:
	//Constructors
	Bowling();
	Bowling(string f, string l, string o);
	Bowling (string f, string l, int t);
	Bowling (string f, string l, int t, vector<int> s);

	//Accessors
	string getFirst() const;
	string getLast() const;
	int getTotal() const;
	string getOutput() const;
	int getStrikes() const;
	int getSpares() const;
	vector<int> Scores() const;

	//Modifiers
	void setOutput(string o);
	void setTotal(int t);
	void setScores(vector<int> s);
	void setStrikes(int strikes_);
	void setSpares(int spares_);

	//Member functions that operates on bowling objects
	void printFinal(int maxNameLen); //Prints the final total score of the player
	void printScoreChart(int maxNameLen); //Print the scorechart of the player
	vector<int> getScores(string s); //Convert a string of scores to a vector of integers

private: // Representation Member variables
	string entire_output;
	string first;
	string last;
	vector<int> scores;
	int total;
	int strikes;
	int spares;
};

//Prototypes for other functions
bool isLessThan(const Bowling& p1, const Bowling& p2);
bool OrderName(const Bowling& p1, const Bowling& p2);
bool moreSpares(const Bowling& p1, const Bowling& p2);
bool moreStrikes(const Bowling& p1, const Bowling& p2);

#endif