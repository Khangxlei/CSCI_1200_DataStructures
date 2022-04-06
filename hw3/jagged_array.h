/*  
This is a Jagged Array template class header file. The goal of this file is to create
a template class named JaggedArray, that creates several arrays holding different type (given by user) of elements.
The class will allow the main program to add/remove elements, as well as access other class information.

Sample execution:
JaggedArray<char> ja(4);

ja.addElement(1,'a');
ja.addElement(2,'b');
ja.addElement(3,'c');
ja.print()

Code output:
  num_bins:  4
  num_elements:   3
  counts:  0 1 1 1
  values:    a b c 

Khang Le
DS CSCI 1200
02/26/2021
*/

#include <iostream>

using namespace std;

template <class T> class JaggedArray {
public:
    //Typedef
    typedef unsigned int size_type;

    //Constructors, Assignment Operators and Destructors
    JaggedArray(const size_type& a) { this->create(a); } //Constructor with int argument
    JaggedArray() {this-> create(); } //Default constructor
    JaggedArray(JaggedArray& ja) {this-> copy(ja); } //Copy constructor
    void operator=(JaggedArray<T>& v){this->copy(v);} //Assignment operator
    ~JaggedArray(); //Destructor

    //Accessors
    T& getElement(size_type bin, size_type position);
    size_type numBins(){ return num_bins; }
    size_type numElements(){return num_elements; }
    unsigned int numElementsInBin(size_type bin);
    bool isPacked() const {return counts == NULL && unpacked_values==NULL; }

    //Modifiers
    void removeElement(size_type bin, size_type position);
    void print();
    void addElement(const size_type& ind, const T& elmt );
    void clear();

    //Changing structure of data
    void pack();
    void unpack();
    

private:
    //Private member functions
    void copy(JaggedArray<T>& ja);
    void create(size_type a);
    void create();

    //Private member varables
    size_type num_bins;
    size_type *counts;
    size_type num_elements;
    T** unpacked_values;
    size_type* offsets;
    T* packed_values;
};

//Creates the appropriate data structure for each member variables to hold the information of elements
template <class T> void JaggedArray<T>::create(size_type a){
    //Initializing variables
    num_bins = a;
    counts = new size_type[num_bins];
    num_elements = 0;
    unpacked_values = new T*[num_bins];
    offsets = NULL;
    packed_values = NULL;

    //Initializing indexes of all array types to 0
    for (size_type i =0; i< num_bins; ++i){
        *(counts + i) = 0;
        unpacked_values[i] = new T[1];
    }
}

//Same as create function above, but sets everything to null since no arguments are given
template <class T> void JaggedArray<T>::create(){
    //Initializing variables
    num_bins = NULL;
    counts = NULL;
    num_elements = NULL;
    unpacked_values = NULL;
    offsets = NULL;
    packed_values = NULL;
}

//Function copies a given JaggedArray object to the current JaggedArray object with identical values
template <class T> void JaggedArray<T>::copy(JaggedArray<T>& ja){
    this-> num_bins = ja.numBins();
    this-> num_elements = ja.numElements();

    if (ja.isPacked() == false){ //If the JaggedArray is unpacked
        offsets = NULL;
        packed_values = NULL;

        //Assigning count values from copy JaggedArray object to the new one
        this-> counts = new size_type [num_bins];
        for (size_type i=0; i<num_bins; ++i){
            *(counts+i) = ja.counts[i];
        }

        //Creating the unpacked_values array
        unpacked_values = NULL;
        unpacked_values = new T* [num_bins];

        //For loop goes through the pointer arrays of unpacked_values,
        //it then creates the array (size of how much elements are in the bin)
        //that those array points to, and assign the values to the this current one
        for (size_type i=0; i<num_bins; ++i){
            unpacked_values[i] = new T [numElementsInBin(i)];
            for (size_type x=0; x<numElementsInBin(i); ++x){
                unpacked_values[i][x] = ja.getElement(i,x);
            }
        }
    }
    else { //If the JaggedArray is packed
        unpacked_values = NULL;
        counts = NULL;
        offsets = new size_type[num_bins];
        packed_values = new T[num_elements];

        //Transfers all values in offsets to this one
        for (size_type i= 0; i<num_bins; ++i){
            *(offsets+i) = ja.offsets[i];
        }

        //Transfers all values in packed_values into this one
        for (size_type i=0; i<num_elements; ++i){
            *(packed_values+i) = ja.packed_values[i];
        }
    }
}

