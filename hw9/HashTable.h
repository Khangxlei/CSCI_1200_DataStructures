#ifndef hash_table
#define hash_table

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "kmer.h"

class HashTable {
public:
	//Constructor and Destructor
	HashTable(int size);
	~HashTable() { destroy_table(); }

	//Accessors
	unsigned int getSize(){ return tableSize; }
	std::vector<Kmer> getTable() { return hashTable; }

	//Member functions
	int hash(const std::string& key) ;
	void insert(std::string& kmer, std::vector<int>& pos);
	void rehash();

	//Print
	void print();


private:
	//REPRESENTATION
	std::vector<Kmer> hashTable;
	std::string entireGenome;
	unsigned int tableSize;

	//Private helper function
	void destroy_table(){
		hashTable.clear();
		entireGenome = "";
	}

};

#endif