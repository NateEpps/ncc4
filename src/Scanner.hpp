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
    Plus, Minus, Multiply, Division, Modulus, None
};

/// @brief Token types
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
    
    /// @brief Require a condition is true-- string passed to `expected` on failure
    void require(bool, std::string);

    /// @brief We've encountered an unimplemented feature
    void stub(std::string);

    /// @brief Match given character against `current`, and advance, skipping whitespace.
    void match(char);

    /// @brief Parse a number
    /// @todo Issue 3 - Negative number handling
    /// @todo Issue 15 - Specific error handling for floats
    void parseNumber();

    /// @brief Parse an operator
    void parseOp();

    /// @brief Parse numberes, identifiers, literals, parenthesis, etc
    /// @todo Issue 14 - Parenthesis handling
    void parse();
    
    /// @brief Multiplication
    /// @todo Issue 13 - "require"ments
    void mult();
    
    /// @brief Division
    /// @todo Issue 13 - "require"ments
    /// @todo Issue 10 - Division Improvements
    void div();
    
    /// @brief Modulus
    /// @todo Issue 13 - "require"ments
    void mod();
    
    /// @brief Tier 3 contains multiplication, division, and modulus
    void t3();

    /// @brief Handle an add
    /// @todo Issue 13 - "require"ments
    void add();

    /// @brief Handle subtraction
    /// @todo Issue 13 - "require"ments
    /// @todo Issue 12 - No negq?
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
