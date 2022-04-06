#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "grid.h"
#include "sort.h"

// Print Generated Map from 2D vector
void print_map(std::vector<std::vector<char>> & map, std::ostream &output) {
  output << "Board:" << std::endl;
  for (unsigned int i = 0; i < map.size(); i++) {
    for (unsigned int j = 0; j < map[i].size(); j++) {
      output << map[i][j];
    }
    output << std::endl;
  }
}

// .--------------.-------------------.---------------------.-----------------.---------------.-------------.
// | Program name |    Parameter 1    |     Parameter 2     |   Parameter 3   |  Parameter 4  | Parameter 5 |
// :--------------+-------------------+---------------------+-----------------+---------------+-------------:
// | ./a.out      | [dictionary file] | [initial grid file] | [solution mode] | [output mode] | [gc]        |
// '--------------'-------------------'---------------------'-----------------'---------------'-------------'
int main(int argc, char *argv[]) {
  // No matter what happened, 4 parameters are required.
  if (argc < 5)
  {
    std::cerr << "Program required at least 4 parameters to run." << std::endl;
    return 1;
  }

  // Open dict file
  std::ifstream in_dict_str(argv[1]);
  if (!in_dict_str.good())
  {
    std::cerr << "Can't open " << argv[1] << " to read." << std::endl;
    return 1;
  }

  Dictionary * dict = new Dictionary(in_dict_str);

  // Open Grid File
  std::ifstream in_grid_str(argv[2]);
  if (!in_grid_str.good())
  {
    std::cerr << "Can't open " << argv[2] << " to read." << std::endl;
    return 1;
  }

  grid * g = new grid(in_grid_str, dict);

  // Get Solution mode
  // one_solution / all_solution
  std::string mode = argv[3];

  bool one_solution = mode == "one_solution";

  // Get Output mode
  // count_only / print_boards
  std::string output = argv[4];

  bool count_only = output == "count_only";

  std::string gc = "";
  // Maybe we have 5th？
  if (argc > 5)
  {
    gc = argv[5];
  }

  bool is_giant_components = gc == "gc";

  // Search work
  g->search_word();

  sort s(g->getSearched(), g);
  s.setFlags(one_solution, count_only, is_giant_components);

  // Get combinations
  std::list<solution*> valid;
  s.combination(valid);

  unsigned int count = valid.size();

  std::list<solution*>::iterator iter;
  if (one_solution) {
    count >= 1 ? count = 1 : count = 0;
  }

  std::cout << "Number of solution(s): " << count << std::endl;
  if (!count_only) {
    std::vector<std::vector<char>> tmp;
    iter = valid.begin();
    while (iter != valid.end()) {
      if (count != 0) {
        (*iter)->generate_overlay(tmp);
        print_map(tmp, std::cout);
        count--;
      }
      delete *iter;
      iter++;
    }
  }

  // Clean up
  delete g;
  delete dict;

  return 0;
}