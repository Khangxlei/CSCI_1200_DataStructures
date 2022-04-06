#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "HashTable.h"

using namespace std;

int main(){

	string genome_file;
	int table_size = 100;
	float occupancy = 0.5;
	int kmerLen;
	string command;
	ifstream file("input_small.txt");
	if (file.good()){
		while (file >> command){
			if (command == "genome") file >> genome_file;
			else if (command == "table_size") file >> table_size;
			else if (command == "occupancy") file >> occupancy;
			else if (command == "kmer") file >> kmerLen;
			else break;
		}
	}

	ifstream genomeFile(genome_file);
	string entireGenome;
	if (genomeFile.good()){
		string genomeLine;
		while (genomeFile >> genomeLine){
			entireGenome += genomeLine;
		}
	}

	HashTable hashTable(table_size);
	hashTable.createEmptyTable();


	
	string kmer;
	float unique_keys =0;
	
	for (unsigned int i=0; i<entireGenome.size(); ++i){
		if (kmer.size() < kmerLen) kmer.push_back(entireGenome[i]);
		if (kmer.size() == kmerLen){
			vector<int> vect1;
			vect1.push_back(i - (kmerLen-1));
			pair<string, vector<int>> tmpPair = make_pair(kmer, vect1);
			hashTable.insert(tmpPair);
			unique_keys++;
			float overload = unique_keys / hashTable.getSize();
			if (overload > occupancy) hashTable.rehash();
			kmer.erase(kmer.begin());
		}
	}
	//hashTable.print();


	int mismatch;
	string query_sequence;
	file >> mismatch >> query_sequence;

	string search_kmer = query_sequence.substr(0, kmerLen);

		int index = hashTable.hash(search_kmer);
		vector<pair<string, vector<int>>> hTable = hashTable.getTable();
		
		int count = 0;
		cout << "Query: " << query_sequence << endl;

		bool done = false;
		while (!done) {
			if (hTable[index].first != search_kmer) {
				//index = (1 + index) % hashTable.getSize(); 
				unsigned int i=1;
				bool done = false;
				while (i < hashTable.getSize() && !done){
					index = (i + index) % hashTable.getSize();
					++i;
					if (hTable[index].first == search_kmer) break;
				}
				continue;
			}

			else {
				done = true;
				
				int matches_found = 0;
				vector<int> starting_points = hTable[index].second;
				for (unsigned int i= 0; i < starting_points.size(); ++i){
					int difference = 0;
					string sample_DNA;
					bool loop_done = false;
					for (unsigned int j = starting_points[i]; !loop_done ;++j){
						if (entireGenome[j] != query_sequence[sample_DNA.size()]) difference++;
						if (difference > mismatch) {
							sample_DNA = "";
							loop_done = true;
							continue;
						}
						sample_DNA += entireGenome[j];
						if (sample_DNA.size() == query_sequence.size()) loop_done = true;
					}
					if (sample_DNA.size() != 0 && difference <= mismatch){
						matches_found++;
						cout << starting_points[i] << ' ' << difference << ' ' << sample_DNA << endl;
					}
				}
				if (matches_found == 0) cout << "No Match" << endl;
				break;
			}
		}

	while (file >> command){
		if (command == "quit") break;
		
		if (command == "query"){
			file >> mismatch >> query_sequence;
		}
			string search_kmer = query_sequence.substr(0, kmerLen);

		int index = hashTable.hash(search_kmer);
		vector<pair<string, vector<int>>> hTable = hashTable.getTable();
		
		int count = 0;
		cout << "Query: " << query_sequence << endl;

		bool done = false;
		while (!done) {
			if (hTable[index].first != search_kmer) {
				//index = (1 + index) % hashTable.getSize(); 
				unsigned int i=1;
				bool done = false;
				while (i < hashTable.getSize() && !done){
					index = (i + index) % hashTable.getSize();
					++i;
					if (hTable[index].first == search_kmer) break;
				}
				continue;
			}

			else {
				done = true;
				
				int matches_found = 0;
				vector<int> starting_points = hTable[index].second;
				for (unsigned int i= 0; i < starting_points.size(); ++i){
					int difference = 0;
					string sample_DNA;
					bool loop_done = false;
					for (unsigned int j = starting_points[i]; !loop_done ;++j){
						if (entireGenome[j] != query_sequence[sample_DNA.size()]) difference++;
						if (difference > mismatch) {
							sample_DNA = "";
							done = true;
							loop_done = true;
							continue;
						}
						sample_DNA += entireGenome[j];
						if (sample_DNA.size() == query_sequence.size()) loop_done = true;
					}
					if (sample_DNA.size() != 0 && difference <= mismatch){
						matches_found++;
						cout << starting_points[i] << ' ' << difference << ' ' << sample_DNA << endl;
					}
				}
				if (matches_found == 0) cout << "No Match" << endl;
				break;
			}
		}

	}

	return 0;
}