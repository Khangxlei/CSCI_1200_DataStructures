#include <iostream>

using namespace std;

template <class T> class JaggedArray {
public:
    //Typedef
    typedef unsigned int size_type;


    //Constructors, Assignment Operators and Destructors
    JaggedArray(const size_type& a) { this->create(a); }
    JaggedArray(JaggedArray& ja) {this-> copy(ja); }
    void operator=(JaggedArray<T>& v){this->copy(v);}
    ~JaggedArray();

    //Accessors
    size_type numBins(){ return num_bins; }
    size_type numElements(){return num_elements; }
    unsigned int numElementsInBin(unsigned int bin);
    T& getElement(size_type bin, size_type position);
    bool isPacked() const {return counts == NULL && unpacked_values==NULL; }
    void print();
    void pack();
    void unpack();

    //Modifiers
    void addElement(const size_type& ind, const T& elmt );
    void clear();
    void removeElement(size_type bin_pos, size_type pos_in_bin);
    

private:
    void copy(JaggedArray<T>& ja);
    void create(size_type a);
    void resize(T *&original, size_type size);

    size_type num_bins;
    size_type *counts;
    size_type num_elements;
    T** unpacked_values;
    size_type* offsets;
    T* packed_values;

};

//Creates the data structure to hold the information of elements
template <class T> void JaggedArray<T>::create(size_type a){
    num_bins = a;
    counts = new size_type[num_bins];
    num_elements = 0;
    unpacked_values = new T*[num_bins];
    offsets = NULL;
    packed_values = NULL;

    //Initializing all index of array to 0
    for (size_type i =0; i< num_bins; ++i){
        *(counts + i) = 0;
    }
    for (size_type i= 0; i<num_bins; ++i){
        unpacked_values[i] = new T[0];
    }

}

template <class T> void JaggedArray<T>::copy(JaggedArray<T>& ja){
    num_bins = ja.numBins();
    num_elements = ja.numElements();

    //If the JaggedArray is unpacked
    if (ja.isPacked() == false){
        offsets = NULL;
        packed_values = NULL;
    //Assigning count values from copy JaggedArray object to the new one
        counts = new size_type [num_bins];
        for (size_type i=0; i<num_bins; ++i){
            *(counts+i) = ja.counts[i];
        }

        //Creating the unpacked_values array
        unpacked_values = new T* [num_bins];
        for (size_type i=0; i<num_bins; ++i){
            unpacked_values[i] = new T [numElementsInBin(i)];
            for (size_type x=0; x<numElementsInBin(i); ++x){
                unpacked_values[i][x] = ja.getElement(i,x);
            }
        }
    }
    else {
        unpacked_values = NULL;
        counts = NULL;
        offsets = new size_type[num_bins];
        packed_values = new T[num_elements];
        for (size_type i= 0; i<num_bins; ++i){
            offsets[i] = ja.offsets[i];
        }
        for (size_type i=0; i<num_elements; ++i){
            packed_values[i] = ja.packed_values[i];
        }
    }
}




