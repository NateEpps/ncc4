//
// test.cpp
// Nathanael Epps
//

#include "test.hpp"

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
TEST_CASE_WITH_OUTPUT(MultiMult, "5 * 4 * 3 * 2 * 1", "120");
TEST_CASE_WITH_OUTPUT(Divide, "10 / 5", "2");
TEST_CASE_WITH_OUTPUT(NestedDiv, "100 / 2 / 10 / 5", "1");
TEST_CASE_WITH_OUTPUT(Mod, "12 % 5", "2");
TEST_CASE_WITH_OUTPUT(Mod2, "19 % 10 % 7", "2");

TEST_CASE_WITH_OUTPUT(OrderOfOps, "3 * 2 + 2 * 2", "10");
TEST_CASE_WITH_OUTPUT(OrderOfOps2, "3 * (2 + 2) * 2", "24");
ERROR_CASE(UnmatchedParen, "2 * (3 + 4");
ERROR_CASE(UnmatchedParen2, "(2 *");
ERROR_CASE(UnmatchedParen3, "(2");

int main(int argc, const char** argv) {
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

    if (!ExpgenTest())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
