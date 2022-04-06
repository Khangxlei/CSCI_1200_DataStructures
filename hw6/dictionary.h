#ifndef INC_7TH_DICTIONARY_H
#define INC_7TH_DICTIONARY_H


#include <fstream>
#include <vector>
#include <string>

// Parse Dict file
class Dictionary {
public:
    Dictionary(std::ifstream &file);

    // Getters
    unsigned int size() const { return list.size(); }
    const std::vector<unsigned int> &getLength(char x) const;
    bool search(std::string &str) const;

    // Debug
    void print() const;

private:
    std::vector<std::string> list;
    std::vector<std::vector<unsigned int>> alphabet = std::vector<std::vector<unsigned int>>(26);

    // Calculate Length
    void lengths();
};


#endif //INC_7TH_DICTIONARY_H