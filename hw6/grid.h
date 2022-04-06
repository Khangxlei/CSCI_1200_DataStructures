#ifndef INC_7TH_GRID_H
#define INC_7TH_GRID_H


#include <fstream>
#include <vector>
#include <list>
#include "dictionary.h"
#include "word.h"

// Parse map and search possible map
class grid {
public:
    grid(std::ifstream &file, Dictionary *d);
    ~grid(){ clear(); }

    // Getters
    unsigned int row() const { return map.size(); }
    unsigned int col() const { return row() > 0 ? map[0].size() : 0; }
    unsigned int num_const() const { return constraints.size(); };
    const std::vector<std::vector<char>> &getMap() const { return map; }
    const std::list<unsigned int> &getConstraints() const { return constraints; };
    Dictionary * getDictionary() const { return dict; }
    std::list<word*> getSearched() const { return searched; };
    char getChar(unsigned int x, unsigned int y) const;
    std::string getString(unsigned int x,
                          unsigned int y,
                          int type,
                          unsigned int length) const;
    // Helper
    bool isLegalIndex(unsigned int x, unsigned int y) const { return x < col() && y < row(); };

    // Entry
    void search_word();

    // Debug
    void print() const;


    void clear();
private:
    std::vector<std::vector<char>> map;
    Dictionary * dict = nullptr;
    std::list<unsigned int> constraints;
    std::list<word*> searched;

    void search_recursive(unsigned int x,
                          unsigned int y,
                          Dictionary * dict,
                          std::list<word*> &result);
};


#endif