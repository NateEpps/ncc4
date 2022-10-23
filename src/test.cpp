//
// test.cpp
// Nathanael Epps
//

#include "test.hpp"

TEST_CASE(ParseNumber, "5");
TEST_CASE_WITH_OUTPUT(ParseNumber2, "5", "5");
TEST_CASE(ParseNumberWithExtra, "5a");
TEST_CASE(ParseNumberLeadingWs, "     5");
ERROR_CASE(ParseNumberError, "Error");
TEST_CASE(ParseLongNumber, "90210");
TEST_CASE(MixedChars, "123abc456");
TEST_CASE(NegativeInt, "-5");
TEST_CASE(NegativeInt2, "-456");
ERROR_CASE(MinusSign, "-"); // Todo: unary minus (see JustPlus)
ERROR_CASE(MinusSignExtra, "-a");
TEST_CASE_WITH_OUTPUT(Add, "1+2", "3");
TEST_CASE(JustPlus, "+");
TEST_CASE_WITH_OUTPUT(Add2, "123 + 456", "579");
TEST_CASE_WITH_OUTPUT(Sub, "5 - 4", "1");
TEST_CASE_WITH_OUTPUT(Sub2, "10 - 15", "-5");
TEST_CASE_WITH_OUTPUT(AddAndSub, "4 + 5 - 3", "6");
TEST_CASE_WITH_OUTPUT(Mult, "2 * 4", "8");
ERROR_CASE(AddAdd, "2 + +");
TEST_CASE_WITH_OUTPUT(OrderOfOps, "3 * 2 + 2 * 2", "10");
ERROR_CASE(Divide, "9 / 3");
ERROR_CASE(Mod, "12 % 5");
TEST_CASE_WITH_OUTPUT(MultiMult, "5 * 4 * 3 * 2 * 1", "120");

int main(int argc, const char** argv) {
    std::cout << argv[0] << " v" << NCC_VERSION << "\n\n";
    
    if (system(nullptr) == 0) {
        std::cerr << "\'system\' function unavailable\n";
        return EXIT_FAILURE;
    }

    RunTests();

    return EXIT_SUCCESS;
}
