/*
This program applies the knowledge of maps, and utilize the STL class
to store data and provide corresponding outputs given a set of input.
The program keeps track of a Halloween costume store, which 
customer rents which costume and provide the user the information.

Khang Le
Data Structures
04.02.2021
*/

#include <iostream>
#include<string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <list>

#include "customer.h"
#include "inventory.h"

using namespace std;

//This function will print out all the customers holding a given costume that is passed through
void costume_lookup(map<string, vector<string>>& rent_notebook, map<string, int>& inventory, const string& costume){
	//create iterators for both maps
	map<string, vector<string>>::iterator notebook_itr = rent_notebook.find(costume);
	map<string, int>::iterator inv_itr = inventory.find(costume);

	//if given costume is in the inventory and rent notebook
	if (inv_itr != inventory.end() && notebook_itr != rent_notebook.end()){
		cout << "Shop info for " << costume << " costumes:" << endl;
		if ((inv_itr->second) > 1){
			cout << "  " << (inv_itr->second) << " copies available" << endl;
		}
		else if ((inv_itr->second) == 1){
			cout << "  " << inv_itr->second << " copy available" << endl;
		}
		if ((notebook_itr->second).size() == 1){
			cout << "  1 copy rented by:\n    " << (notebook_itr->second)[0] << endl;
		}
		else if ((notebook_itr->second).size() > 1){
			cout << "  " << (notebook_itr->second).size() << " copies rented by:" << endl;
			for (unsigned int i=0; i < (notebook_itr->second).size(); ++i){
				cout << "    " << (notebook_itr->second)[i] << endl;
			}
		}
	}
	//if the given costume is not in either maps
	else {
		cout << "The shop doesn't carry " << costume << " costumes." << endl;
	}
}

//Helper function sorts two pairs of strings, this is done for the
//sort() function to sort the list of customers alphabetically
bool sort_name(pair<string, string>& a, pair<string, string>& b){
	//create strings to stores the customers' first and last names
	int pos;
	string last_a;
	string last_b;
	string first_a;
	string first_b;

	//Parses the customers' full names, separating them into first and last names
	pos = (a.first).find(" ");
	last_a = (a.first).substr(pos+1, (a.first).size()-(pos+1));
	first_a = (a.first).substr(0, pos);
	pos = (b.first).find(" ");
	last_b = (b.first).substr(pos+1, (b.first).size()-(pos+1));
	first_b = (b.first).substr(0,pos);

	//if the customers' last names are the same, return the bool function for their first names
	if (last_a == last_b){
		return first_a < first_b;
	}
	return last_a < last_b;
}

//This function will print out the costumes of all the customers in the data structure
void print_attendees(map<string, string>& customer){
	
	//Checks if there is only one customer and print them only
	if (customer.size() == 1){
		cout << "Costume info for the 1 party attendee:" << endl;
		map<string, string>::const_iterator itr = customer.begin();
		//if the one customer does not have a costume
		if ((itr->second).size() <= 0){
			cout << "  " << itr->first << " does not have a costume." << endl;
		}
		//if they have a costume
		else {
			cout << "  " << itr->first << " is wearing a " << itr->second << " costume." << endl;
		}
	}

	//If there is more than one customer in data
	else if (customer.size() > 1){

		//Create a vector of pair of 2 strings
		vector<pair<string, string>> vect;
		//transfer all the customer data into the vector
		for (map<string, string>::const_iterator itr = customer.begin(); itr != customer.end(); ++itr){
			vect.push_back(*itr);
		}
		//sort the vector alphabetically with the sort_name helper function
		sort(vect.begin(), vect.end(), sort_name);
		cout << "Costume info for the " << vect.size() << " party attendees:" << endl;
		//goes through the sorted vector, and print out the customer's costume
		for (unsigned int i=0; i<vect.size(); ++i){
			if ((vect[i].second).size() <= 0){
				cout << "  " << vect[i].first << " does not have a costume." << endl;
			}
			else {
				cout << "  " << vect[i].first << " is wearing a " << vect[i].second << " costume." << endl;
			}
		}
	}
}

