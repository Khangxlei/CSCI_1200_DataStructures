/*
This program will wrap a given input text inside a printed box. The box size will be determined by the user, and they
will be able to choose whether to justify the text left, right, or full. 

Example execution:
./hw01.exe example.txt output.txt 16 flush_left

**inside output.txt file**
--------------------
| This is an       |
| example of text  |
| justification.   |
--------------------

02.04.2021
Khang Le
Data Structures

*/

#include <iostream>   
#include <fstream>
#include <sstream> 
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

//Function find any words that exceeds the given width, and split them however many times it needs to with a hiphen
vector<string> organizing(vector<string> vect0, int width){ 
	vector<string> vect;
	for (string x: vect0){
		if (int(x.size()) <= width){
				vect.push_back(x);
		}
		if (int(x.size()) > width){
			int line_amt = x.size() / width +1;
			//for loop splits the word as much time needed to fit into the box
			for (int y=0; y < line_amt; ++y){
				string str = "";
				if(y+1 == line_amt){
					str = x.substr(y*(width-1));
					vect.push_back(str);
					continue;
				}
				str = x.substr(y*(width-1), width-1);
				str += '-';
				vect.push_back(str);
			}

		}
	}
	return vect;
}

//Function operates when command flush_left is called, it takes in all arguments and print out the text left justified into the file
void flush_left(vector<string>& vect, string output_name, int width){ 
	//Variables declaration
	const std::string box_width(width+4,'-');
	std::string line;
	std::string output_line;
	ofstream output_file(output_name);
	output_file << box_width << endl;

	//For loop goes through the vector of words and prints them out based on the width
	//Each loop goes through 1 out of 4 if statements, deciding whether to continue adding more words onto the line, or print it out
	for (string x: vect){
		if (int ((line+x).size()) == width){
			output_line = line + x;
			if (output_line[output_line.size()-1] == ' '){
				output_line.pop_back();
			}
			output_file << "| " << output_line << std::string(int(width - output_line.size()), ' ') << " |" << endl;
			line = "";
		}
		else if ((int(line.size()) < width) && (int((line + x).size()) == width)){
			output_line = line + x;
			if (output_line[output_line.size()-1] == ' '){
				output_line.pop_back();
			}
			output_file << "| " << output_line << std::string(int(width - output_line.size()), ' ') << " |" << endl;
			line = "";
		}
		else if ((int(line.size()) <= width) && int((line +x).size()) > width ){
			output_line = line;
			if (output_line[output_line.size()-1] == ' '){
				output_line.pop_back();
			}
			output_file << "| " << output_line << std::string(int(width - output_line.size()), ' ') << " |" << endl;
			if (x[x.size()-1] == '-'){
				line = x;
				continue;
			}
			line = x + " ";
		}
		else if ((int(line.size()) < width) && (int((line + x).size()) < width)){
			line += x + " ";
		}
	}

	output_file << "| " << line << std::string(width - line.size(), ' ')  << " |" << endl;
	output_file << box_width << std::endl;
}

//Does the same thing as function flush_left, but instead of outputting it with spaces to the right, does the opposite with spaces to the left
void flush_right(vector<string>& vect, string output_name, int width){
	//Variables declaration
	const std::string box_width(width+4,'-');
	string line;
	string output_line;
	ofstream output_file(output_name);
	output_file << box_width << endl;

	//For loop goes through the vector of words and prints them out based on the width
	//Each loop goes through 1 out of 4 if statements, deciding whether to continue adding more words onto the line, or print it out
	for (string x: vect){
		if (int ((line+x).size()) == width){
			output_line = line + x;
			int lspace_number;
			lspace_number = width - output_line.size();
			output_file <<  "| " << std::string(lspace_number, ' ') << output_line << " |" << endl;
			line = "";
		}
		else if ((int(line.size()) < width) && (int((line + x).size()) == width)){
			output_line = line + x;
			if (output_line[output_line.size()-1] == ' '){
				output_line.pop_back();
			}
			int lspace_number;
			lspace_number = width - output_line.size(); 
			output_file <<  "| " << std::string(lspace_number, ' ') << output_line << " |" << endl;
			line = "";
		}
		else if ((int(line.size()) <= width) && int((line +x).size()) > width ){
			output_line = line;
			if (output_line[output_line.size()-1] == ' '){
				output_line.pop_back();
			}
			int lspace_number;
			lspace_number = width - output_line.size();
			output_file <<  "| " << std::string(lspace_number, ' ') << output_line << " |" << endl;
			if (x[x.size()-1] == '-'){
				line = x;
				continue;
			}
			line = x + " ";
		}
		else if ((int(line.size()) < width) && (int((line + x).size()) < width)){
			line += x + " ";
		}
	}
	if (output_line[output_line.size()-1] == ' '){
		output_line.pop_back();
	}
	if (line[line.size()-1] == ' '){
		line.pop_back();
	}
	output_file << "|" << std::string(width - line.size() +1, ' ') << line  << " |" << endl;
	output_file << box_width << std::endl;
}

