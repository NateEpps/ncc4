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

/// @brief Write an instruction to ouput
void write(std::string);

}

#endif
