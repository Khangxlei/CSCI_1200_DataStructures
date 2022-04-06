/*
This is a class storing information /functions of the bowling players that were parsed from the input file.
It holds various functions that helps the main program to accomplish its task of outputting
specific statistics/scores of different bowling players

02.12.2021
Khang Le
Data Structures
*/


#include "bowling.h"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

Bowling::Bowling(){ //Default constructor
	first = "";
	last = "";
	total = 0;
	entire_output ="";
	vector<int> scores;
	strikes = 0;
	spares = 0;
}

Bowling::Bowling(string f, string l, string o){ //Constructor with only names and an output line given
	first = f;
	last = l;
	total = 0;
	entire_output = o;
	vector<int> scores;
	strikes = 0;
	spares = 0;

}

Bowling::Bowling (string f, string l, int t){ //Constructor with only names and total scores given
	first = f;
	last = l;
	total = t;
	entire_output = "";
	vector<int> scores;
	strikes = 0;
	spares = 0;
}

Bowling::Bowling (string f, string l, int t, vector<int> s){ //Constructor with only names, total scores, and a vector of scores given
	first = f;
	last = l;
	total = t;
	scores = s;
	entire_output = "";
	strikes = 0;
	spares = 0;
}

//Function return first name
string Bowling::getFirst() const{
	return first;
}

//Function get last name
string Bowling::getLast() const {
	return last;
}

//Function return that vector of scores that were parsed from the main program
vector<int> Bowling::Scores() const{
	return scores;
}

//Function return the total score of the player
int Bowling::getTotal() const{
	return total;
}

//Function return the number of strikes the player had in a game
int Bowling::getStrikes() const{
	return strikes;
}

//Function return the number of spares the player had in a game
int Bowling::getSpares() const{
	return spares;
}

//Function return the string of output that will be used to put into an output file for grading
string Bowling::getOutput() const{
	return entire_output;
}

//Function sets the amount of strikes the player has
void Bowling::setStrikes(int strikes_){
	strikes = strikes_;
}

//Function sets the amount of spares the player has
void Bowling::setSpares(int spares_) {
	spares = spares_;
}

//Function sets the output string that will be used to put into a file
void Bowling::setOutput(string o){
	entire_output = o;
}

//Function sets the total amount of scores of the player
void Bowling::setTotal(int t){
	total = t;
}

//Function sets the vector of scores of the player
void Bowling::setScores(vector<int> s){
	scores = s;
}

//Function prints the name of the player with their final score for leaderboard
void Bowling::printFinal(int maxNameLen){
	entire_output += first + last + string(maxNameLen- int(first.size()+last.size()), ' ') + string(5-to_string(total).size(),' ') + 
	to_string(total) + '\n';
}

