/**
 * @file
 * @author Nathanael Epps
 */

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>

namespace ncc {

class Controller;

/// @brief Operator types
enum class OpType {
    Plus, Minus, None
};

enum class TokenType {
    NumberLiteral, Operator, None
};

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

    /// @brief We've encountered an unimplemented feature
    void stub(std::string);

    /// @brief Match given character against `current`, and advance, skipping whitespace.
    void match(char);

    /// @brief Parse a number
    void parseNumber();

    /// @brief Parse an operator
    void parseOp();

    /// @brief Parse numberes, identifiers, literals, etc
    void parse();

    /// @brief Handle an add
    void add();

    /// @brief Handle subtraction
    void sub();

    /// @brief Tier 4 contains addition and subtraction
    void t4();

    /// @brief Parse an expression
    void expression();

protected:
    /// @brief Parent controller
    Controller* parent;

    /// @brief Current char
    char next;

    /// @brief Token, for lexical parsing
    std::string token;

    /// @brief Last parsed operator type
    OpType opType;

    /// @brief Token type
    TokenType tokenType;
};

}

#endif
