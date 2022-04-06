/*
This program will take in an input of score records of bowling players. It will then, based on the user's wish, either output 
a special statistic for each of the player for each game, or a standardized bowling score board with a leaderboard of final scores. 

Example execution:
./hw01.exe example.txt output.txt standard

**inside output.txt file**
------------------------------------------------------------------------------
| Fred Adams   | 2 - | 1 5 | 6 / |   X | 2 2 | - - | - 8 | 2 / | 2 3 | - 2   |
|              |   2 |   8 |  28 |  42 |  46 |  46 |  54 |  66 |  71 |    73 |
------------------------------------------------------------------------------
| Sally Jones  |   X |   X |   X |   X |   X |   X |   X |   X |   X | X X X |
|              |  30 |  60 |  90 | 120 | 150 | 180 | 210 | 240 | 270 |   300 |
------------------------------------------------------------------------------

Sally Jones   300
Fred Adams     73

02.12.2021
Khang Le
Data Structures
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "bowling.h"

using namespace std;

//Function checks whether the passed string is a number or not for parsing later
bool is_number(const std::string& str){
	for (string::const_iterator i = str.begin(); i != str.end(); ++i ){
		if (isdigit(*i)){
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	//Checks if the user gave enough commands when running .exe file
	if (argc != 4){
		cerr << "ERROR: Not enough arguments given" << endl;
		return 1;
	}

	//Converting user's strings on command lines to variables for program use
	const string input_name = argv[1];
	const string output_name = argv[2];
	const string cmd = argv[3];

	//Variables declaration
	vector<int> scores;
	vector<Bowling> players;
	string str;
	string first;
	string last;
	string scores_str;
	string entire_output;
	int char_counter =0;

	//Open the input file and reads it
	ifstream input_file (input_name);
	if (!input_file){
		cerr << "ERROR: Unknown input file" << endl;
		return 1;
	} 

	//Open the output file and test if it is valid
	ofstream output_file(output_name);
	if (output_file.is_open()){
	} else {
		cerr << "ERROR: Unable to open output file" << endl;
		return 1;
	}

	//While loop that goes through the input file of players' names and scores, parse them and put them all into 
	// a profile object that stores those information
	while (input_file >> str) {

		//While parsing, if sees a string as a word, not a number, char_counter counts it and 
		//add the previous players' names and scores to a bowling class object. 
		if (!is_number(str)){
			char_counter += 1;
			if (char_counter >1){
				Bowling profile (first, last, entire_output);
				scores = profile.getScores(scores_str);
				profile.setScores(scores);
				players.push_back(profile);
				scores_str = "";
				scores.clear();
				char_counter -= 1;
			}
			first = str;
			first += ' ';
			input_file >> last;
		}
		else {
			scores_str += str + ' ';
		}
	}

	//Add the last player's info to be parsed into the bowling class object
	Bowling profile (first, last, entire_output);
	scores = profile.getScores(scores_str);
	profile.setScores(scores);
	players.push_back(profile);
	scores_str = "";
	scores.clear();

	//Sorts the vector filled with the bowling class players objects in order of their last name
	sort(players.begin(), players.end(), OrderName);

	int maxNameLen = 0;
	//For loop calculates the maximum length of a player's name for printing
	for (int i=0; i < int(players.size()); ++i){
		if ((int(players[i].getFirst().size()) + int(players[i].getLast().size())) > maxNameLen){
			maxNameLen = (int(players[i].getFirst().size()) + int(players[i].getLast().size()));
		}
	} 

	//Prints output upon custom command given by user
	//This chunk of code will print players' strikes and spares, in a leaderboard format
	if (cmd == "custom") {

		//For loop goes around the players vector, calculating the number of strikes and spares each player got
		for (int i = 0; i <int(players.size()); ++i){
			scores = players[i].Scores();
			int incr =2;
			int strikes =0;
			int spares = 0;

			//For loop going through vector of scores, determining whether each frame was a spare, strike or none
			for (int x=0; x < int(scores.size()); x += incr){
				if (scores[x] == 10){
					strikes += 1;
					incr = 1;
					continue;
				}
				else if ((scores[x] + scores[x+1]) < 10){
					incr =2;
					continue;
				}
				else if ((scores[x] + scores[x+1]) == 10) {
					incr =2;
					spares += 1;
					continue;
				}
			}
			//Add number of strikes and spares into the player class object
			players[i].setStrikes(strikes);
			players[i].setSpares(spares);
		}

		//Sort players based on number of strikes
		int simpl = (maxNameLen -3 )/2;
		int simpl1 = (maxNameLen -2 )/2;

		//File output the leaderboard of amount of strikes and spares
		output_file << string(simpl, ' ') << "STRIKES" << string(maxNameLen+4 -7 - simpl, ' ') << '\t' << string(simpl1, ' ') << 
		"SPARES" << string(maxNameLen+4 -6 - simpl1, ' ') << endl;
		output_file << string(maxNameLen + 4, '-') << '\t' << string(maxNameLen + 4, '-') << endl;
		for (unsigned int i=0; i < players.size(); ++i){

			//Sorts the players vector based on number of strikes, prints the i'th person in the vector
			sort(players.begin(), players.end(), moreStrikes);
			output_file << players[i].getFirst() << players[i].getLast() << 
			string(maxNameLen- int(players[i].getFirst().size()+players[i].getLast().size()), ' ') <<
			"  " << string(2-to_string(players[i].getStrikes()).size(),' ') << players[i].getStrikes() << '\t';

			//Sort players based on number of spares, prints the i'th person in the vector
			sort(players.begin(), players.end(), moreSpares);
			output_file << players[i].getFirst() << players[i].getLast() << 
			string(maxNameLen- int(players[i].getFirst().size()+players[i].getLast().size()), ' ') <<
			"  " << string(2-to_string(players[i].getSpares()).size(),' ') << players[i].getSpares() << endl;
		}
	}

	//Prints output upon standard command given by user
	if (cmd == "standard"){
		string box_tb = string(maxNameLen+66,'-');
		entire_output += box_tb + '\n';

		//For loop goes through the vector of players, each time printing the players' scores for the whole game
		for (int i=0; i< int(players.size()); ++i){
			players[i].setOutput(entire_output);
			players[i].printScoreChart(maxNameLen);
			entire_output = players[i].getOutput();
			entire_output += box_tb + '\n';
		}
		entire_output += '\n';

	//This prints out the second portion of standard command
		sort(players.begin(), players.end(), isLessThan);
		for (int i=0; i < int(players.size()); ++i){
			players[i].setOutput(entire_output);
			players[i].printFinal(maxNameLen);
			entire_output = players[i].getOutput();
		}
	}
	output_file << entire_output;
}
