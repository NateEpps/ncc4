//
// ExpgenFixture.cpp
// Nathanael Epps
//

#include "ExpgenFixture.hpp"
#include "Util.hpp"
#include <iostream>
using namespace ncc::test;

template <class T>
static void printMap(std::map<T, T> theMap, std::string header) {
    std::cerr << header << "\n";
    std::cerr << "(" << theMap.size() << ") {\n";
    for (const auto& [left, right] : theMap)
        std::cerr << "   {" << left << ", " << right << "}\n";
    std::cerr << "}\n";
}

static std::map<std::string, std::string> convertToIO(std::map<int, int> argsMap) {
    printMap(argsMap, "Args:");
    std::map<std::string, std::string> ioMap;
    for (auto [seed, iter] : argsMap) {
        std::string input = std::to_string(seed) + " " + std::to_string(iter);
        std::string output = std::to_string(seed);
        ioMap[input] = output;
    }

    printMap(ioMap, "IO:");

    return ioMap;
}

ExpgenFixture::ExpgenFixture() : Fixture("Expgen") {}

std::shared_ptr<ExpgenFixture> ExpgenFixture::factory() {
    return std::shared_ptr<ExpgenFixture>(new ExpgenFixture);
}

bool ExpgenFixture::run(std::string input, std::optional<std::string> optOutput) {
    std::string seed = input.substr(0, input.find(' '));
    std::string iter = input.substr(input.find(' ') + 1);
    std::string output = optOutput.value_or("");

    std::cout << "Seed:         " << seed << "\n";
    std::cout << "Iterations:   " << iter << "\n";

    std::cout << "Expected output:\n" << testFormat(output) << "\n";

    std::cout << "...\n";

    return true;
}

#warning Maps don't allow duplicate entries. Will need to refactor with multimap

std::map<std::string, std::string> ExpgenFixture::getInputOutput() const {
    std::map<int, int> args = {{5, 0},
                               {5, 1},
                               {5, 1},
                               {10, 2},
                               {0, 2},
                               {5, 3},
                               {5, 4},
                               {5, 5},
                               {8, 8},
                               {ncc::util::randInt(-20, 20), 5},
                               {ncc::util::randInt(0, 20), 5},
                               {ncc::util::randInt(0, 20), 5},
                               {10, 10}};

    printMap(args, "original: ");

    return convertToIO(args);
}
