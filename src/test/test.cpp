//
// test.cpp
// Nathanael Epps
//

#include "TestController.hpp"
#include <chrono>
#include <iostream>

int main(int argc, const char** argv) {
    if (system(nullptr) == 0) {
        std::cerr << "Error: \"system\" function unavailable\n";
        return EXIT_FAILURE;
    }

    ncc::test::TestController ctrl;
    return ctrl.run(ncc::util::bundle(argc, argv));
}
