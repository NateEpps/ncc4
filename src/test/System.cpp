//
// System.cpp
// Nathanael Epps
//

#include "System.hpp"
#include "BasicFixture.hpp"
#include "ErrorFixture.hpp"
#include "FullPrintRaxFixture.hpp"
#include <iostream>
#include <thread>

using namespace ncc::test;

static const std::string separator =
    "--------------------------------------------------------------------";

static void printHeader(std::string name) {
    static const char block = '@';
    std::string header =
        std::string(2, block) + " Test Fixture \"" + name + "\" " + std::string(2, block);
    std::string buf(header.size(), block);

    std::cout << buf << "\n" << header << "\n" << buf << "\n\n";
}

System::System() {
    add<BasicFixture>();
    add<ErrorFixture>();
    add<FullPrintRaxFixture>();
}

int System::run(args_t cmd) {
    // for each fixture...
    for (std::shared_ptr<Fixture> fixture : testFixtures) {
        printHeader(fixture->name);

        FixtureIterator itr = fixture->begin();
        const FixtureIterator end = fixture->end();

        while (itr != end) {
            TestResult res = itr.runTest();

            if (res != TestResult::Success) {
                if (res == TestResult::Failure)
                    std::cerr << "*** Test Failed ***\n";
                else if (res == TestResult::Exception)
                    std::cerr << "*** Test threw unexpected exception ***\n";

                return EXIT_FAILURE;
            }

            std::cout << separator << "\n";
            itr++;
        }
    }

    return EXIT_SUCCESS;
}
