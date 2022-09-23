/**
 * @file
 * @author Nathanael Epps
 */

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>

namespace ncc {

class Controller;

/**
 * @brief Handle expressions
 */
class Scanner {
public:
    /// @brief Constructor, store parent controller
    Scanner(Controller*);
    
    /// @brief Skip whitespace
    void skipWs();
    
    /// @brief Parser expected (argument)
    void expected(std::string);
    
    /// @brief Match given character against `current`, and advance, skipping whitespace.
    void match(char);
    
    /// @brief Parse a number
    void parseNumber();
    
    /// @brief Parse... something. Right now only handles numbers
    void parse();
    
    /// @brief Parse an expression
    void expression();
    
protected:
    /// @brief Parent controller
    Controller* parent;
    
    /// @brief Current char
    char current;
    
    /// @brief Token, for lexical parsing
    std::string token;
};

}

#endif
