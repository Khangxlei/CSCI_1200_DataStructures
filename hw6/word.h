#ifndef INC_7TH_WORD_H
#define INC_7TH_WORD_H

#include <string>
#include <vector>

// Store found word and position of where it is found
class word {
public:
    word(unsigned int x1,
         unsigned int x2,
         unsigned int y1,
         unsigned int y2,
         const std::string &w):
         theword(w),
         _start_x(x1),
         _start_y(y1),
         _end_x(x2),
         _end_y(y2),
         _length(w.size()),
         _position(x1 == x2){};

    // Getter
    const std::string &getWord() const {return theword;}
    unsigned int start_x() const {return _start_x;}
    unsigned int start_y() const {return _start_y;}
    unsigned int end_x() const {return _end_x;}
    unsigned int end_y() const {return _end_y;}

    // Helper
    unsigned int length() const {return _length;}
    int position() const {return _position;}

    bool is_between(unsigned int x, unsigned int y) const;

    // Debug
    void print() const;

    // Compare
    static bool same_word(const word &word1, const word &word2);
    static bool collapse(const word &word1, const word &word2);

private:
    std::string theword;
    unsigned int _start_x = 0;
    unsigned int _start_y = 0;
    unsigned int _end_x = 0;
    unsigned int _end_y = 0;

    unsigned int _length = 0;
    // Across: 0; Down: 1
    int _position = 0;
};

#endif