//Function returns a vector of words containing equally distributed spaces ONLY when there is less extra spaces than words
vector<string> distr_space(int space_number, vector<string> line_words){
	//Since there are less extra spaces than number of words on the line, it does a for loop around a vector of words, 
	//assigning a single space to each word until it reaches the number of extra spaces
	for (int i=0; i < space_number; ++i){
	std::string addtn_space= " ";
	line_words[i] += addtn_space;
	}
	return line_words;
}

//Function returns a vector of words containing equally distributed spaces ONLY when there is more extra spaces than words
vector<string> equally_distr_space (int max_addtn_space, int space_number, int words_amt, vector<string>& line_words){
	int spaces_counter=0;

	//Goes through every single word on the line, each time keeping track of how much spaces it has concatenated to the words.
	//By keeping track, it will find the correct number of spaces to assign to each word that is equally distributed.
	for (int i=1; (i*(max_addtn_space) <= space_number) && (i-1 < words_amt); ++i){
		string addtn_space(max_addtn_space,' ');
		line_words[i-1] += addtn_space;
		spaces_counter += max_addtn_space;

 		//As loop goes through the words on the line, it checks the next word and if the number of spaces 
 		//exceed the actual number of extra spaces available, does a while loop to find the next appropriate number of 
 		//spaces to concatenate.
		if ((i+1) * max_addtn_space > space_number) {
			bool result = true;
			//While loop finds the next number of spaces to assign to the next word 
			while (result){
				if (((max_addtn_space -1)*(i+1)> space_number) or ((max_addtn_space-1)+ spaces_counter >= space_number)) {
					max_addtn_space -= 1;
					result= true;
				}
				else {
					result= false;
				}
			}
		}
	}
	return line_words;
} 

//Convert a string of words to a vector of those words
vector<string> str_to_vect (string line){
	std::stringstream sstream(line);
	std::istream_iterator<std::string> total(sstream);
	std::istream_iterator<std::string> words;
	std::vector<std::string> line_words(total, words);
	return line_words;
}
int char_to_int (char* Char) {
	stringstream conversion (Char);
	stringstream conversion1 (Char);
	int width;
	float fwidth;
	conversion >> width;
	conversion1 >> fwidth;
	if (fwidth != width) {
		cerr << "ERROR: Entered width is not valid" << endl;
		exit(3);
	}
	else {
		return width;
	}
}

