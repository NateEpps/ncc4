//
// FullPrintRaxFixture.cpp
// Nathanael Epps
//

#include "FullPrintRaxFixture.hpp"
using namespace ncc::test;

FullPrintRaxFixture::FullPrintRaxFixture() : FullFixture("FullPrintRax") {}

std::shared_ptr<FullPrintRaxFixture> FullPrintRaxFixture::factory() {
    return std::shared_ptr<FullPrintRaxFixture>(new FullPrintRaxFixture);
}

ncc::ScaffoldType FullPrintRaxFixture::getScaffoldType() const {
    return ncc::ScaffoldType::PRINT_RAX;
}

types::inputOutput_t FullPrintRaxFixture::getInputOutput() const {
    return {{"5", "5"},        {"1+2", "3"},       {"123 + 456", "579"}, {"5 - 4", "1"},
            {"10 - 15", "-5"}, {"4 + 5 - 3", "6"}, {"2 * 4", "8"}};
}
