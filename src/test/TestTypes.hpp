/**
 * @file
 * @author Nathanael Epps
 */

#ifndef TESTTYPES_HPP
#define TESTTYPES_HPP

#include <vector>
#include <string>

namespace ncc::test::types {

/// @brief Test input list
typedef std::vector<std::string> input_t;

/// @brief `input_t` iterator
typedef std::vector<std::string>::iterator input_iterator_t;

/// @brief Test input/output list
typedef std::vector<std::pair<std::string, std::string>> inputOutput_t;

/// @brief `inputOutput_t` itertator
typedef std::vector<std::pair<std::string, std::string>>::iterator inputOutput_iterator_t;

}

#endif
