//
// Util.cpp
// Nathanael Epps
//

#include "Util.hpp"
#include <algorithm>
#include <cstdlib>

int ncc::util::randInt(int lo, int hi) {
    static bool init = false;
    if (!init) {
        srand(time(nullptr));
        init = true;
    }
    
    if (lo < hi)
        return rand() % (hi - lo + 1) + lo;
    else
        return 0;
}

ncc::args_t ncc::util::bundle(int argc, const char** argv) {
    return std::vector<std::string>(argv, argv + argc);
}

ncc::args_itr_t ncc::util::getOpt(ncc::args_t& args, std::string target) {
    return std::find(args.begin(), args.end(), target);
}
