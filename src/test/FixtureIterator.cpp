//
// FixtureIterator.cpp
// Nathanael Epps
//

#include "FixtureIterator.hpp"
#include "Fixture.hpp"
#include <iostream>
#include <stdexcept>
using namespace ncc::test;

/*static*/ std::map<std::string, std::any> FixtureIterator::storedContainers;

FixtureIterator::FixtureIterator(std::weak_ptr<Fixture> wp, Position pos)
    : inputOnly(isInputOnly(wp)), parentFixture(wp) {

    std::shared_ptr<Fixture> parent = parentFixture.lock();

    if (inputOnly) {
        if (storedContainers.find(parent->name) == storedContainers.end())
            storedContainers[parent->name] = std::make_any<types::input_t>(parent->getInput());

        types::input_t* container =
            std::any_cast<types::input_t>(&storedContainers.at(parent->name));

        if (pos == FixtureIterator::Begin)
            inputItr = container->begin();
        else if (pos == FixtureIterator::End)
            inputItr = container->end();
    } else {
        if (storedContainers.find(parent->name) == storedContainers.end())
            storedContainers[parent->name] =
                std::make_any<types::inputOutput_t>(parent->getInputOutput());

        types::inputOutput_t* container =
            std::any_cast<types::inputOutput_t>(&storedContainers.at(parent->name));

        if (pos == FixtureIterator::Begin)
            inputOutputItr = container->begin();
        else if (pos == FixtureIterator::End)
            inputOutputItr = container->end();
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

// postfix - dummy parameter
FixtureIterator FixtureIterator::operator++(int) {
    ++(*this);
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

/*static*/ bool FixtureIterator::isInputOnly(std::weak_ptr<Fixture> wpf) {
    return !wpf.lock()->getInput().empty();
}
