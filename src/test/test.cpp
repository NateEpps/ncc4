//
// test.cpp
// Nathanael Epps
//

#include "System.hpp"
#include <chrono>
#include <iostream>

int main(int argc, const char** argv) {
    ncc::test::System system;

    auto start = std::chrono::system_clock::now();
    int rval = system.run(ncc::util::bundle(argc, argv));
    auto end = std::chrono::system_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\nTest time " << ms << "ms\n";
    return rval;
}
