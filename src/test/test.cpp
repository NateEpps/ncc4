//
// test.cpp
// Nathanael Epps
//

#include "test.hpp"
#include <chrono>

static bool expgenFlag = false;

TEST_CASE(ParseNumber, "5");
TEST_CASE_WITH_OUTPUT(ParseNumber2, "5", "5");
TEST_CASE(ParseNumberWithExtra, "5a");
TEST_CASE(ParseNumberLeadingWs, "     5");
ERROR_CASE(ParseNumberError, "Error");
TEST_CASE(ParseLongNumber, "90210");
TEST_CASE(MixedChars, "123abc456");
TEST_CASE(NegativeInt, "-5");
TEST_CASE(NegativeInt2, "-456");
ERROR_CASE(UnaryMinus, "-"); // Todo: unary minus (see UnaryPlus)
ERROR_CASE(MinusSignExtra, "-a");
TEST_CASE_WITH_OUTPUT(Add, "1+2", "3");
TEST_CASE(UnaryPlus, "+");
TEST_CASE_WITH_OUTPUT(Add2, "123 + 456", "579");
TEST_CASE_WITH_OUTPUT(Sub, "5 - 4", "1");
TEST_CASE_WITH_OUTPUT(Sub2, "10 - 15", "-5");
TEST_CASE_WITH_OUTPUT(AddAndSub, "4 + 5 - 3", "6");
TEST_CASE_WITH_OUTPUT(Mult, "2 * 4", "8");
ERROR_CASE(AddAdd, "2 + +");

ERROR_CASE(UnmatchedParen, "2 * (3 + 4");
ERROR_CASE(UnmatchedParen2, "(2 *");
ERROR_CASE(UnmatchedParen3, "(2");

int main2(int argc, const char** argv) {
    // make sure "system" is available
    if (system(nullptr) == 0) {
        std::cerr << "Error: \'system\' function unavailable\n";
        return EXIT_FAILURE;
    }

    // header
    std::cout << argv[0] << " v" << NCC_VERSION << "\n";

    // parse command line args
    ncc::args_t args = ncc::util::bundle(argc, argv);
    if (ncc::util::getOpt(args, "-v", "--version") != args.end()) {
        return EXIT_SUCCESS;
    } else if (ncc::util::getOpt(args, "-h", "--help") != args.end()) {
        help(args.at(0));
        return EXIT_SUCCESS;
    } else if (ncc::util::getOpt(args, "--expgen") != args.end()) {
        expgenFlag = true;
    }

    // Run tests
    std::cout << "\n";
    if (!expgenFlag) {
        if (!RunTests())
            return EXIT_FAILURE;
        std::cout << "\n";
    }

    std::vector<std::pair<int, int>> expgenArgs = {{5, 0},
                                                   {5, 1},
                                                   {5, 1},
                                                   {5, 1},
                                                   {5, 4},
                                                   {5, 4},
                                                   {5, 5},
                                                   {5, 5},
                                                   {ncc::util::randInt(3, 20), 3},
                                                   {ncc::util::randInt(3, 20), 4},
                                                   {ncc::util::randInt(3, 20), 5},
                                                   {8, 8}};

    if (!ExpgenTest(expgenArgs))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int main(int argc, const char** argv) {
    auto start = std::chrono::system_clock::now();
    int rcode = main2(argc, argv);
    auto end = std::chrono::system_clock::now();

    auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Test time: " << timeMs << "ms\n";
    return rcode;
}
