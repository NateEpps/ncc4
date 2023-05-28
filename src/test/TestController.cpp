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
    static constexpr char block = '@';
    std::string header =
        std::string(2, block) + " Test Fixture \"" + name + "\" " + std::string(2, block);
    std::string buf(header.size(), block);

    std::cout << buf << "\n" << header << "\n" << buf << "\n\n";
}

// clang-format off
static void printHelp(const std::string& cmd0) {
    std::cout << "Usage:\n";
    std::cout << "      " << cmd0 << " ...\n\n";
    std::cout << "  --list / -l                          List all test fixtures\n";
    std::cout << "  --help / -h                          Bring up this help info\n";
    std::cout << "  (Specific fixture) [Test number]     Run just the named fixture. Optional [Test number] param can be used to indicate a specific test\n";
    std::cout << "  (Nothing)                            Run the full test suite-- all test fixtures\n";
}
// clang-format on

TestController::TestController() : listFlag(false), helpFlag(false) {
    add<BasicFixture>();
    add<ErrorFixture>();
    add<FullPrintRaxFixture>();
    add<ExpgenFixture>();
    add<FullMainFixture>();
}

int TestController::run(args_t cmdLineArgs) {
    // check args
    if (!processArgs(cmdLineArgs)) {
        printHelp(cmdLineArgs[0]);
        return EXIT_FAILURE;
    }

    // check flags
    if (helpFlag) {
        printHelp(cmdLineArgs[0]);
        return EXIT_SUCCESS;
    }

    if (listFlag) {
        for (std::shared_ptr<Fixture> fixture : testFixtures)
            std::cout << fixture->name << "\n";

        return EXIT_SUCCESS;
    }

    // Otherwise, run things...
    int status = EXIT_SUCCESS;
    auto start = std::chrono::system_clock::now();

    if (specificFixture.has_value()) {
        if (specificIndex.has_value()) { // Runing just one specific fixture-test pair
            printHeader(specificFixture.value()->name);

            FixtureIterator itr = specificFixture.value()->begin();
            itr += specificIndex.value();

            if (!runTest(itr, specificIndex.value()))
                status = EXIT_FAILURE;
        } else {
            if (!runFixture(specificFixture.value())) // Running a specific fixture
                status = EXIT_FAILURE;
        }
    } else {
        for (std::shared_ptr<Fixture> fixture : testFixtures) { // Run everything
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

    int index = 0;
    while (itr != end) {
        if (!runTest(itr, index))
            return false;

        index++;
        itr++;
    }

    return true;
}

bool TestController::runTest(FixtureIterator& itr, int index) {
    std::cout << index << ") ";
    TestResult res = itr.runTest();
    bool status = true;

    if (res != TestResult::Success) {
        if (res == TestResult::Failure)
            std::cerr << "*** Test Failed ***\n";
        else if (res == TestResult::Exception)
            std::cerr << "*** Test threw unexpected exception ***\n";

        status = false;
    }

    std::cout << separator << "\n";
    return status;
}

bool TestController::processArgs(args_t& args) {
    helpFlag = (ncc::util::getOpt(args, "--help", "-h") != args.end());
    listFlag = (ncc::util::getOpt(args, "--list", "-l") != args.end());

    // A flag was set, bail out here
    if (helpFlag || listFlag)
        return true;

    // Otherwise, see if we have a specifically named test
    auto params = ncc::util::getParameters(args);
    if (params.empty())
        return true; // no specific test. Bail out here

    // If params aren't empty, we should have at least a fixture name
    std::string targetName = params[0];
    auto itr =
        std::find_if(testFixtures.begin(), testFixtures.end(),
                     [&](std::shared_ptr<Fixture> fixture) { return fixture->name == targetName; });

    if (itr == testFixtures.end()) {
        std::cerr << "Error: Unknown fixture \"" << targetName << "\"\n";
        return false;
    }

    specificFixture = *itr;

    // See if we've been passed a test index as well
    if (params.size() >= 2) {
        std::string maybeIndex = params[1];
        std::stringstream ss(maybeIndex);
        int extracted;

        if (!(ss >> extracted)) {
            std::cerr << "Error: Could not convert \"" << maybeIndex << "\" to an int\n";
            return false;
        }

        specificIndex = extracted;
    }

    return true;
}
