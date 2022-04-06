#include <iostream>
#include "jagged_array.h"
#include <cstring>

using namespace std;

int main() {
	JaggedArray <char> ja(7);
	cout << "Num Elements: " << ja.numElements() << endl;
	ja.addElement(1,'z');
	ja.addElement(2,'s');
	ja.addElement(1,'2');
	ja.addElement(4,'w');
	ja.addElement(3,'q');
	ja.addElement(1,'j');
	ja.addElement(1,'k');
	cout<<"khang"<<endl;
	cout << *(ja.numElementsInBin()+1) << endl;
	ja.print();
	ja.clear();


}