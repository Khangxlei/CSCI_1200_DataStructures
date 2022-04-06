#include <iostream>

using namespace std;

template <class T> class JaggedArray {
public:
	//Typedef
	typedef unsigned int size_type;

	JaggedArray(size_type a) { this->create(a); }
	size_type numBins(){ return num_bins; }
	size_type numElements(){return num_elements; }
	size_type* numElementsInBin() {return counts; }
	void copy(const JaggedArray<T>& ja);
	void print();
	void addElement(const size_type& ind, const T& elmt );

private:
	void create(size_type a);

	size_type num_bins;
	size_type *counts;
	size_type num_elements;
	T* unpacked_values[];

};

//Creates the data structure to hold the information of elements
template <class T> void JaggedArray<T>::create(size_type a){
	num_bins = a;
	num_elements = 0;
	counts = new size_type[num_bins];
	//Initializing all index of array to 0
	for (size_type i =0; i< num_bins; ++i){
		*(counts + i) = 0;
	}

}

template <class T> void JaggedArray<T>::print(){
	cout << numBins() << " " << numElements() << endl;
	cout << *(counts+1) << endl;

}

//Function add a given data and index into our data structures
template <class T> void JaggedArray<T>::addElement(const size_type& ind, const T& elmt ){
	//Editing the counts array
	*(counts + ind) += 1;
	//Editing the unpacked_values array
	unpacked_values[ind][0] = elmt;
}