//This function unpacks the JaggedArray object, meaning turning it from packed to unpacked
template <class T> void JaggedArray<T>::unpack(){
    if (this-> isPacked() == false) { //Error checking
        cerr << "Jagged Array is currently unpacked" << endl;
        exit (1);
    }
    //Creates necessary arrays to hold values for packed version
    unpacked_values = new T*[num_bins];
    counts = new size_type [num_bins];

    //For loop assigning appropriate values to the counts array
    for (size_type i =0; i<num_bins; ++i){
        if (num_bins -1 == i){ //Check to see if the index on counts array is the last one, since the value for that is calculated different
            counts[i] = num_elements - offsets[i];
            continue;
        }
        *(counts+i) = offsets[i+1] - offsets[i];
    }

    //For loop creating a pointer of arrays within unpacked_values, and does another for loop assigning
    //values within the arrays that are pointed to
    for(size_type i=0;i<num_bins; ++i){
        unpacked_values[i]= new T[*(counts+i)];
        for(size_type k=0; k<counts[i]; ++k){
            unpacked_values[i][k]=packed_values[offsets[i]+k];
        }
    }
    //Free memory
    delete[] offsets;
    delete[] packed_values;
    offsets = NULL;
    packed_values = NULL;
}

//Function packs a JaggedArray object, turning it from unpack to pack
template <class T> void JaggedArray<T>::pack(){
    if (this-> isPacked() == true){ //Error checking
        cerr << "Jagged Array is currently packed" << endl;
        exit(1);
    }

    //Create offsets array and assign the first value to 0
    offsets = new size_type [num_bins];
    offsets[0]= 0;

    //Going through offsets array and assign it values by using both the counts and offsets array
    for (size_type i=1; i<num_bins; ++i){
        offsets[i] = counts[i-1] + offsets[i-1];
    }

    //Copying values from unpacked_values to a single array of packed_values
    packed_values = new T [num_elements];
    int pv_index = 0;
    for (size_type i=0; i<num_bins; ++i){
        for (size_type k=0; k<*(counts+i); ++k){ //For loop looping the inside array of unpacked_values
            packed_values[pv_index] = unpacked_values[i][k];
            pv_index +=1;
        }
    }
    //Free memory
    delete [] counts;
    counts = NULL;

    //Has to free the array of single pointers first before freeing the array of double pointers
    for (size_type i=0; i<num_bins; ++i){
        delete [] unpacked_values[i];
    }
    delete[] unpacked_values;
    unpacked_values = NULL;
}

//Function prints all the information in this class based on the required output of this assignment
template <class T>  void JaggedArray<T>::print() {
    if (this-> isPacked() == true) { //Printing chart if jagged array's packed
        cout << "  num_bins:  "<< num_bins << endl;
        cout << "  num_elements:  " << num_elements << endl;
        cout << "  offsets: ";
        //Printing values in offsets array
        for(size_type index=0; index<num_bins; index++){
            cout << offsets[index] << ' ';
        }
        cout << "\n   values:  ";

        //Printing values in packed_values array
        for(size_type i=0;i<num_elements;i++){
            cout << packed_values[i] << ' ';
        }
    cout << endl;
    cout << endl;
    }

    else { //Printing chart if the jagged array is unpacked
        cout << "  num_bins:  "<< num_bins << endl;
        cout << "  num_elements:  "<< num_elements << endl;
        cout << "  counts:  ";
        for(size_type i=0; i<num_bins; i++) {
                cout << *(counts+i) <<' ';
        }
        cout << endl;
        cout << "  values:  ";

        //Calculate max number of elements inside a single bin, this max_elements variable will be used
        //to print elements based on the assignment's format
        size_type max_elements = 0;
        for (size_type i =0; i<num_bins; ++i){
            if (*(counts+i) > max_elements){
                max_elements = *(counts+i);
            }
        }

        //For loop loops max_elements of time to print values like output
        size_type line_no = 1;
        for (size_type i=0; i < max_elements; ++i){

            //For loop looping the number of bins, each time printing the index corresponding
            //to the line number
            for (size_type j=0; j<num_bins; ++j){

                //If there are no elements in bin, prints out space to skip over it
                if (numElementsInBin(j)==0){
                    cout << "  ";
                    continue;
                }
                //If the bin has no elements to be printed on the line number,
                //it simply prints a blank space and continues the for loop
                if (numElementsInBin(j) < line_no){
                    cout << "  ";
                    continue;
                }
                cout << unpacked_values[j][line_no-1] << ' ';
            }
            line_no += 1;
            cout << endl;
            if (i == (max_elements-1)){
                break;
            }
            cout << "           ";
        }
            cout << endl;
    }

}

