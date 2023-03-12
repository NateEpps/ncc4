//
// test.cpp
// Nathanael Epps
//

#include "TestController.hpp"
#include <chrono>
#include <iostream>

int main(int argc, const char** argv) {
    ncc::test::TestController ctrl;

    auto start = std::chrono::system_clock::now();

    int rval = ctrl.run(ncc::util::bundle(argc, argv));

    auto end = std::chrono::system_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\nTest time " << ms << "ms\n";
    return rval;
}
