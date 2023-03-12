//
// FullPrintRaxFixture.cpp
// Nathanael Epps
//

#include "FullPrintRaxFixture.hpp"
#include "Controller.hpp"
#include "Util.hpp"
#include "io.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace ncc::test;

FullPrintRaxFixture::FullPrintRaxFixture() : Fixture("FullPrintRax") {
    if (system(nullptr) == 0)
        throw std::runtime_error(
            "Cannot create FullPrintRaxFixture, \"system\" function unavailable");
}

std::shared_ptr<FullPrintRaxFixture> FullPrintRaxFixture::factory() {
    return std::shared_ptr<FullPrintRaxFixture>(new FullPrintRaxFixture);
}

bool FullPrintRaxFixture::run(std::string input, std::optional<std::string> optOutput) {
    static const std::string prompt = "*** ";

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
    std::cout << prompt << "Running ncc...\n";
    ncc::io::init(inputStream, asmStream);
    ncc::Controller ctrl;
    ctrl.run(ncc::ScaffoldType::PRINT_RAX);
    asmStream.close();
    if (!std::filesystem::exists("tmp.s")) {
        std::cerr << "Unable to create assembly file\n";
        return false;
    }
    FileDeleter asmGuard("tmp.s");

    // Turn assembled file into an executable
    std::cout << prompt << "Assembling with gcc...\n";
    system("gcc tmp.s -o Tmp");
    if (!std::filesystem::exists("Tmp"))
        throw std::runtime_error("Invoking gcc failed, output program does not exist");
    FileDeleter exeGuard("Tmp");

    // Run program and retrieve output
    std::cout << prompt << "Running executable...\n";
    system("./Tmp &> tmp-output.txt");
    if (!std::filesystem::exists("tmp-output.txt"))
        throw std::runtime_error("Error running executable, output text file does not exist");
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

types::inputOutput_t FullPrintRaxFixture::getInputOutput() const {
    return {{"5", "5"},        {"1+2", "3"},       {"123 + 456", "579"}, {"5 - 4", "1"},
            {"10 - 15", "-5"}, {"4 + 5 - 3", "6"}, {"2 * 4", "8"}};
}
