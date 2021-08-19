/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Parser
*/

#ifndef LIB_PARSER_PARSER_HPP_
#define LIB_PARSER_PARSER_HPP_

#include <string>
#include <vector>
#include "Error.hpp"
#include "arcade.hpp"

namespace arc {
/** @class Parser
 * @brief Parser for .ini configuration files
 */
class Parser {
 public:
    explicit Parser(const std::string &filename);
    virtual ~Parser(void) {}

    inline std::vector<item> getItems(void) const { return _items;}
    inline char **getMap(void) const { return _map;}

 private:
    std::vector<std::string> readLines(std::ifstream &file);
    bool isFilenameCorrect(std::string filename);

    void parseMap(std::vector<std::string> lines);
    void parseItems(std::vector<std::string> &lines);
    item createItem(std::string line);

    std::vector<item> _items;
    char **_map;
};

/** @class ParseError
 * @brief Errors related to parsing
 */
class ParseError : public Error {
 public:
    explicit ParseError(std::string const &message)
        : Error(std::string("parser: ") + message) {}
};
}  // namespace arc
#endif  // LIB_PARSER_PARSER_HPP_
