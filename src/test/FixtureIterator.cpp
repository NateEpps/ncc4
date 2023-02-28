//
// FixtureIterator.cpp
// Nathanael Epps
//

#include "FixtureIterator.hpp"
#include "Fixture.hpp"
#include <iostream>
#include <stdexcept>
using namespace ncc::test;

#warning This class works with vector's, but doesn't play nice with maps

FixtureIterator::FixtureIterator(std::weak_ptr<Fixture> wp, std::vector<std::string>::iterator itr)
    : inputOnly(true), parentFixture(wp), inputItr(itr) {}

FixtureIterator::FixtureIterator(std::weak_ptr<Fixture> wp,
                                 std::map<std::string, std::string>::iterator itr)
    : inputOnly(false), parentFixture(wp), inputOutputItr(itr) {}

// prefix
FixtureIterator& FixtureIterator::operator++() {
    if (inputOnly)
        inputItr++;
    else
        inputOutputItr++;

    return *this;
}

// postfix
FixtureIterator FixtureIterator::operator++(int) {
    if (inputOnly)
        inputItr++;
    else
        inputOutputItr++;

    return *this;
}

bool FixtureIterator::operator==(const FixtureIterator& that) {
    if (inputOnly != that.inputOnly)
        throw std::runtime_error("Cannot compare input-only and IO fixture iterators");

    if (inputOnly)
        return inputItr == that.inputItr;
    else
        return inputOutputItr == that.inputOutputItr;
}

bool FixtureIterator::operator!=(const FixtureIterator& that) { return !(*this == that); }

TestResult FixtureIterator::runTest() {
    try {
        bool b;
        if (inputOnly)
            b = parentFixture.lock()->run(*inputItr);
        else
            b = parentFixture.lock()->run(inputOutputItr->first, inputOutputItr->second);

        if (b)
            return TestResult::Success;
        else
            return TestResult::Failure;
    } catch (std::exception& ex) {
        std::cerr << "FixtureIterator::runTest(): Caught exception \"" << ex.what() << "\"\n";
        return TestResult::Exception;
    }
}
