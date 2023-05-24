//
// ErrorFixture.cpp
// Nathanael Epps
//

#include "ErrorFixture.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <iostream>
#include <sstream>
using namespace ncc::test;

ErrorFixture::ErrorFixture() : Fixture("Error") {}

std::shared_ptr<ErrorFixture> ErrorFixture::factory() {
    return std::shared_ptr<ErrorFixture>(new ErrorFixture);
}

bool ErrorFixture::run(std::string input, std::optional<std::string>) {
    std::cout << "Input:\n" << testFormat(input) << "\n";

    std::stringstream inputStream(input);
    std::stringstream outputStream;
    ncc::io::init(inputStream, outputStream, false);

    ncc::Controller ctrl;
    bool success = false;
    std::string exMssg;

    try {
        ctrl.run(ncc::ScaffoldType::NONE);
    } catch (std::exception& ex) {
        exMssg = ex.what();
        success = true;
    }

    std::cout << "Output:\n" << testFormat(outputStream.str()) << "\n";

    std::cout << "\nError message: " << (exMssg.empty() ? "--" : exMssg) << "\n";

    return success;
}

types::input_t ErrorFixture::getInput() const {
    /// @todo Unary minus is here, and unary plus is in BasicFixture, see issue #3
    return {"Error", "-", "-a", "2 + +",   "2 * (3 + 4",   "(2 *",
            "(2",    ")", "\"", "\"Hello", "variableName", "var = 10;"};
}
