/**
 * @file
 * @author Nathanael Epps
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Parser.hpp"
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
    ///
    /// This runs the compiler at the highest conceptual level. When testing, or for other
    /// development purposes, this is the method to wrap in a `try` / `catch` setup
    void run(ScaffoldType st);

    /// @brief Add a string literal to the data section, and return index
    ///
    /// DO NOT pass opening/closing quotes.
    /// @todo Issue 4 - Avoid duplication
    size_t addStringData(std::string);

    /// @brief Retrieve writeable data section
    std::string getDataSection();

  protected:
    /// @brief High-level parser
    Parser parser;

    /// @brief Output extra surrounding code until, like, __0.7__
    Scaffold scaffold;

    /// @brief Data section until we do something better
    std::vector<std::string> data;
};

} // namespace ncc

#endif
