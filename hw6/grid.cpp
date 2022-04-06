#include <iostream>
#include <list>
#include <algorithm>
#include "grid.h"

const char NOTE_SYMBOL = '!';
const char CONSTRAINT_SYMBOL = '+';
const char PLACEHOLDER_SYMBOL = '#';

grid::grid(std::ifstream &file, Dictionary *d) {
  dict = d;
  std::string str;
  while (file >> str) {
    if (str.length() > 0) {
      // Should not be a note
      if (str[0] != NOTE_SYMBOL) {
        // A constraint
        if (str[0] == CONSTRAINT_SYMBOL) {
          constraints.push_back(std::stoi(str.erase(0, 1)));
        } else {
          std::vector<char> tmp(str.length(), PLACEHOLDER_SYMBOL);
          for (unsigned int i = 0; i < str.length(); i++) {
            tmp[i] = str[i];
          }
          map.push_back(tmp);
        }
      }
    }
  }

  // Always in order...
  constraints.sort(std::greater<unsigned int>());
}

// Get string by location and length
// if there is # on the path or unable to reach, return empty
std::string grid::getString(unsigned int x, unsigned int y, int type, unsigned int length) const {
  // Type 0: across, Type 1: Down
  std::string str;
  if (isLegalIndex(x, y)) {
    unsigned int end_x = x, end_y = y;
    if (type == 0) {
      end_x += length - 1;
    } else {
      end_y += length - 1;
    }

    if (isLegalIndex(end_x, end_y)) {
      if (type == 0) {
        for (unsigned int i = x; i <= end_x; i++) {
          if (map[y][i] != PLACEHOLDER_SYMBOL) {
            str.push_back(map[y][i]);
          } else {
            return std::string();
          }
        }
      } else {
        for (unsigned int i = y; i <= end_y; i++) {
          if (map[i][x] != PLACEHOLDER_SYMBOL) {
            str.push_back(map[i][x]);
          } else {
            return std::string();
          }
        }
      }
    }
  }

  return str;
}

// Entry
void grid::search_word() {
  search_recursive(0, 0, dict, searched);
}


/*
Recursive function starts with  x = y = 0. It will first make the the character is not a '#',



*/

// Recursively search all possible words in grid
void grid::search_recursive(unsigned int x,
                            unsigned int y,
                            Dictionary *dict,
                            std::list<word *> &result) {
  // Current Letter
  if (isLegalIndex(x, y)) {
    // start char should be legal
    if (map[y][x] != PLACEHOLDER_SYMBOL) {

      std::vector<unsigned int> d = dict->getLength(getChar(x, y));	//This line gets a vector of number. In dictionary class when initalized,
      																//the program went through the dictionary file, each time looking at the first letter
      																//of the word and appending the length of the word to its corresponding index inside the vector
      																//Ex: "country" will append 7 into 3rd vector (index 2) of big vector.
      // Check each of them
      for (unsigned int i = 0; i < d.size(); i++) {
        // Get Word in grid
        // Across?
        std::string c = getString(x, y, 0, d[i]);
        // Down?
        std::string down = getString(x, y, 1, d[i]);

        if (dict->search(c)) {
          result.push_back(new word(x, x + d[i] - 1, y, y, c));
        }

        if (dict->search(down)) {
          result.push_back(new word(x, x, y, y + d[i] - 1, down));
        }
      }
    } // Not a legal character

    // Proceed with one letter
    search_recursive(x + 1, y, dict, result);
  } else {
    // cross out of bound
    if (x >= col() && y < row()) {
      search_recursive(0, y + 1, dict, result);
    } else if (y >= row()) {
      // The end of the grid
    }
  }
}

// Get char by location
char grid::getChar(unsigned int x, unsigned int y) const {
  if (isLegalIndex(x, y)) { return map[y][x]; }
  return '\0';
}

// Clear all possible words when finished.
void grid::clear() {
  map.clear();
  constraints.clear();
  std::list<word *>::iterator i = searched.begin();
  while (i != searched.end()) {
    delete *i;
    i++;
  }
}

// Debug
void grid::print() const {
  std::cout << "Map: " << row() << " x " << col() << std::endl;
  std::cout << "Constraint: " << num_const() << std::endl;
  std::list<unsigned int>::const_iterator cb = constraints.begin();
  while (cb != constraints.end()) {
    std::cout << *cb << " ";
    cb++;
  }
  std::cout << std::endl;

  for (unsigned int i = 0; i < map.size(); i++) {
    for (unsigned int j = 0; j < map[i].size(); j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}