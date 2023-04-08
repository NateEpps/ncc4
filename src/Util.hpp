/**
 * @file
 * @author Nathanael Epps
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// This and the associated source file are mainly used for things that need
// to be shared between the compiler, tests, and/or expgen-- this isn't really
// for compiler-specific code

namespace ncc {

/// @brief Vector of strings convenience typedef
typedef std::vector<std::string> args_t;

/// @brief `args_t` iterator
typedef std::vector<std::string>::iterator args_itr_t;

namespace util {

/// @brief Convert a string to a value via a stringstream
/// @tparam T
/// @param str
/// @return Converted value
template <class T>
T convert(std::string str) {
    if (str.empty())
        throw std::runtime_error("ncc::util::convert: Can't convert empty string");

    std::stringstream ss(str);
    T data;
    if (ss >> data)
        return data;
    else
        throw std::runtime_error("ncc::util::convert: Conversion error for string \"" + str + "\"");
}

/// @brief Return random integer in range [lo, hi]
///
/// Return 0 on error
int randInt(int lo, int hi);

/// @brief Bundle args
args_t bundle(int, const char**);

/// @brief Return an iterator to the given arg from the arg list
args_itr_t getOpt(args_t&, std::string);

/// @brief Get all non-options from `args`, meaning command line args that don't start with "-" or
/// "--"
std::vector<std::string> getParameters(const args_t& args);

/// @brief Given `args`, search for and return an iterator for the first parameter found
template <class... Args>
args_itr_t getOpt(args_t& args, std::string target, Args... extra) {
    args_itr_t itr = getOpt(args, target);

    if (itr == args.end())
        return getOpt(args, extra...);
    else
        return itr;
}

/// @brief Read and return file contents, given a file name.
///
/// Exception on error
std::string readFile(std::string);

/// @brief Write `contents` to file named `name`, replace contents if the file exists
void writeFile(std::string name, std::string contents);

/// @brief Return a nicely formatted string with the current date/time
std::string getFormattedDateTime();

} // end namespace util
} // end namespace ncc

#endif
