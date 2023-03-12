//
// ExpgenFixture.cpp
// Nathanael Epps
//

#include "ExpgenFixture.hpp"
#include "Util.hpp"
#include <iostream>
using namespace ncc::test;

static types::inputOutput_t convertToIO(std::vector<std::pair<int, int>> argsData) {
    types::inputOutput_t ioData;
    for (auto argPair : argsData) {
        std::string inputData =
            std::to_string(argPair.first) + " " + std::to_string(argPair.second);
        std::string outputData = std::to_string(argPair.first);
        ioData.emplace_back(std::make_pair(inputData, outputData));
    }

    return ioData;
}

ExpgenFixture::ExpgenFixture() : Fixture("Expgen") {}

std::shared_ptr<ExpgenFixture> ExpgenFixture::factory() {
    return std::shared_ptr<ExpgenFixture>(new ExpgenFixture);
}

bool ExpgenFixture::run(std::string input, std::optional<std::string> optOutput) {
    std::string seed = input.substr(0, input.find(' '));
    std::string iter = input.substr(input.find(' ') + 1);
    std::string output = optOutput.value_or("");

    if (seed != output) {
        std::cerr << "Seed and output must match (given \"" << seed << "\" and \"" << output
                  << "\")\n";
        return false;
    }

    std::cout << "Seed:         " << seed << "\n";
    std::cout << "Iterations:   " << iter << "\n";

    std::cout << "Expected output:\n" << testFormat(output) << "\n";

    std::cout << "...\n";

    return true;
}

types::inputOutput_t ExpgenFixture::getInputOutput() const {
    std::vector<std::pair<int, int>> args = {{5, 0},
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

    return convertToIO(args);
}