//Main program output
int main(int argc, char* argv[]){
	if (argc != 5){
		cerr << "ERROR: Not enough arguments given" << endl;
		exit(3);
	}
	//Takes in argument line given when executing the file. Assign each arguments to a variable for program use.
	const string input_name = argv[1];
	const string output_name = argv[2];
	const int width = char_to_int (argv[3]);
	const string format = argv[4];

	//Create string variables to use to print the box
	const string box_width( width+ 4,'-');
	string output_line;

	if ((format != "flush_left") and (format != "flush_right") and (format != "full_justify")){
		cerr << "ERROR: Command is not valid" << std::endl;
		exit(3);
	}

	ifstream input_file(input_name);
	string output;
	string input_text;
	if (input_file.is_open()){
		while (getline(input_file, output)){
				input_text = input_text + output + '\n';
		}
		input_file.close();
	}

	else {
		cerr << "ERROR: Unable to open input file" << endl;
		exit(3);
	}

	//Split the sentence(s) in the input file into a vector
	std::stringstream sstream(input_text);
	std::istream_iterator<std::string> total(sstream);
	std::istream_iterator<std::string> words;
	std::vector<std::string> vect0(total, words);
	std::vector<std::string> vect;

	ofstream output_file(output_name);
	if (output_file.is_open()){
	} else {
		cerr << "ERROR: Unable to open output file" << endl;
		exit(3);
	}

	//Call flush_left function if user wants to left justify text
	if (format == "flush_left"){
		vect = organizing(vect0, width);
		flush_left(vect, output_name, width);
	}

	//Call flush_right function if user wants to right justify text
	if (format == "flush_right"){
		vect = organizing(vect0, width);
		flush_right(vect, output_name, width);

	}

	if (format == "full_justify"){
		output_file << box_width << endl;
		string word;
		string line;
		vect = organizing(vect0, width);

		//For loop goes through the vector of words and prints them out based on the width
		//Each loop goes through 1 out of 4 if statements, deciding whether to continue adding more words onto the line, 
		//or print it out
		for (string x: vect) {

			if (int ((line+x).size()) == width){

				output_line = line + x;
				vector<string> line_words = str_to_vect(output_line);
				int space_number = width - (output_line.size());
				int words_amt = line_words.size();
				int max_addtn_space;

				if (words_amt > 1){
					max_addtn_space = round(double (space_number / (words_amt -1))) ;
				}
				if (words_amt <= 1) {
					max_addtn_space = 0;
				}
				if (space_number < words_amt){
					line_words = distr_space(space_number, line_words);
				}

				if (space_number >= words_amt){
					line_words = equally_distr_space(max_addtn_space, space_number, words_amt, line_words);
				}
				//Convert the vector of words ready to be output into a string
				output_line = "";
				for (string i: line_words){
					output_line += i +' ';
				}
				if (output_line[output_line.size()-1] == ' '){
					output_line.pop_back();
				}
				output_file << "| " << output_line << " |" << endl;
				line = "";
				continue;
			}

			if ((int(line.size()) < width) && (int((line + x).size()) == width)){
				output_line = line + x;
				if (output_line[output_line.size()-1] == ' '){
					output_line.pop_back();
				}

				vector<string> line_words = str_to_vect(output_line);
				int space_number = width - (output_line.size());
				int words_amt = line_words.size();
				int max_addtn_space;

				if (words_amt > 1){
					max_addtn_space = round(double (space_number / (words_amt -1))) ;
				}
				if (words_amt <= 1) {
					max_addtn_space = 0;
				}
				if (space_number < words_amt){
					line_words = distr_space(space_number, line_words);
				}

				if (space_number >= words_amt){
					line_words = equally_distr_space(max_addtn_space, space_number, words_amt, line_words);
				}

				output_line = "";
				for (string i: line_words){
					output_line += i +' ';
				}
				if (output_line[output_line.size()-1] == ' '){
					output_line.pop_back();
				}
				output_file << "| " << output_line << " |" << endl;
				line = "";
				continue;
			}

			if ((int(line.size()) <= width) && int((line +x).size()) > width ){
				output_line = line;
				if (output_line[output_line.size()-1] == ' '){
					output_line.pop_back();
				}

				vector<string> line_words = str_to_vect(output_line);
				int space_number = width - (output_line.size());
				int words_amt = line_words.size();
				int max_addtn_space;

				if (words_amt > 1){
					max_addtn_space = round(double (space_number / (words_amt -1))) ;
				}
				if (words_amt < 1) {
					max_addtn_space = 0;
				}
				if (words_amt == 1){
					output_line = "";
					if (line_words[0][-1] == ' '){
				 		line_words[0].pop_back();
					}
					output_file << "| " << line_words[0] << std::string(width - (line_words[0].size()),' ') << " |" << endl;
					if (x[x.size()-1] == '-'){
						line = x;
						continue;
					}
					else {
						line = x + " ";
						continue;
					}
				}
				if (space_number < words_amt){
					line_words = distr_space(space_number, line_words);
				}

				if (space_number >= words_amt){
					line_words = equally_distr_space(max_addtn_space, space_number, words_amt, line_words);
				}
				output_line = "";
				for (string i: line_words){
					output_line += i +' ';
				}
				if (output_line[output_line.size()-1] == ' '){
					output_line.pop_back();
				}
				output_file << "| " << output_line << " |" << endl;
				if (x[x.size()-1] == '-'){
					line = x;
					continue;
				}

				line = x + " ";
				continue;
			}

			if ((int(line.size()) < width) && (int((line + x).size()) < width)){
				line += x + " ";
				continue;
			}
		}

		//Printing last line as left justified regardless 
		output_file << "| " << line << std::string(width - line.size(), ' ')  << " |" << endl;
		output_file << box_width << std::endl;
	}
}