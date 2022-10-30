//
// test.hpp
// Nathanael Epps
//

#ifndef TEST_HPP
#define TEST_HPP

#include "Controller.hpp"
#include "io.hpp"
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
    
    std::ofstream asmStream;
    asmStream.open("tmp.s", std::ios::out|std::ios::trunc);
    if (!asmStream.is_open())
        throw std::runtime_error("Test \"" + name + "\" unable to create assembly file");
    
    std::cout << "Compiling...\n";
    ncc::io::init(input, asmStream, true);
    ncc::Controller ctrl;
    ctrl.run();
    asmStream.close();
    
    std::string assembleCommand = "gcc tmp.s -o Tmp";
    std::cout << "Assembling... [" << assembleCommand << "]\n";
    system(assembleCommand.c_str());
    if (!existsInCwd("Tmp"))
        throw std::runtime_error("Error assembling executable");
    
    std::string runCommand = "./Tmp > tmp_output.txt";
    std::cout << "Running... [" << runCommand << "]\n";
    system(runCommand.c_str());
    if (!existsInCwd("tmp_output.txt"))
        throw std::runtime_error("Error running generated executable");
    
    std::ifstream outputFile;
    outputFile.open("tmp_output.txt");
    if (!outputFile.is_open())
        throw std::runtime_error("Error opening tmp_output.txt stream");
    
    std::stringstream outputStringStream;
    std::string line;
    while (std::getline(outputFile, line))
        outputStringStream << line;
    
    std::cout << "Input:\n>>> " << in << "\n";
    std::cout << "Output:\n";
    
    std::string finalResult = outputStringStream.str();
    MultiLineOutput(outputStringStream);
    
    for (int x = 0; x < out.size(); x++) {
        if (out.at(x) != finalResult.at(x))
            throw std::runtime_error("Actual output did not match expected (\"" + out + "\")");
    }
    
    std::cout << "Cleaning up...\n";
    std::filesystem::remove("tmp.s");
    std::filesystem::remove("Tmp");
    std::filesystem::remove("tmp_output.txt");
    std::cout << "\n";
}

#define TEST_CASE_WITH_OUTPUT(name, in, out) void testCase##name () { TestCaseWithOutput(#name, in, out); } TestAdder name (#name, &testCase##name)

static void RunTests() {
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
}

#endif
