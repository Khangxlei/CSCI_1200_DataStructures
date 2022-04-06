#ifndef hash_table
#define hash_table

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "kmer.h"

using namespace std;


class HashTable {
public:
	HashTable(int size) : tableSize(size) {}

	int getSize(){ return tableSize; }
	vector<kmer> getTable() { return hashTable; }

	int hash(const string& key) ;
	void insert(pair<string, vector<int>>& kmer);
	void createEmptyTable();
	void rehash();

	void print();


private:
	//vector<pair<string, vector<int>>> hashTable;
	vector<kmer> hashTable;
	string entireGenome;
	int tableSize;

};

void HashTable::print(){
	for (unsigned int i=0; i<tableSize; ++i){
		cout << hashTable[i].first << ' ';
		for (unsigned int j=0; j< (hashTable[i].second).size(); ++j){
			cout << (hashTable[i].second)[j] << ' ';
		}
		cout << endl;
	}
}

// http://isthe.com/chongo/tech/comp/fnv/#FNV-param
int HashTable::hash(const string& key)  {
	const unsigned int offset_basis = 144066263297769815596495629667062367629;
	const unsigned int FNV_prime = 309485009821345068724781371;
    unsigned int h = offset_basis;
    for (unsigned int i=0; i<key.size(); ++i){
    	h = h*FNV_prime;
    	h = h ^ key[i];
    }
    return h % this->tableSize;

}

void HashTable::insert(pair<string, vector<int>>& kmer){
	int index = hash(kmer.first);		
	if (hashTable[index].getString() == "X"){
		kmer k(kmer.first, kmer.second)''
		hashTable[index] = k;
		return;
	}

	
	else {
		if (hashTable[index].first == kmer.first){
			//go through the int vector and push back
			for (unsigned int i=0; i< (kmer.second).size(); ++i){
				(hashTable[index].second).push_back(kmer.second[i]);
			}
			
			return;
		}
		unsigned int i= 1;
		bool done = false;
		//linear probing
		while (!done && i < this->tableSize){
			index = (i + index) % this->tableSize;
			++i;
			if (hashTable[index].first == kmer.first) {
				for (unsigned int j=0; j < (kmer.second).size(); ++j){
					(hashTable[index].second).push_back(kmer.second[j]);
				}
				done = true;
				return;
			}
			else if ((hashTable[index].first) == "X") {
				hashTable[index] = kmer;
				done = true;
				return;
			}	
		}
	}
}


void HashTable::rehash(){
	int original_size = this->tableSize;
	this->tableSize = this->tableSize* 2;
	vector<pair<string, vector<int>>> tmpTable;

	for (unsigned int i=0; i<tableSize; ++i){
		vector<int> integer;
		integer.push_back(-1);
		tmpTable.push_back(make_pair("X", integer));
	}

	for (unsigned int i= 0; i<original_size; ++i){
		if (hashTable[i].first != "X"){
			int index = hash(hashTable[i].first);
			if (tmpTable[index].first != "X" && tmpTable[index].first != hashTable[i].first){
				bool done = false;
				for (unsigned int j=0; j<this->tableSize && !done; ++j){
					index = (j + index) % this->tableSize;
					if (tmpTable[index].first == hashTable[i].first) break;
				}
				//index = (1 + index) % this->tableSize;
			}
			tmpTable[index] = hashTable[i];
		}
	}
	this->hashTable.clear();
	this->hashTable = tmpTable;
}

void HashTable::createEmptyTable(){
	for (unsigned int i=0; i<this->tableSize; ++i){
		//ensure the value we add into the value is not valid 
		vector<int> vect;
		vect.push_back(-1);
		kmer K("X", vect);
		hashTable.push_back(K);
/*
		vector<int> integer;
		integer.push_back(-1);
		hashTable.push_back(make_pair("X", integer));*/
	}
}




#endif