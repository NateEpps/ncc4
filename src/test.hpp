//
// test.hpp
// Nathanael Epps
//

#ifndef TEST_HPP
#define TEST_HPP

#include "Controller.hpp"
#include "io.hpp"
#include "Util.hpp"
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

static std::vector<std::pair<std::string, std::function<void()>>> testVec;

struct TestAdder {
    TestAdder(std::string name, std::function<void()> test) {
        testVec.push_back(std::make_pair(name, test));
    }
};

static void MultiLineOutput(std::stringstream& ss) {
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty())
            break;
        std::cout << ">>> " << line << "\n";
    }
}

static void TestCase(std::string name, std::string in) {
    std::stringstream input, output;
    input << in;
    ncc::io::init(input, output, false);
    ncc::Controller ctrl;
    ctrl.run(ncc::ScaffoldType::NONE);
    std::cout << "Test Case \"" << name << "\"\n";
    std::cout << "Input:\n>>> " << in << "\n";
    std::cout << "Output:\n";

    MultiLineOutput(output);
    std::cout << "\n";
}

#define TEST_CASE(name, in) void testCase##name () { TestCase(#name, in); } TestAdder name (#name, &testCase##name)

static void ErrorCase(std::string name, std::string in) {
    std::stringstream input, output;
    input << in;
    ncc::io::init(input, output, false);
    ncc::Controller ctrl;
    try {
        ctrl.run(ncc::ScaffoldType::NONE);
    }
    catch (std::exception& ex) {
        std::cout << "Error Case \"" << name << "\"\n";
        std::cout << "Input:\n>>> " << in << "\n";
        std::cout << "Error Output:\n";
        MultiLineOutput(output);
        std::cout << "\n";
        return;
    }
    throw std::runtime_error("Test " + name + " was expected to fail, and didn't");
}

#define ERROR_CASE(name, in) void testCase##name () { ErrorCase(#name, in); } TestAdder name (#name, &testCase##name)

static bool existsInCwd(std::string file) {
    return std::filesystem::exists(std::filesystem::current_path().concat(std::string("/") + file));
}

static void TestCaseWithOutput(std::string name, std::string in, std::string out) {
    std::cout << "Assembled Test Case \"" << name << "\"\n";

    std::stringstream input;
    input << in;

    // Create stream for assembly file
    std::ofstream asmStream;
    asmStream.open("tmp.s", std::ios::out|std::ios::trunc);
    if (!asmStream.is_open())
        throw std::runtime_error("Test \"" + name + "\" unable to create assembly file");

    // Run Compiler
    std::cout << "Compiling...\n";
    ncc::io::init(input, asmStream, true);
    ncc::Controller ctrl;
    ctrl.run();
    asmStream.close();

    // Assemble output to executable
    std::string assembleCommand = "gcc tmp.s -o Tmp";
    std::cout << "Assembling... [" << assembleCommand << "]\n";
    std::cout << std::flush;
    system(assembleCommand.c_str());
    if (!existsInCwd("Tmp"))
        throw std::runtime_error("Error assembling executable");

    // Run executable
    std::string runCommand = "./Tmp > tmp_output.txt";
    std::cout << "Running... [" << runCommand << "]\n";
    std::cout << std::flush;
    system(runCommand.c_str());
    if (!existsInCwd("tmp_output.txt"))
        throw std::runtime_error("Error running generated executable");

    std::cout << "Input:\n>>> " << in << "\n";
    std::cout << "Output:\n";

    // Grab output
    std::string finalResult = ncc::util::readFile("tmp_output.txt");

    std::stringstream finalResultStream(finalResult);
    MultiLineOutput(finalResultStream);

    // Check output
    for (int x = 0; x < out.size(); x++) {
        if (out.at(x) != finalResult.at(x))
            throw std::runtime_error("Actual output did not match expected (expected: \"" + out + "\")");
    }

    // Cleanup
    std::cout << "Cleaning up...\n";
    std::filesystem::remove("tmp.s");
    std::filesystem::remove("Tmp");
    std::filesystem::remove("tmp_output.txt");
    std::cout << "\n";
}

#define TEST_CASE_WITH_OUTPUT(name, in, out) void testCase##name () { TestCaseWithOutput(#name, in, out); } TestAdder name (#name, &testCase##name)

static bool ExpgenTest() {
    /// @todo Should look into `std::filesystem::status(...)` at some point, to check executable status

    if (!existsInCwd(EXPGEN_NAME)) {
        std::cerr << EXPGEN_NAME << " program file does not exist in CWD\n";
        return false;
    }

    std::cout << "Expgen test...\n";
    std::cout << "==============\n\n";
    
#warning Todo- implement expgen test...

    return true;
}

static bool RunTests() {
    int count = 0;

    for (const auto& pair : testVec) {
        try {
            std::cout << (count + 1) << ") ";
            pair.second();
            count++;
        }
        catch (std::exception& ex) {
            std::cerr << "Test \"" << pair.first << "\" threw an exception: " << ex.what() << "\n";
            break;
        }
    }

    std::cout << "Passed " << count << " / " << testVec.size() << " tests\n";

    return count == testVec.size();
}

void help(std::string command) {
    std::cout << "Usage:\n\t" << command << " [option]\n\n";
    
    std::cout << " -h / --help           Bring up this help info\n";
    std::cout << " -v / --version        Exit after printing version info\n";
    std::cout << " (no option)           Run the test suite\n";
}

#endif
