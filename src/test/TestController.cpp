//
// TestController.cpp
// Nathanael Epps
//

#include "TestController.hpp"
#include "BasicFixture.hpp"
#include "ErrorFixture.hpp"
#include "ExpgenFixture.hpp"
#include "FullMainFixture.hpp"
#include "FullPrintRaxFixture.hpp"
#include <algorithm>
#include <chrono>
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

TestController::TestController() : listFlag(false), helpFlag(false) {
    add<BasicFixture>();
    add<ErrorFixture>();
    add<FullPrintRaxFixture>();
    add<ExpgenFixture>();
    add<FullMainFixture>();
}

int TestController::run(args_t cmd) {
    // check args
    if (!processArgs(cmd))
        return EXIT_FAILURE;

    // check flags
    if (helpFlag) {
        std::cout << "Usage:\n";
        std::cout << "      " << cmd[0] << " [option, specific fixture, OR nothing]\n\n";
        std::cout << "  --list / -l          List all test fixtures\n";
        std::cout << "  --help / -h          Bring up this help info\n";
        std::cout << "  (Specific fixture)   Run just the named fixture\n";
        std::cout << "  (Nothing)            Run the full test suite\n";
        return EXIT_SUCCESS;
    }

    if (listFlag) {
        for (std::shared_ptr<Fixture> fixture : testFixtures)
            std::cout << fixture->name << "\n";

        return EXIT_SUCCESS;
    }

    // Otherwise, run things
    int status = EXIT_SUCCESS;
    auto start = std::chrono::system_clock::now();

    if (specificFixture.has_value()) {
        if (!runFixture(specificFixture.value()))
            status = EXIT_FAILURE;
    } else {
        for (std::shared_ptr<Fixture> fixture : testFixtures) {
            if (!runFixture(fixture)) {
                status = EXIT_FAILURE;
                break;
            }
        }
    }

    auto end = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\nTest time " << ms << "ms\n";
    std::cout << ncc::util::getFormattedDateTime() << "\n";
    return status;
}

bool TestController::runFixture(std::shared_ptr<Fixture> fixture) {
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

            return false;
        }

        std::cout << separator << "\n";
        itr++;
    }

    return true;
}

bool TestController::processArgs(args_t& args) {
    if (ncc::util::getOpt(args, "--help", "-h") != args.end())
        helpFlag = true;

    if (ncc::util::getOpt(args, "--list", "-l") != args.end())
        listFlag = true;

    // A flag was set, bail out here
    if (helpFlag || listFlag)
        return true;

    // Otherwise, see if we have a specifically named test
    auto params = ncc::util::getParameters(args);
    if (params.empty())
        return true;

    std::string targetName = params[0];
    auto itr =
        std::find_if(testFixtures.begin(), testFixtures.end(),
                     [&](std::shared_ptr<Fixture> fixture) { return fixture->name == targetName; });

    if (itr == testFixtures.end()) {
        std::cerr << "Error: Unknown fixture \"" << targetName << "\"\n";
        return false;
    }

    specificFixture = *itr;
    return true;
}
