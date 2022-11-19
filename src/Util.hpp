/**
 * @file
 * @author Nathanael Epps
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

namespace ncc::util {

/// @brief Bundle args
std::vector<std::string> bundle(int, const char**);

/// @brief Return an iterator to the given arg from the arg list
std::vector<std::string>::iterator getOpt(std::vector<std::string>&, std::string);

/// @brief Given `args`, search for and return an iterator for the first parameter found
template <class... Args>
std::vector<std::string>::iterator getOpt(std::vector<std::string>& args, std::string target, Args... extra) {
    auto itr = getOpt(args, target);
    
    if (itr == args.end())
        return getOpt(args, extra...);
    else
        return itr;
}

} // end namespace ncc::util

#endif
