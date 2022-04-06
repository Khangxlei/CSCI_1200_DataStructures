#ifndef kmer_h
#define kmer_h

#include <string>
#include <iostream>
#include <vector>

class Kmer {
public:
	//Constructors
	Kmer(const std::string& str, const std::vector<int>& sp) : kmer(str), starting_positions(sp) {}
	Kmer (const std::string& str="x") : kmer(str), starting_positions(std::vector<int>()) {}
	
	//Accessors
	std::string getKmer() { return kmer; }
	std::vector<int> getPositions() { return starting_positions; }

	//Modifiers
	void setPositions(int x) { starting_positions.push_back(x); }

private:
	//REPRESENTATION
	std::string kmer;
	std::vector<int> starting_positions;
};


#endif