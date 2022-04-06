#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "HashTable.h"
#include "kmer.h"

using namespace std;

int main(){

	// variable delcarations and set intial values
	string genome_file;
	int table_size = 100;
	float occupancy = 0.5;
	int kmerLen;
	string command;
	string entireGenome;
	
	// takes in command from input file
	while (cin >> command){
		if (command == "genome") {
			cin >> genome_file;
			ifstream genomeFile(genome_file);
			string genomeLine;
			//combine all the text in the genome file into one big string
			while (genomeFile >> genomeLine){
				entireGenome += genomeLine;
			}
		}
		else if (command == "table_size") cin >> table_size;
		else if (command == "occupancy") cin >> occupancy;
		else if (command == "kmer") cin >> kmerLen;
		else break;
	}
	
	//create the hash table
	HashTable hashTable(table_size);
	//hashTable.createEmptyTable();

	string kmer;
	float unique_keys =0;

	// Goes through the big string of genome sequence, while splitting them into k-mers each time and adding it
	// into the hash table
	for (unsigned int i=0; i<entireGenome.size(); ++i){
		string kmer = entireGenome.substr(i, kmerLen);
		vector<int> vect;
		vect.push_back(i);
		int kmer_size = kmer.size();
		if (kmer_size == kmerLen) hashTable.insert(kmer,vect);
		else continue;
		unique_keys++;
		//check for occupancy and rehash if neccesary
		float overload = unique_keys / hashTable.getSize();
		if (overload > occupancy) hashTable.rehash();
	}

	//variable delcarations for query search
	int mismatch;
	string query_sequence;
	cin >> mismatch >> query_sequence;

	//find the sequence that we find to search, and split it into a kmer of k-length
	string search_kmer = query_sequence.substr(0, kmerLen);

	//find the index of the kmer of the query sequence and locate it in the hash table
	int index = hashTable.hash(search_kmer);
	vector<Kmer> hTable = hashTable.getTable();
		
	cout << "Query: " << query_sequence << endl;

	// if the index we initially got does not have the kmer we're looking for, we will use
	// linear probe to find it
	bool done = false;
	while (!done) {
		if (hTable[index].getKmer() != search_kmer) {
			unsigned int i=1;
			bool done_ = false;
			while (i < hashTable.getSize() && !done_){
				index = (i + index) % hashTable.getSize();
				++i;
				if (hTable[index].getKmer() == search_kmer) break;
			}
			continue;
		}

		// when we have found the desired kmer in the table, we will now saerch for the correct one
		// with the correct starting point
		else {
			done = true;
			int matches_found = 0;
			vector<int> starting_points = hTable[index].getPositions();

			// goes through the vector of the starting points for that specific kmer
			for (unsigned int i= 0; i < starting_points.size(); ++i){
				int difference = 0;
				//create a string based on the starting point position, and check for mismatch
				string sample_DNA = entireGenome.substr(starting_points[i], query_sequence.size());
				for (unsigned int j=0; j < sample_DNA.size(); ++j){
					if (sample_DNA[j] != query_sequence[j]) difference++;
					if (difference > mismatch) break;
				}
				// if there are too much differences, that will not be included in the output
				if (difference > mismatch) continue;
				// if differences matches the constraints, we print its position and sequence out
				else if (difference <= mismatch && sample_DNA.size() == query_sequence.size()) {
					matches_found++;
					cout << starting_points[i] << ' ' << difference << ' ' << sample_DNA << endl;
				}
			}
			// output if there are no match
			if (matches_found == 0) cout << "No Match" << endl;
			break;
		}
	}

	while (cin >> command){
		if (command == "quit") break;
		
		if (command == "query"){
			cin >> mismatch >> query_sequence;
		}

		//find the sequence that we find to search, and split it into a kmer of k-length
		string search_kmer = query_sequence.substr(0, kmerLen);

		//find the index of the kmer of the query sequence and locate it in the hash table
		int index = hashTable.hash(search_kmer);
		vector<Kmer> hTable = hashTable.getTable();
			
		cout << "Query: " << query_sequence << endl;

		// if the index we initially got does not have the kmer we're looking for, we will use
		// linear probe to find it
		bool done = false;
		while (!done) {
			if (hTable[index].getKmer() != search_kmer) {
				unsigned int i=1;
				bool done_ = false;
				while (i < hashTable.getSize() && !done_){
					index = (i + index) % hashTable.getSize();
					++i;
					if (hTable[index].getKmer() == search_kmer) break;
				}
				continue;
			}

			// when we have found the desired kmer in the table, we will now saerch for the correct one
			// with the correct starting point
			else {
				done = true;
				int matches_found = 0;
				vector<int> starting_points = hTable[index].getPositions();

				// goes through the vector of the starting points for that specific kmer
				for (unsigned int i= 0; i < starting_points.size(); ++i){
					int difference = 0;
					//create a string based on the starting point position, and check for mismatch
					string sample_DNA = entireGenome.substr(starting_points[i], query_sequence.size());
					for (unsigned int j=0; j < sample_DNA.size(); ++j){
						if (sample_DNA[j] != query_sequence[j]) difference++;
						if (difference > mismatch) break;
					}
					// if there are too much differences, that will not be included in the output
					if (difference > mismatch) continue;
					// if differences matches the constraints, we print its position and sequence out
					else if (difference <= mismatch && sample_DNA.size() == query_sequence.size()) {
						matches_found++;
						cout << starting_points[i] << ' ' << difference << ' ' << sample_DNA << endl;
					}
				}
				// output if there are no match
				if (matches_found == 0) cout << "No Match" << endl;
				break;
			}
		}
	}

	return 0;
}