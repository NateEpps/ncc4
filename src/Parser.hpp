/*
 * @file
 * @author Nathanael Epps
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Scanner.hpp"

namespace ncc {
class Controller;

/**
 * @brief Parse high-level language constructs
 */
class Parser {
public:
    /// @brief Construct a parser
    explicit Parser(Controller*);

    /// @brief Parse a program
    void program();

protected:
    /// @brief Parent pointer
    Controller* const parent;

    /// @brief Expression/lexical scanner
    Scanner scanner;
};

}

#endif
