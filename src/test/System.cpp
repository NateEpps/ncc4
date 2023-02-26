//
// System.cpp
// Nathanael Epps
//

#include "System.hpp"
#include "BasicFixture.hpp"
#include "ErrorFixture.hpp"
#include <iostream>

using namespace ncc::test;

static const std::string separator =
    "--------------------------------------------------------------------";

System::System() {
    add<BasicFixture>();
    add<ErrorFixture>();
}

static void printHeader(std::string name) {
    static const char block = '@';
    std::string header =
        std::string(2, block) + " Test Fixture \"" + name + "\" " + std::string(2, block);
    std::string buf(header.size(), block);

    std::cout << buf << "\n" << header << "\n" << buf << "\n\n";
}

#warning Todo- error handling
int System::run(args_t cmd) {
    // for each fixture...
    for (std::shared_ptr<Fixture> fixture : testFixtures) {
        printHeader(fixture->name);
        auto inputs = fixture->getInput();
        auto inputOutputs = fixture->getInputOutput();

        // run each test case
        if (!inputs.empty()) {
            for (auto input : inputs) {
                TestResult res = runImpl(fixture, input);

                if (res != TestResult::Success) {
                    if (res == TestResult::Failure)
                        std::cerr << "*** Test Failed ***\n";
                    else if (res == TestResult::Exception)
                        std::cerr << "*** Test threw unexpected exception ***\n";

                    return EXIT_FAILURE;
                }

                std::cout << separator << "\n";
            }
        } else if (!inputOutputs.empty()) {
            std::cerr << cmd[0] << ": IO tests not yet supported\n";
            return EXIT_FAILURE;

            /* for (auto [input, output] : inputOutputs) {
                TestResult res = runImpl(fixture, input, output);
                //...
                std::cout << separator << "\n";
            } */
        } else {
            std::cerr << cmd[0] << ": Test fixture \"" << fixture->name
                      << "\" does not provide IO data\n";
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

System::TestResult System::runImpl(std::shared_ptr<Fixture> fixture, std::string input) {
    try {
        if (fixture->run(input))
            return TestResult::Success;
        else
            return TestResult::Failure;
    } catch (...) {
        return TestResult::Exception;
    }
}

System::TestResult System::runImpl(std::shared_ptr<Fixture> fixture, std::string input,
                                   std::string output) {
    try {
        if (fixture->run(input, output))
            return TestResult::Success;
        else
            return TestResult::Failure;
    } catch (...) {
        return TestResult::Exception;
    }
}
