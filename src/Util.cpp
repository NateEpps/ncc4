//
// Util.cpp
// Nathanael Epps
//

#include "Util.hpp"

std::vector<std::string> ncc::util::bundle(int argc, const char** argv) {
    return std::vector<std::string>(argv, argv + argc);
}

std::vector<std::string>::iterator ncc::util::getOpt(std::vector<std::string>& args, std::string target) {
    return std::find(args.begin(), args.end(), target);
}
