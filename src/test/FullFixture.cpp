//
// FullFixture.cpp
// Nathanael Epps
//

#include "FullFixture.hpp"
#include "Controller.hpp"
#include "Util.hpp"
#include "io.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace ncc::test;

FullFixture::FullFixture(std::string str) : Fixture(str) {}

bool FullFixture::run(std::string input, std::optional<std::string> optOutput) {
    std::string output = optOutput.value_or("");

    std::cout << "Input:\n" << testFormat(input) << "\n";
    std::cout << "Expected output:\n" << testFormat(output) << "\n";

    // Create input and assembly file streams
    std::stringstream inputStream(input);
    std::ofstream asmStream;
    asmStream.open("tmp.s", std::ios::out | std::ios::trunc);
    if (!asmStream.is_open()) {
        std::cerr << "Unable to open assembly file stream\n";
        return false;
    }

    // Run compiler and close output stream
    std::cout << PROMPT << "Running ncc...\n";
    ncc::io::init(inputStream, asmStream);
    ncc::Controller ctrl;
    ctrl.run(this->getScaffoldType());
    asmStream.close();
    if (!std::filesystem::exists("tmp.s")) {
        std::cerr << "Unable to create assembly file\n";
        return false;
    }
    FileDeleter asmGuard("tmp.s");

    // Turn assembled file into an executable
    std::cout << PROMPT << "Assembling with gcc...\n";
    system("gcc tmp.s -o Tmp");
    if (!std::filesystem::exists("Tmp")) {
        std::cerr << "Invoking gcc failed, output program does not exist\n";
        return false;
    }
    FileDeleter exeGuard("Tmp");

    // Run program and retrieve output
    std::cout << PROMPT << "Running executable...\n";
    system("./Tmp &> tmp-output.txt");
    if (!std::filesystem::exists("tmp-output.txt")) {
        std::cerr << "Error running executable, output text file does not exist\n";
        return false;
    }
    FileDeleter txtGuard("tmp-output.txt");

    std::string realOutput = ncc::util::readFile("tmp-output.txt");

    // Report & compare
    std::cout << "Output:\n" << testFormat(realOutput) << "\n";

    // go char-by-char based on expected. Real output might
    // have newlines, control characters, etc
    bool success = true;
    for (int x = 0; x < output.size(); x++) {
        if (output[x] != realOutput[x]) {
            success = false;
            break;
        }
    }

    if (!success) {
        asmGuard.disable();
        exeGuard.disable();
        txtGuard.disable();
    }

    std::cout << "\n" << (success ? "PASS" : "FAIL") << "\n";
    return success;
}
