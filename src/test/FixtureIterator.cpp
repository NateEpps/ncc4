//
// FixtureIterator.cpp
// Nathanael Epps
//

#include "FixtureIterator.hpp"
#include "Fixture.hpp"
#include <iostream>
#include <stdexcept>
using namespace ncc::test;

static std::map<std::string, types::input_t> inputRecords;
static std::map<std::string, types::inputOutput_t> inputOutputRecords;

FixtureIterator::FixtureIterator(std::weak_ptr<Fixture> wp, Position pos)
    : inputOnly(!wp.lock()->getInput().empty()), parentFixture(wp) {

    std::shared_ptr<Fixture> parent = parentFixture.lock();
    if (inputOnly) {
        if (inputRecords.find(parent->name) == inputRecords.end())
            inputRecords[parent->name] = parent->getInput();

        if (pos == FixtureIterator::Begin)
            inputItr = inputRecords.at(parent->name).begin();
        else if (pos == FixtureIterator::End)
            inputItr = inputRecords.at(parent->name).end();
    } else {
        if (inputOutputRecords.find(parent->name) == inputOutputRecords.end())
            inputOutputRecords[parent->name] = parent->getInputOutput();

        if (pos == FixtureIterator::Begin)
            inputOutputItr = inputOutputRecords.at(parent->name).begin();
        else if (pos == FixtureIterator::End)
            inputOutputItr = inputOutputRecords.at(parent->name).end();
    }
}

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

FixtureIterator& FixtureIterator::operator+=(int i) {
    for (int x = 0; x < i; x++)
        (*this)++;

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
        auto parent = parentFixture.lock();

        if (inputOnly)
            b = parent->run(*inputItr);
        else
            b = parent->run(inputOutputItr->first, inputOutputItr->second);

        if (b)
            return TestResult::Success;
        else
            return TestResult::Failure;
    } catch (std::exception& ex) {
        std::cerr << "FixtureIterator::runTest(): Caught exception \"" << ex.what() << "\"\n";
        return TestResult::Exception;
    }
}
