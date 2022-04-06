/*
This is the implementation file for the Inventory class.
This file implements the functions that will be needed for the
the main program use the functions related to costumes.
*/

#include <iostream>
#include <string>
#include <vector>
#include <ostream>

#include "inventory.h"

//This function modifies the corresponding private member variables
//when a customer returns a costume back into the inventory
void Inventory::returnCostume(std::string& customer){
	copies += 1;
	//takes the name of the customer off the list
	for (unsigned int i=0; i<customers.size(); ++i){
		//delete the customer's name in the list
		if (customers[i].getName() == customer){
			customers.erase(customers.begin()+i);
			break;
		}
	}
}

//Function modifies variables when customer rents a specific
//costume in the inventory
void Inventory::rentCostume(std::string& customer){
	copies -= 1;
	customers.push_back(customer);
}

//Function prints out the information regarding the costume
void Inventory::costume_lookup(std::ostream& cout){
	cout << "Shop info for " << costume << " costumes:" << std::endl;
	//If there are more than one costume in the inventory
	if (copies > 1){
		cout << "  " << copies << " copies available" << std::endl;
	}
	//Only 1 costume
	else if (copies == 1){
		cout << "  1 copy available" << std::endl;
	}
	//if there is only 1 customer holding the costume
	if (customers.size() == 1){
		cout << "  1 copy rented by:\n    " << customers[0].getName() << std::endl;
	}
	//more than 1 customer holding the custome
	else if (customers.size() > 1){
		cout << "  " << customers.size() << " copies rented by:" << std::endl;
		//goes through the list of customers and print them out
		for (unsigned int i=0; i<customers.size(); ++i){
			cout << "    " << customers[i].getName() << std::endl;
		}
	}
}