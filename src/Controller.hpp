/**
 * @file
 * @author Nathanael Epps
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Scanner.hpp"
#include "Scaffold.hpp"
#include <vector>

namespace ncc {

/**
 * @brief Runs the compiler at a high level
 *
 * Stores data section as well
 */
class Controller {
public:
    /// @brief Constructor
    Controller();
    
    /// @brief Run the compiler
    void run(ScaffoldType st);
    
    /// @brief Add a string literal to the data section, and return index
    ///
    /// Don't pass opening/closing quotes.
    /// @todo Issue 4 - Avoid duplication
    size_t addStringData(std::string);
    
    /// @brief Retrieve writeable data section
    std::string getDataSection();

private:
    Scanner scanner;
    Scaffold scaffold;
    
    std::vector<std::string> data;
    
};

}

#endif
