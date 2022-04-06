#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "HashTable.h"

//Hash Table constructor that creates the table
HashTable::HashTable(int size){
	this->tableSize = size;
	for (unsigned int i=0; i<this->tableSize; ++i){
		Kmer K("x");
		hashTable.push_back(K);
	}
}

// hash function returns a number for a given kmer, that number will be the index inside the hash table to be inserted
// credit to this website for showing me this hash function: http://www.isthe.com/chongo/tech/comp/fnv/

int HashTable::hash(const std::string& key)  {
	//the two numbers are found in the website which are both prime numbers to create a 16 bit number
	const long int offset_basis = 2166136261;
	const long int FNV_prime = 16777619;
    unsigned int h = offset_basis; // set the hash number as the offset_basis

    // goes through the kmer, each time multiplying hash with the FNV_prime number along with
    // xoring the ith index of the kmer
    for (unsigned int i=0; i<key.size(); ++i){
    	h = h*FNV_prime;
    	h = h ^ key[i];
    }
    //return h mod table size to ensure the hash is under the hash table size
    return h % this->tableSize;

}

// function inserts a given kmer, as well as its starting position into an appropriate location of the hash table
void HashTable::insert(std::string& kmer, std::vector<int>& pos){
	//first hash the string to get an index
	int index = hash(kmer);		
	//if the first index we get from hashing is available, we insert it
	if (hashTable[index].getKmer() == "x"){
		Kmer k(kmer, pos);
		hashTable[index] = k;
		return;
	}
	
	//linear probe to find an available slot to insert the kmer if that original index isn't available
	else {
		if (hashTable[index].getKmer() == kmer){
			//go through the insert vector and push back
			for (unsigned int i=0; i< pos.size(); ++i){
				hashTable[index].setPositions(pos[i]);
			}
			
			return;
		}
		unsigned int i= 1;
		bool done = false;
		//linear probing to find the next available slot
		while (!done && i < this->tableSize){
			index = (i + index) % this->tableSize;
			++i;
			//while using linear probe, if we find the kmer we want to insert, we will push_back the locations into the
			// existing starting locations in the hash table
			if (hashTable[index].getKmer() == kmer) {
				for (unsigned int j=0; j < pos.size(); ++j){
					hashTable[index].setPositions(pos[i]);
				}
				done = true;
				return;
			}
			// if we reach an index that is empty, we will simply add the kmer into that location
			else if ((hashTable[index].getKmer()) == "x") {
				Kmer k(kmer, pos);
				hashTable[index] = k;
				done = true;
				return;
			}	
		}
	}
}

// in the case we reach overload in our occupancy, we rehash the table in order to decrease the occupancy
void HashTable::rehash(){
	// set original size for later use
	unsigned int original_size = this->tableSize;
	// double the table size and create a new temporary table
	this->tableSize = this->tableSize* 2;
	std::vector<Kmer> tmpTable;

	// intialize the temporary table with double the original size
	for (unsigned int i=0; i<tableSize; ++i){
		Kmer k("x");
		tmpTable.push_back(k);
	}

	//goes through the original table, each time if the index has a kmer, we hash it to the new temporary hash table
	for (unsigned int i= 0; i<original_size; ++i){
		if (hashTable[i].getKmer() != "x"){
			int index = hash(hashTable[i].getKmer());
			//if collision happens when transferring values to the new table, we use linear probing
			if (tmpTable[index].getKmer() != "x" && tmpTable[index].getKmer() != hashTable[i].getKmer()){
				bool done = false;
				//linear probe until we find an available slot to insert
				for (unsigned int j=0; j<this->tableSize && !done; ++j){
					index = (j + index) % this->tableSize;
					if (tmpTable[index].getKmer() == hashTable[i].getKmer()) break;
				}
			}
			// insert the kmer to the new temp hash table with the appropriate index
			tmpTable[index] = hashTable[i];
		}
	}

	//clear the original hash table and transfer all the contents from the temporary one to this one
	this->hashTable.clear();
	for (unsigned int i=0; i < tmpTable.size(); ++i){
		hashTable.push_back(tmpTable[i]);
	}
}

// function is for debugging, print the content of the hash table (not used for homework assignment purposes)
void HashTable::print(){
	for (unsigned int i=0; i<tableSize; ++i){
		std::cout << hashTable[i].getKmer() << ' ';
		for (unsigned int j=0; j< (hashTable[i].getPositions()).size(); ++j){
			std::cout << (hashTable[i].getPositions())[j] << ' ';
		}
		std::cout << std::endl;
	}
}