template <class T> void JaggedArray<T>::unpack(){
    if (this-> isPacked() == false) {
        cerr << "Jagged Array is currently unpacked" << endl;
        exit (1);
    }
    unpacked_values = new T*[num_bins];
    counts = new size_type [num_bins];
    for (size_type i =0; i<num_bins; ++i){
        if (num_bins -1 == i){ //Check to see if the index on counts array is the last one, since the value for that is calculated different
            counts[i] = num_elements - offsets[i];
        }
        else {
            *(counts+i) = offsets[i+1] - offsets[i];
        }
    }
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

template <class T> void JaggedArray<T>::pack(){
    if (this-> isPacked() == true){
        cerr << "Jagged Array is currently packed" << endl;
        exit(1);
    }
    offsets = new size_type [num_bins];
    offsets[0]= 0;
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
    for (size_type i=0; i<num_bins; ++i){
        delete [] unpacked_values[i];
    }
    delete[] unpacked_values;
    unpacked_values = NULL;
}

template <class T>  void JaggedArray<T>::print() {
    if (this-> isPacked() == true) { //Printing chart if jagged array's packed
        cout << "  num_bins:  "<< num_bins << endl;
        cout << "  num_elements:  " << num_elements << endl;
        cout << "  offsets: ";
        //Printing values in offsets array
        for(size_type index=0; index<num_bins; index++){
            std::cout<<offsets[index]<<' ';
        }
        cout << "\n   values:  ";

        //Printing values in packed_values array
        for(size_type i=0;i<num_elements;i++){
            std::cout<<packed_values[i]<<' ';
        }
    cout << endl;
    cout << endl;
    }

    else { //Printing chart if the jagged array is unpacked
        cout << "  num_bins:  "<< num_bins << endl;
        cout << "  num_elements:  "<< num_elements << endl;
        cout << "  counts:  ";
        for(size_type i=0; i<num_bins; i++) {
                cout << numElementsInBin(i) <<' ';
        }
        cout << endl;
        cout << "  values:  ";
        //Calculate max number of elements inside a single bin
        size_type max_elements = 0;
        for (size_type i =0; i<num_bins; ++i){
            if (numElementsInBin(i) > max_elements){
                max_elements = numElementsInBin(i);
            }
        }

        //For loop loops the max number of elements in a bin time to print values like output
        size_type line_no = 1;
        for (size_type i=0; i < max_elements; ++i){
            //For loop looping the number of bins, each time printing the index corresponding
            //to the line number
            for (size_type j=0; j<num_bins; ++j){
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


template <class T>  void JaggedArray<T>::clear(){
    if (this->isPacked() == true){
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



template <class T> void JaggedArray<T>::resize(T *&original, size_type size){
    T* resize = new T[size +1];
    for (size_type i=0; i<size+1; ++i){
        resize[i] = original[i];
    }
    delete [] original;
    original = resize;
}

template <class T> T& JaggedArray<T>::getElement(size_type bin, size_type position){
    if (this-> isPacked() == true){ //Returns element when array is packed
        if (bin < 0 || bin > num_bins-1){
            cerr << "Input bin is invalid" << endl;
            exit(1);
        }
        if (position <0 || position > numElementsInBin(bin)-1){
            cerr << "Bin position is invalid" << endl;
            exit(1);
        }
        return packed_values[offsets[bin]+position];
    }
    else { //Returns element when array is unpacked
        if (bin < 0 || bin > num_bins-1){
            cerr << "Input bin is invalid" << endl;
            exit(1);
        }
        if (position <0 || position > numElementsInBin(bin)-1){
            cerr << "Bin position is invalid" << endl;
            exit(1);
        }
        return unpacked_values[bin][position];
    }
}

template <class T> unsigned int JaggedArray<T>::numElementsInBin(unsigned int bin) {
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
    if (this ->isPacked() == true){
        cerr << "Jagged Array is currently in packed mode" << endl;
        exit(1);
    }
    else if (ind > num_bins || ind < 0) {
        cerr << "Invalid index" << endl;
        exit(1);
    }

    for (size_type i =0; i<num_bins; ++i){
        if (i == ind){ //If iterator reaches the index given my function argument, adds the element into the unpacked_array
            T *tempArr = new T [numElementsInBin(i)+1];
            for (size_type k =0; k < numElementsInBin(i); ++k){
                tempArr[k] = unpacked_values[i][k];
            }
            delete[] unpacked_values[i]; //Free the exising array
            unpacked_values[i] = tempArr; //Transfers the temporary array into the unpacked_values array
            unpacked_values[i][numElementsInBin(i)] = elmt;
            *(counts+i) += 1;
        }
    }

    num_elements += 1;  
}


template <class T> void JaggedArray<T>:: removeElement(size_type bin, size_type binpos){
    //Error checking
    if (this-> isPacked() == true){
        cerr << "Cannot make edits to a packed jagged array" << endl;
        exit(1);
    }
    else if (bin <0 || binpos > numElementsInBin(bin) || bin > num_bins || binpos < 0){
        cerr << "Input for bin/bin's position is invalid" << endl;
        exit(3);
    }
    for (size_type index= bin; index< *(counts+bin); ++index){
        if (index +1 == *(counts+bin)) {break;}
        unpacked_values[bin][index] = unpacked_values[bin][index+1];
    }
    //Updating info
    num_elements -= 1;
    counts[bin] -= 1;
}

template <class T> JaggedArray<T>::~JaggedArray()
{
    delete [] counts;
    delete [] offsets;
    delete [] packed_values;
    if(unpacked_values!=NULL)
        {
        for(size_type i=0; i<num_bins; i++)
            {
            delete [] unpacked_values[i];
            }
        delete [] unpacked_values;
        }
   counts=NULL;
   offsets=NULL;
   packed_values=NULL;
   unpacked_values=NULL;

}