/**
 * @file
 * @author Nathanael Epps
 *
 * Expression generator tool
 */

#include <iostream>
#include <sstream>
#include <stdexcept>

template <class T>
T convert(std::string str) {
    std::stringstream ss(str);
    T data;
    if (ss >> data)
        return data;
    else
        throw std::runtime_error("Conversion error for string \"" + str + "\"");
}

int main2(int argc, const char** argv) {
    if (argc < 3)
        throw std::runtime_error("Not enough args");
    
    int seed = convert<int>(argv[1]);
    int iter = convert<int>(argv[2]);
    
    std::cout << "Seed:        " << seed << "\n";
    std::cout << "Iterations:  " << iter << "\n";
    
    std::cout << "\nNow, to actually implement the thing...\n";
    
    return 0;
}

int main(int argc, const char** argv) {
    try {
        return main2(argc, argv);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
    } catch (...) {
        std::cerr << "Caught unknown exception\n";
    }
    
    std::cerr << "Usage:\n\t" << argv[0] << " (seed) (iterations)\n";
    return -1;
}
