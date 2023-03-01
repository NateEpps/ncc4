//
// Fixture.cpp
// Nathanael Epps
//

#include "Fixture.hpp"
#include <iostream>

using namespace ncc::test;

Fixture::Fixture(std::string n) : name(n) {}

std::vector<std::string> Fixture::getInput() const { return {}; }

std::map<std::string, std::string> Fixture::getInputOutput() const { return {}; }

// clang-format off
FixtureIterator Fixture::begin() {
    return FixtureIterator(shared_from_this(), FixtureIterator::Begin);
}

FixtureIterator Fixture::end() {
    return FixtureIterator(shared_from_this(), FixtureIterator::End);
}
// clang-format on

std::string Fixture::testFormat(std::string input) {
    static const std::string prompt = ">> ";

    if (input.empty())
        return input;

    // remove newlines from end
    while (input.back() == '\n')
        input = input.substr(0, input.size() - 1);

    // one-liner check
    if (input.find('\n') == std::string::npos)
        return prompt + input;

    // time to bring out the big guns. Tokenize input
    size_t index = input.find('\n');
    std::vector<std::string> lines;
    while (index != std::string::npos) {
        std::string curLine = input.substr(0, index);
        input = input.substr(index + 1);
        lines.push_back(curLine);

        index = input.find('\n');
    }
    lines.push_back(input);
    input = "";

    // recombine with formatting
    std::string output;
    for (auto line : lines)
        output += prompt + line + "\n";

    // chop off last newline in multi-line case if we need to
    if (output.back() == '\n')
        output = output.substr(0, output.size() - 1);

    return output;
}
