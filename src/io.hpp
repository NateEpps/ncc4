/**
 * @file
 * @author Nathanael Epps
 */

#ifndef IO_HPP
#define IO_HPP

#include <iostream>

namespace ncc::io {

/// @brief Initialize input
///
/// Parameters are input stream, output stream, and switch to control formatting
void init(std::istream&, std::ostream&, bool f = true);

/// @brief Read and return a character
char read();

/// @brief Unread a character
///
/// Doesn't actually put back in input stream-- simply stores for next `read` call.
void unread(char);

/// @brief Write an instruction to output
void write(std::string);

/// @brief Write unformatted output
void put(std::string);

/// @brief Write an error message to output
void error(std::string);

/// @brief Retrieve string used as a tab by `ncc::io`
std::string getTab();

/// @brief Miscellaneous log data
///
/// Params are source, message
void misc(std::string, std::string);

} // end namespace ncc::io

#endif