int main(int argc, char* argv[]){
	//Error and mode check
	string mode;
	if (argc > 2){
		cout << "Too much arguments given" << endl;
	} 
	if (argc < 2) {
		mode = "normal";
	}
	else {
		mode = argv[1];
	}

	//If mode is normal, (not extra credit)
	if (mode == "normal"){

		//create 3 maps, inventory holds the copies of costume.
		//customer holds the costume of every customer.
		//rent_notebook holds list of customers holding a costume
		map<string, int> inventory;
		map<string, string> customer;
		map<string, vector<string>> rent_notebook;

		//Taking in input file data
		string token;
		while (cin >> token){
			//add operation
			if (token == "a"){
				string costume;
				int copies;
				cin >> costume;
				cin >> copies;

				//Find if the costume is already in the inventory map
				map<string, int>::iterator itr = inventory.find(costume);

				//if the costume is not in the inventory, we add it into the inventory
				if (itr == inventory.end()){
					inventory.insert(make_pair(costume, copies));
					vector<string> empty_vect;
					rent_notebook.insert(make_pair(costume, empty_vect));
				}
				//if the costume is in the inventory, we simply add it
				else {
					itr->second += copies;
				}
				if (copies > 1){
					cout << "Added " << copies << ' ' << costume << " costumes." << endl;
				}
				else {
					cout << "Added " << copies << ' ' << costume << " costume." << endl;
				}
			}
			//rent operation
			else if (token == "r"){
				//variable declarations
				string first;
				string last;
				string full_name;
				string costume;

				cin >> first;
				cin >> last;

				full_name = first + " ";
				full_name += last;
				cin >> costume;

				//finds the costume and customer's name in the inventory and customer map
				map<string, int>::iterator shop_itr = inventory.find(costume);
				map<string, string>::iterator customer_itr = customer.find(full_name);


				//Finds if the customer's name is in the map, if not add the customer 
				//into the map
				if (customer_itr == customer.end()){
					customer.insert(make_pair(full_name, ""));
				}


				//Checks if the shop holds the given costume
				int check =0;
				if (shop_itr == inventory.end()){
					cout << "The shop doesn't carry " << costume << " costumes." << endl;
					check += 1;
				}

				else {
					if (shop_itr-> second <= 0){
						cout << "No " << costume << " costumes available." << endl;
						check += 1;
					}
				}

				//Error free
				if (check == 0){
					//Finds if the customer's name is on the map
					map<string, string>::iterator customer_itr = customer.find(full_name);

					//If customer is not on the map, we add them onto the map and allow them to borrow the costume
					if (customer_itr == customer.end()){
						customer.insert(make_pair(full_name, costume));
						cout << full_name << " rents a " << costume << " costume." << endl;

						(shop_itr->second) -= 1;

						//Add this onto the notebook, to keep track which customers hold the customer
						map<string, vector<string>>::iterator notebook_it = rent_notebook.find(costume);
						(notebook_it->second).push_back(full_name);
					}
					//Else if the customer is on the map
					else {
						string customer_pos = customer_itr->second;
						//If customer is already holding the costume
						if (customer_pos == costume) cout << full_name << " already has a " << costume << " costume." << endl;
						//if customer is holding a different costume
						else if (customer_pos.size() >0){
							cout << full_name << " returns a " << (customer_itr->second) << " costume before renting a " << costume << " costume." << endl;

							//Finds the customer's costume in the inventory and returns it
							map<string, int>::iterator return_costume = inventory.find(customer_pos);
							return_costume->second += 1;
							map<string, vector<string>>::iterator notebook_it = rent_notebook.find(customer_pos);
							vector<string> customers = notebook_it->second;

							//loop through the vector of customers holding the costume, and remove the current customer out of the vector
							for (unsigned int i=0; i<customers.size(); ++i){
								if (customers[i] == full_name){
									(notebook_it->second).erase((notebook_it->second).begin() + i);
								}
							}

							//Rents the given costume to the customer
							(shop_itr->second) -= 1;
							customer_itr->second = costume;

							//Finds the costume's name in the rent_notebook map and push_back the customer's name onto the list
							notebook_it = rent_notebook.find(costume);
							(notebook_it->second).push_back(full_name);
						}
						//if customer is not holding any costumes
						else if (customer_pos.size() == 0){
							cout << full_name << " rents a " << costume << " costume." << endl;
							customer_itr->second = costume;
							(shop_itr->second) -= 1;

							//Finds the costume's name in the rent_notebook map and push_back the customer's name onto the list
							map<string, vector<string>>::iterator notebook_it = rent_notebook.find(costume);
							(notebook_it->second).push_back(full_name);
						}
					}
				}
			}
			//lookup operation
			else if (token == "l"){
				string costume;
				cin >> costume;
				costume_lookup(rent_notebook, inventory, costume);
			}
			//print operation
			else if (token == "p"){
				print_attendees(customer);
			}
		}
	}
	else if (mode == "ec"){
		//create 2 lists:
		//customer_list holds Customer class object which have information regarding the customers
		//inventory_list holds Inventory objects, which have information regarding the costumes
		list<Customer> customer_list;
		list<Inventory> inventory_list;

		//Taking in input data
		string token;
		while (cin >> token){
			//add operation
			if (token == "a"){
				string costume;
				int copies;
				cin >> costume;
				cin >> copies;

				int check =0;
				//Goes through inventory list to see if its already been added
				for (list<Inventory>::iterator itr = inventory_list.begin(); itr != inventory_list.end(); ++itr){
					if ((*itr).getCostume() == costume){
						(*itr).addCopies(copies);
						check += 1;
					}
				}
				//if costume is not in the list
				if (check == 0){
					Inventory inv(costume, copies);
					inventory_list.push_back(inv);
				}
				if (copies > 1){
					cout << "Added " << copies << ' ' << costume << " costumes." << endl;
				}
				else {
					cout << "Added " << copies << ' ' << costume << " costume." << endl;
				}
			}	

			//rent operation
			else if (token == "r"){
				//variable declarations
				string first;
				string last;
				string full_name;
				string costume;

				cin >> first;
				cin >> last;

				full_name = first + " ";
				full_name += last;
				cin >> costume;

				//Error checking variables
				int check = 0;
				int costume_check = 0;

				//Checks if the given costume is in the inventory, and if there is enough copies
				for (list<Inventory>::iterator itr = inventory_list.begin(); itr != inventory_list.end(); ++itr){
					if ((*itr).getCostume() == costume){
						costume_check += 1;
						if ((*itr).getCopies() == 0){
							check += 1;
							cout << "No " << costume << " costumes available." << endl;
						}
					}
				}

				//if there are no costumes in the store
				if (costume_check == 0) cout << "The shop doesn't carry " << costume << " costumes." << endl;

				int customer_check = 0;
				int customer_costume = 0;

				//Checks if the customer is in the list, if not we add them into the list
				for (list<Customer>::iterator c_it = customer_list.begin(); c_it != customer_list.end(); ++c_it){
					if ((*c_it).getName() == full_name){
						//if the customer is already holding the given costume
						if ((*c_it).getCostume() == costume){
							cout << full_name << " already has a " << costume << " costume." << endl;
							customer_costume += 1;
						}
						customer_check += 1;
					}
				}

				//Add customer onto list if they're not in it
				if (customer_check == 0){
					Customer a(full_name);
					customer_list.push_back(a);
				}

				//Error free
				if (costume_check >0 && check == 0 && customer_costume == 0){
					//goes through the inventory and update the necessary information for when a customer rent a costume
					//saves the iterator for later
					list<Inventory>::iterator inv_itr = inventory_list.begin(); 
					while (inv_itr != inventory_list.end()){
						if ((*inv_itr).getCostume() == costume){
							(*inv_itr).rentCostume(full_name);	
							break;
						}
						++inv_itr;
					}
					//loops through customer list to find the customer, when it finds the customer, breaks the for
					//loop to save the iterator
					list<Customer>::iterator cust_it = customer_list.begin();
					while (cust_it != customer_list.end()){
						if ((*cust_it).getName() == full_name) break;
						++cust_it;
					}
					//goes through list of customers, and does the correct operation to rent the customer the costume
					for (list<Customer>::iterator cust_it = customer_list.begin(); cust_it != customer_list.end(); ++cust_it){
						if ((*cust_it).getName() == full_name){
							//if the customer is holding a different costume
							if ((*cust_it).getCostume().size() > 0){
								//goes through inventory list to find the costume the customer is returning, and returns int
								for (list<Inventory>::iterator itr = inventory_list.begin(); itr != inventory_list.end(); ++itr){
									if ((*itr).getCostume() == (*cust_it).getCostume()){
										(*itr).returnCostume(full_name);
										(*cust_it).setCostume(costume);
										cout << full_name << " returns a " << (*itr).getCostume() << " costume before renting a " << costume << " costume." << endl;
										break;
									}
								}
							}
							//if customer is not holding any costumes, we simply set the given costume as their new costume
							else if ((*cust_it).getCostume().size() == 0){
								(*cust_it).setCostume(costume);
								cout << full_name << " rents a " << costume << " costume." << endl;
							}
						}
					}
				}
			}
			//lookup operation
			else if (token == "l"){
				string costume;
				cin >> costume;
				int check =0;
				//goes through inventory list and prints the information of the costume
				for (list<Inventory>::iterator inv_it = inventory_list.begin(); inv_it != inventory_list.end(); ++inv_it){
					if ((*inv_it).getCostume() == costume){
						check += 1;
						(*inv_it).costume_lookup(std::cout);
						break;
					}
				}
				//if the given costume is not in the inventory
				if (check == 0){
					cout << "The shop doesn't carry " << costume << " costumes." << endl;
				}
			}
			//print operation
			else if (token == "p"){
				//if there is only 1 customer 
				if (customer_list.size() == 1){
					//print the costume of the 1 customer
					cout << "Costume info for the 1 party attendee:" << endl;
					list<Customer>::iterator cust_it = customer_list.begin();
					if ((*cust_it).getCostume().size() <= 0){
						cout << "  " << (*cust_it).getName() << " does not have a costume." << endl;
					}
					else {
						cout << "  " << (*cust_it).getName() << " is wearing a " << (*cust_it).getCostume() << " costume." << endl;
					}
				}
				//if there is more than 1 customer
				else if (customer_list.size() > 1){
					//create a vector of pair of strings
					vector<pair<string, string>> vect;
					//goes through customer list and add the customer's name and costume as a pair into the vector
					for (list<Customer>::iterator itr = customer_list.begin(); itr != customer_list.end(); ++itr){
						string name = (*itr).getName();
						string costume_ = (*itr).getCostume();
						vect.push_back(make_pair(name, costume_));
					}

					//sort the vector alphabetically by customers' names
					sort(vect.begin(), vect.end(), sort_name);
					cout << "Costume info for the " << vect.size() << " party attendees:" << endl;
					//goes through the sorted vector and print their costumes
					for (unsigned int i=0; i<vect.size(); ++i){
						if ((vect[i].second).size() <= 0){
							cout << "  " << vect[i].first << " does not have a costume." << endl;
						}
						else {
							cout << "  " << vect[i].first << " is wearing a " << vect[i].second << " costume." << endl;
						}
					}
				}
			}
		}
	}
}