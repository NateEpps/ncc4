//
// Util.cpp
// Nathanael Epps
//

#include "Util.hpp"

ncc::args_t ncc::util::bundle(int argc, const char** argv) {
    return std::vector<std::string>(argv, argv + argc);
}

ncc::args_itr_t ncc::util::getOpt(ncc::args_t& args, std::string target) {
    return std::find(args.begin(), args.end(), target);
}