//Function prints out the main part of assignment, which is the scoreboard
void Bowling::printScoreChart(int maxNameLen){
	string a = "| ";
	entire_output += a + first + last + string(maxNameLen- int(first.size()+last.size()), ' ') + " |";

	//Variables declaration for later use
	int increment = 2;
	int col_counter =0;
	int running_score= 0;
	vector<int> round_scores;
	int last_column =0;

	//For loop prints top half of player's score records, this part only contains the scores they got
	//each round, not the running score
	//Each time it will increment by two within the vector of players' scores, if it sees a strike, it will change
	//the increment to one
	for (int i=0; i< int(scores.size()); i+=increment){
		string output_line;

		//If function that operates when it is on the 10th column of the scoreboard
		if (last_column == 5){
		//These three strings are output strings for each scores, to make string manipulation easier
		string x;
		string y;
		string z;
			if (scores[i] + scores[i+1] < 10){ //If function checks if there will only be 2 numbers for the last column
				x = to_string(scores[i]);
				y = to_string(scores[i+1]);
				z = "  ";
				if (scores[i]==0){
					x = '-';
				}
				if (scores[i+1]==0){
					y = '-';
				}
				output_line = x + ' ' + y + z;
				entire_output += ' ' + output_line + " |";
				running_score += scores[i] + scores[i+1];
				round_scores.push_back(running_score);
				total = round_scores[round_scores.size()-1];
				break;
			}
			else if (scores[i] == 10){ //Checks if the first final round throw is a strike (guaranteed to be 3 throws in final round)
				strikes += 1;
				x = "X";
				y = to_string(scores[i+1]);
				z = to_string(scores[i+2]);

				if ((scores[i+1] == 10) || (scores[i+1] == 0) || (scores[i+2] ==10) || (scores[i+2]== 0)){
					if (scores[i+1] == 10){
						strikes += 1;
						y = 'X';
					}
					if (scores [i+2] == 10){
						z = 'X';
					}
					if ((scores[i+2] == 10) && (scores[i+1] != 0)) {
						strikes += 1;
					}
					if (scores [i+1] == 0){
						y = '-';
					}
					if (scores [i+2]==0){
						z = '-';
					}
					if ((scores[i+1] == 0) && (scores[i+2]==10)) {
						spares += 1;
						y = '-';
						z = '/';
					}
				}
			}
			else {
				x = to_string(scores[i]);
				y = "/";
				z = to_string(scores[i+2]);

				if ((scores[i+1] == 10) || (scores[i+2] == 10)) {
					if (scores[i+1] == 10){
						spares += 1;
						x = '-';
						y = '/';
					}
					if (scores[i+2] == 10){
						strikes += 1;
						z = 'X';
					}
				}

				if ((scores[i] == 0) || (scores[i+1] == 0) || (scores[i+2] == 0)) {
					if (scores[i] == 0){
						x = '-';
					}
					if (scores[i+1] == 0){
						y = '-';
					}
					if (scores[i+2] == 0){
						z = '-';
					}
				}
			}
			//After manipulating with string x,y, and z, concatenates all of them into the entire_output string
			//which will be used to output into the file in the main program
			output_line = x + ' ' + y + ' ' + z;
			entire_output += ' ' + output_line + " |";
			running_score += scores[i] + scores[i+1] + scores[i+2];
			round_scores.push_back(running_score);
			total = round_scores[round_scores.size()-1];
			break;
		}
		//Checks if the throw is a strike, change increment of for loop to 1
		if (scores[i] == 10){
			string a = "   X";
			string b = " |";
			entire_output += a + b ;
			increment = 1;
			col_counter += 1;
			running_score += 10 + scores[i+1] + scores [i+2];
			round_scores.push_back(running_score);
			if (col_counter == 9){
				last_column += 5;
			}
			continue;
		}
		if (scores[i] + scores[i+1] <= 10){
			if (scores[i+1]== 10){ //Check if it was a 0 thrown first time but a 10 on second try
				spares += 1;
				output_line = "- /";
				running_score += 10 + scores[i+2];
				round_scores.push_back(running_score);
			}
			else if (scores[i] + scores[i+1]== 10) { //Checks if it's a normal spare
				spares += 1;
				output_line = to_string(scores[i]) + " /";
				running_score += 10 + scores[i+2];
				round_scores.push_back(running_score);
			}
			else if (scores[i] + scores[i+1] < 10){ //Check if it's not a spare or strike
				if ((scores[i]== 0) && (scores[i+1] == 0)){
					output_line = "- -";
				}
				else if (scores[i] == 0) {
					output_line = "- " + to_string(scores[i+1]);
				}
				else if (scores[i+1] == 0){
					output_line = to_string(scores[i]) + " -";
				}
				else {
					output_line = to_string(scores[i]) + ' ' + to_string(scores[i+1]);
				}
				running_score += scores[i] + scores[i+1];
				round_scores.push_back(running_score);
			}
			entire_output += ' ' + output_line + " |";
			increment =2;
			col_counter += 1;

			if (col_counter == 9){
				last_column += 5;
			}
			continue;
		}
		if (last_column == 5){
			break;
		}
	}
	entire_output += "\n| " + string(maxNameLen, ' ') + " |";

	//This part prints the bottom half of each column which contains the running score of each round
	for (int x: round_scores){
		if (x == round_scores[round_scores.size()-1]){
			if (x<100){
				if (x >= 10){
					entire_output += "    " + to_string(x) + " |";
				}
				else {
					entire_output += "     " + to_string(x) + " |";
				}
			}
			else {
				entire_output += "   " + to_string(x) + " |";
			}
			break;
		}
		if (x >= 10){
			if (x >= 100){
				entire_output += ' ' + to_string(x) + " |";
			}
			else {
				entire_output += "  " + to_string(x) + " |";
			}
		}
		else {
			entire_output += "   " + to_string(x) + " |";
		}
	}
	entire_output += '\n';
}

//Function takes in a string of scores that are parsed from the input file, converts them into integers,
//add them into a vector returns that vector
vector<int> Bowling::getScores(string scores) {
	//Makes a vector of strings of scores
	stringstream sstream(scores);
	std::istream_iterator<std::string> total(sstream);
	std::istream_iterator<std::string> words;
	std::vector<std::string> vect(total, words);

	vector<int> vscores;
	//Convert the vector of string scores to int scores
	for (string x: vect){
		stringstream conversion (x);
		int score;
		conversion >> score;
		vscores.push_back(score);
	}
	return vscores;
}

//Boolean function checks if the player's score is less or more than the other player, used for sorting
bool isLessThan(const Bowling& p1, const Bowling& p2){
	return (p1.getTotal() > p2.getTotal());
}

//Boolean function checks if the name of the player is alphabetically before or after the other player, used for sorting
bool OrderName(const Bowling& p1, const Bowling& p2){
	return (p1.getLast() < p2.getLast()) || ((p1.getLast() == p2.getLast()) && (p1.getFirst() < p2.getFirst()));
 }

//Boolean function checks if the number of spares is more than the other player, used for sorting
bool moreSpares(const Bowling& p1, const Bowling& p2) {
	if (p1.getSpares() > p2.getSpares()){
		return 1;
	}
	else if (p1.getSpares() == p2.getSpares()) {
		return (p1.getLast() < p2.getLast()) || ((p1.getLast() == p2.getLast()) && (p1.getFirst() < p2.getFirst()));
	}
	else {
		return 0;
	}
}

//Boolean function checks if the number of strikes is more than the other player, used for sorting
bool moreStrikes(const Bowling& p1, const Bowling& p2) {
	if (p1.getStrikes() > p2.getStrikes()){
		return 1;
	}
	else if (p1.getStrikes() == p2.getStrikes()) {
		return (p1.getLast() < p2.getLast()) || ((p1.getLast() == p2.getLast()) && (p1.getFirst() < p2.getFirst()));
	}
	else {
		return 0;
	}
}