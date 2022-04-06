
/*
This program takes in a user input file that contain command keywords. 
Keywords range from accessing/iterating through different lists of 
information, from customer's data to DVD's inventory data. 
Based on those keywords, the program will go through different functions
that gives out a certain output. 

Khang Le
Data Structures CSCI 1200
03.04.2021

Note: I will only be commenting on code that I have written. The ones
that have been provided have been commented, so I will not be changing
them.
*/

// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "Customer.h"
#include "DVD.h"

using namespace std;

// several type defs to keep things neat
// (hint, these are STL lists)
typedef list<DVD> inventory_type;
typedef list<Customer> customers_type;
typedef list<string> preference_type;
typedef list<string> possession_type;

// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }

  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }
  

  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;


  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;

      //Loops through the inventory list to see if the movie is already on the list. If it is,
      //then simply add more copies to it rather than creating another DVD object
      unsigned int dvd_count =0;
      for (inventory_type::iterator inv_it = inventory.begin(); inv_it!= inventory.end(); ++inv_it ){
        if (inv_it-> get_name() == dvd_name){
          dvd_count +=1;
          inv_it-> addCopies(copies);
        }
      }
      // If the given DVD is not in the inventory, it will create a DVD object and add it into the list
      if (dvd_count == 0){
        DVD a(copies, dvd_name);
        inventory.push_back(a);
      }

      //Program confirmation that it has successfuly added the DVD into inventory
      if (copies > 1){
        ostr << copies << " copies of " << dvd_name << " added" << endl;
      }
      else if (copies == 1) {
        ostr << copies << " copy of " << dvd_name << " added" << endl;
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */
      

      //Makes a Customer class object, containing their name and a list of their movie preferences.
      //This will be added into the customers list.
    } else if (token == "customer") {
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;

      //Make a user movie preference list from the input file, checks for error.
      preference_type preferences;
      for (int i = 0; i < num_movies; i++) {
        std::string dvd_name = read_dvd_name(istr);
        //Error checking: checks to see if the given movie preferences are in the inventory
        bool dvd_exist = false
;        for (inventory_type::iterator itr = inventory.begin(); itr!= inventory.end(); ++itr){
          if (itr-> get_name() == dvd_name){
            dvd_exist = true;
          }
        }
        if (dvd_exist == true){
          preferences.push_back(dvd_name);
        }
        if (dvd_exist == false){
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << endl;
        }
      }

      //Error checking: check if the given customer is valid
      unsigned int customer_check=0;
      for (customers_type::iterator itr = customers.begin(); itr!= customers.end(); ++itr){
          if (itr-> get_name() == customer_name){
            ostr << "WARNING: Already have a customer named " << customer_name << endl;
            customer_check += 1;
          }
      }

      //Error checking: checks to see if there are duplicates in the preference list O(log n)
      unsigned int duplicate_check=0;
      for (preference_type::iterator itr = preferences.begin(); itr!= preferences.end(); ++itr){

        //Create a second iterator that is one element after the current iterator
        //It will go around the for loop again to check for duplicates
        preference_type::iterator itr2 = itr;
        itr2++;
        for (itr2 = itr2; itr2!= preferences.end(); ++itr2){
          if(*itr2 == *itr){
            ostr << "WARNING: Duplicate movie " << *itr2 << " on preference list!" << endl;
            itr2 = preferences.erase(itr2);
            itr2--;
            duplicate_check+=1;
          }
        }
      }

      //If there are no errors, it will create a Customer class object with the preference list and add it into 
      //the customer list
      if (customer_check == 0){
        preferences.unique(); 
        Customer a(customer_name, preferences);
        customers.push_back(a); 
        ostr << "new customer: " << customer_name << endl;
      }


      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "ship") {

      shipping_algorithm(inventory,customers, ostr);
      
    } else if (token == "return_oldest") {
        string customer_name = read_customer_name(istr);

        //Error checking: Checks if customer is not in file or has no DVDs
        bool no_customer = true;
        bool no_dvd = false;
        customers_type::iterator itr;
        for (itr = customers.begin(); itr != customers.end(); ++itr){
          if (itr-> get_name() == customer_name) {
            no_customer = false; 
            if (itr-> posessed_list_empty() == true) {no_dvd = true; }
          }
        }

        //Error output
        if (no_customer == true){ ostr << "WARNING: No customer named " << customer_name << endl; }
        if (no_dvd == true){ostr << "WARNING: " << customer_name <<  " has no DVDs to return!" << endl; }

        //If it is error free, program find the given customer, prints their oldest movie in possession, return it into the inventory
        //and remove the DVD from their list
        if (no_customer == false && no_dvd == false){
          customers_type::iterator customer_itr;
          for (customer_itr = customers.begin(); customer_itr !=customers.end(); ++customer_itr){

            //When for loop finds the given customer's name, it will find the customer's oldest movie and print it
            if (customer_itr-> get_name() == customer_name){  
              string old_movie = customer_itr-> getOld();  
              if (old_movie != ""){
                ostr << customer_name << " returns " << old_movie << endl;
              }

              //Goes through the inventory list to find the customer's oldest movie, and returns that DVD into the inventory
              inventory_type::iterator inventory_itr;
              for (inventory_itr = inventory.begin(); inventory_itr != inventory.end(); ++inventory_itr){
                  if (customer_itr-> getOld() == inventory_itr-> get_name()){
                    inventory_itr-> returnDVD();
                    break;
                  }
              }

              //Program returns the customer's oldest movie by removing it from their list
              if (old_movie != ""){
                customer_itr-> returnOld();
              }
              break;
            }
          }
        }

      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "return_newest") {
      std::string customer_name = read_customer_name(istr);
      //Error checking: Checks if customer is not in file or has no DVDs
      bool no_customer = true;
      bool no_dvd = false;
      customers_type::iterator itr;
      for (itr = customers.begin(); itr != customers.end(); ++itr){
        if (itr-> get_name() == customer_name) {
          no_customer = false; 
          if (itr-> posessed_list_empty() == true) {no_dvd = true; }
        }
      }

      //Error output
      if (no_customer == true){ ostr << "WARNING: No customer named " << customer_name << endl; }
      if (no_dvd == true){ostr << "WARNING: " << customer_name <<  " has no DVDs to return!" << endl; }

      //Similar to return_oldest chunk of code. If it is error free, program will find the customer's newest movie,
      //print the movie, remove the movie from the customer's list and return it back
      //into the inventory
      if (no_customer == false && no_dvd == false){
        customers_type::iterator customer_itr;

          //For loop finds the given customer's name in the list
          for (customer_itr = customers.begin(); customer_itr !=customers.end(); ++customer_itr){

            //Finds the customer's newest movie and prints it
            if (customer_itr-> get_name() == customer_name){
              string new_movie = customer_itr-> getNew();  
              if (new_movie != ""){
                ostr << customer_name << " returns " << new_movie<< endl;
              }

              //Return the newest movie into the inventory list
              inventory_type::iterator inventory_itr;
              for (inventory_itr = inventory.begin(); inventory_itr != inventory.end(); ++inventory_itr){
                  if (customer_itr-> getNew() == inventory_itr-> get_name()){
                    inventory_itr-> returnDVD();
                    break;
                  }
              }

              //Makes sure the customer returns the newest movie by removing it from their list
              if (new_movie != ""){
                customer_itr-> returnNew();
              }
              break;
            }
          }
        }


      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "print_customer") {
      std::string customer_name = read_customer_name(istr);
      customers_type::iterator itr;

      //Error checking: Checks if given customer is valid
      unsigned int customer_check =0;
      for (itr = customers.begin(); itr != customers.end(); ++itr){

        //If for loop finds the customer (which means it is valid), it will print the customer's information
        //which is a class member function
        if (itr-> get_name() == customer_name){
          customer_check += 1;
          ostr << itr-> printCustomer() << endl;
        }
      }

      //Error output
      if (customer_check == 0){
        ostr << "WARNING: No customer named " << customer_name << endl;
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "print_dvd") {
      std::string dvd_name = read_dvd_name(istr);

      //Error checking: Checks to see if the given movie is in the inventory
      inventory_type::iterator itr;
      unsigned int flag =0;
      for (itr = inventory.begin(); itr != inventory.end(); ++itr){
        if (itr-> get_name() == dvd_name){flag += 1; }
      }

      //If it is error free, program will find the dvd in the inventory list, and print its info
      //using the printDVD() class member function
      if (flag > 0){
        ostr << dvd_name << ':' << endl;
        inventory_type::iterator itr;
        for (itr = inventory.begin(); itr != inventory.end(); ++itr){
          if (itr-> get_name() == dvd_name){ ostr << itr-> printDVD() << endl;}
        }
      }

      //Error output
      else if (flag ==0){
        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << endl;
      }


      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "add_preference") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);

      //Error checking: Checks if given customer is not in the list, if the given dvd name is already in the customer's preference list
      //and if the customer is already holding the given movie
      unsigned int customer_check=0;
      unsigned int pref_duplicate_check = 0;
      unsigned int possess_check=0;
      customers_type::iterator customer_it;

      for (customer_it = customers.begin(); customer_it != customers.end(); ++customer_it){
        if (customer_it-> get_name() == customer_name){

          //Goes through the user's list of movies they're holding, and see if the given movie is within the list
          //If it is, then raise possess_check by 1 which indicates an error
          possession_type movie_possession = customer_it-> get_possession();
          for (possession_type::iterator pos_it = movie_possession.begin(); pos_it != movie_possession.end(); ++pos_it){
            if (dvd_name == *pos_it){
              possess_check += 1;
            }
          }

          //Goes through customer's preference list to see if the given dvd is already in their list
          preference_type preferences = customer_it-> get_preferences();
          preference_type::iterator pref_itr;
          for (pref_itr = preferences.begin(); pref_itr!= preferences.end(); ++pref_itr){
            if (*pref_itr == dvd_name) {pref_duplicate_check += 1; }
          }
          customer_check += 1;
        }
      }

      //Error checking: See if the given movie is in the inventory. If not, error output
      unsigned int inventory_check=0;
      inventory_type::iterator inv_it;
      for (inv_it = inventory.begin(); inv_it != inventory.end(); ++inv_it){
        if (inv_it-> get_name() == dvd_name){
          inventory_check+=1;
        }
      }

      //Error output
      if (customer_check == 0){
        ostr << "WARNING: No customer named " << customer_name << endl;
      }
      if (pref_duplicate_check > 0){
        ostr << "WARNING: " << customer_name << " already has " << dvd_name << " on his/her preference list!" << endl;
      }
      if (possess_check > 0){
        ostr << "WARNING: " << customer_name << " currently has " << dvd_name << '!' << endl;
      }

      if (inventory_check ==0){
        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << endl;
      }

      //If everything is error free, find the customer in the list and add the input movie into their preference list
      if (customer_check != 0 && inventory_check != 0 && pref_duplicate_check == 0 && possess_check == 0){
          for (customer_it = customers.begin(); customer_it != customers.end(); ++customer_it){
            if (customer_it-> get_name() == customer_name){
              customer_it-> addPreference(dvd_name);
            }
          }
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else {
      cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}

// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->get_name() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}


// ==================================================================

// A basic algorithm for determining which movies to ship to each customer
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr ) {

  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;
   
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(*preferences_itr); 
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }

  //*/

}

// ==================================================================
