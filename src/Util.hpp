/**
 * @file
 * @author Nathanael Epps
 */

#ifndef UTIL_HPP
#define UTIL_HPP

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

/// @brief Return random integer in range [lo, hi]
///
/// Return 0 on error
int randInt(int lo, int hi);

/// @brief Bundle args
args_t bundle(int, const char**);

/// @brief Return an iterator to the given arg from the arg list
args_itr_t getOpt(args_t&, std::string);

/// @brief Given `args`, search for and return an iterator for the first parameter found
template <class... Args>
args_itr_t getOpt(args_t& args, std::string target, Args... extra) {
    args_itr_t itr = getOpt(args, target);
    
    if (itr == args.end())
        return getOpt(args, extra...);
    else
        return itr;
}

} // end namespace util
} // end namespace ncc

#endif
