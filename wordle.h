#ifndef WORDLE_H
#define WORDLE_H

#include <set>
#include <string>
#include <vector>

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict);

//The line below commented out is what my prototype was before and the other line is the prototype with adding in scoping to std
//void findWords(int place, string in, set<string>& pWords, const set<string>& dict, vector<char> f, string alphabet);
void findWords(int place, std::string in, std::set<std::string>& pWords, const std::set<std::string>& dict, std::vector<char> f, std::string alphabet);



// std::set<std::string> wordle(
//     const std::string& in,
//     const std::string& floating,
//     const std::set<std::string>& dict);

#endif