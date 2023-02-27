//
// BasicFixture.cpp
// Nathanael Epps
//

#include "BasicFixture.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <iostream>
#include <sstream>

using namespace ncc::test;

BasicFixture::BasicFixture() : Fixture("Basic") {}

std::shared_ptr<BasicFixture> BasicFixture::factory() {
    return std::shared_ptr<BasicFixture>(new BasicFixture);
}

bool BasicFixture::run(std::string input, std::optional<std::string>) {
    std::cout << "Input:\n" << testFormat(input) << "\n";

    std::stringstream inputStream(input);
    std::stringstream outputStream;

    ncc::io::init(inputStream, outputStream, false);
    ncc::Controller ctrl;
    ctrl.run(ncc::ScaffoldType::NONE);

    std::cout << "Output:\n" << testFormat(outputStream.str()) << "\n";
    return true;
}

std::vector<std::string> BasicFixture::getInput() const {
    return {"5",  "5a",   "    5", "90210",           "123abc456",
            "-5", "-456", "+",     "\"Hello world\"", "rand()"};
}