//Function clears every elements in the JaggedArray object, not deleting it but makes the values to NULL
template <class T>  void JaggedArray<T>::clear(){
    if (this->isPacked() == true){ //Error checking
        cerr << "Cannot make edits to a packed jagged array" << endl;
        exit(1);
    }
    for (size_type i =0; i<num_bins; ++i){
        *(counts+i) =0; //Can't delete the array, we set the values to zero
        delete[] unpacked_values[i]; //Delete all the elements in the unpacked values array and set it to null
        unpacked_values[i] = NULL;
    }
    num_elements = 0;
}

//Function returns the number of elements in a given bin, whether the object is currently in packed or unpacked mode
template <class T> unsigned int JaggedArray<T>::numElementsInBin(size_type bin) {
    if(bin <0 || bin > num_bins -1 ){
        cerr << "Invalid bin input" << endl;
        exit(1);
    }
    if (this-> isPacked() == true){
        if (bin +1 == num_bins){
            return num_elements - offsets[bin];
        }
        else {
            return offsets[bin+1] - offsets[bin];
        }
    }
    else {
        return *(counts+bin);
    }
}

//Function add a given data and index into our data structures
template <class T> void JaggedArray<T>::addElement(const size_type& ind, const T& elmt ){
    if (this ->isPacked() == true || ind > num_bins || ind < 0){
        cerr << "Jagged Array is currently in packed mode" << endl;
        exit(1);
    }

    for (size_type i =0; i<num_bins; ++i){
        if (i == ind){ //If iterator reaches the index given my function argument, adds the element into the unpacked_array
            T *tempArr = new T [numElementsInBin(i)+1];
            for (size_type k =0; k < *(counts+i); ++k){
                tempArr[k] = unpacked_values[i][k];
            }
            delete[] unpacked_values[i]; //Free the exising array
            unpacked_values[i] = tempArr; //Transfers the temporary array into the unpacked_values array
            unpacked_values[i][*(counts+i)] = elmt;
            *(counts+i) += 1;
        }
    }

    num_elements += 1;  
}

//Function finds the element given the bin and the position inside the bin
template <class T> T& JaggedArray<T>::getElement(size_type bin, size_type position){

    //Error checking
    if (bin < 0 || position <0 || position > numElementsInBin(bin)-1 || bin > num_bins-1){
        cerr << "Input bin is invalid" << endl;
        exit(1);
    }
    if (this-> isPacked() == true){ //Returns element when array is packed
        return packed_values[offsets[bin]+position];
    }
    else { //Returns element when array is unpacked
        return unpacked_values[bin][position];
    }
}

//Function removes an element inside an array given the bin number and the position in that bin
template <class T> void JaggedArray<T>::removeElement(size_type bin, size_type binpos){

    //Error checking
    if (this-> isPacked() == true || bin <0  || binpos > numElementsInBin(bin)|| bin > num_bins || binpos < 0) {
        cerr << "Cannot make edits to a packed jagged array" << endl;
        exit(1);
    }

    //For loop starting at the bin index of unpacked_values array, it will shift all elements to the left, which will delete
    //the given element
    for (size_type index= bin; index < *(counts+bin); ++index){
        if (index +1 == *(counts+bin)) break;
        unpacked_values[bin][index] = unpacked_values[bin][index+1];
    }
    //Updating info
    num_elements -= 1;
    counts[bin] -= 1;
}

//Class destructor, deletes everything in the object
template <class T> JaggedArray<T>::~JaggedArray() {
    //Goes through every second arrays of unpacked_values and delete them
    //When finished, delete the entire unpacked_values array
    if (unpacked_values != NULL){
        for (size_type i=0; i<num_bins; ++i){
            delete[] unpacked_values[i];
        }
    }


    delete[] counts;
    delete[] unpacked_values;
    delete[] offsets;
    delete[] packed_values;
}