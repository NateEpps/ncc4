//
// Util.cpp
// Nathanael Epps
//

#include "Util.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <random>
#include <sstream>

int ncc::util::randInt(int lo, int hi) {
    if (lo >= hi)
        return 0;
    
    // This is disgusting and I hate it but it works a lot better then rand()
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<> distribution(lo, hi);
    
    return distribution(generator);
}

ncc::args_t ncc::util::bundle(int argc, const char** argv) {
    return std::vector<std::string>(argv, argv + argc);
}

ncc::args_itr_t ncc::util::getOpt(ncc::args_t& args, std::string target) {
    return std::find(args.begin(), args.end(), target);
}

std::string ncc::util::readFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error(std::string("readFile(\"") + filename + "\") failed: unable to open stream");
    
    std::stringstream bufferStream;
    std::string line;
    while (std::getline(file, line))
        bufferStream << line;
    
    return bufferStream.str();
}

void ncc::util::writeFile(std::string name, std::string contents) {
    std::ofstream file(name, std::ios::out | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error(std::string("writeFile(\"") + name + "\", ...) failed: unable to open stream");
    
    file << contents;
    file.close();
}
