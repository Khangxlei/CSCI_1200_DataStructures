#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H

#include "grid.h"
#include <list>

class solution {
public:
    solution(const std::list<word*> &w, grid * grid2): word_list(w), grid1(grid2) {};

    // Test given word set
    static bool is_valid(const std::list<word*> &word_list, grid *g);
    static bool is_valid_last(const std::list<word*> &word_list, grid *g, bool giant = false);
    // Generate map of words
    void generate_overlay(std::vector<std::vector<char>> &overlay) const;

private:
    std::list<word*> word_list;
    grid * grid1;

    // Checklist
    static bool no_same_word(const std::list<word*> &word_list);
    static bool no_collapse(const std::list<word*> &word_list);
    static bool no_invalid_words(const std::list<word*> &word_list, grid *g);

    static bool is_giant_components(const std::list<word*> &word_list);

    static bool special_begin_end(const std::list<word*> &word_list,
                                  grid *g);
    static bool surrounding(unsigned int x, unsigned int y, int position,
                            const std::list<word*> &word_list,
                            grid *g);
    static bool position_secured(int position, const std::list<word*> &word_list);
    static void num_of_words(unsigned int x, unsigned int y,
                             std::list<word *> &w,
                             const std::list<word*> &word_list,
                             grid *g);
    static void giant_recursive(word* current_word,
                                std::list<std::string> &words,
                                const std::list<word*> &word_list);
};

#endif