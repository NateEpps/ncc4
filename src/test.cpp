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

int main(int argc, const char** argv) {
    std::cout << argv[0] << " v" << NCC_VERSION << "\n\n";
    
    if (system(nullptr) == 0) {
        std::cerr << "\'system\' function unavailable\n";
        return EXIT_FAILURE;
    }
    
    ADD_TEST(ParseNumber);
    ADD_TEST(ParseNumber2);
    ADD_TEST(ParseNumberWithExtra);
    ADD_TEST(ParseNumberLeadingWs);
    ADD_TEST(ParseNumberError);
    ADD_TEST(ParseLongNumber);
    ADD_TEST(MixedChars);
    ADD_TEST(NegativeInt);
    ADD_TEST(NegativeInt2);
    ADD_TEST(MinusSign);
    ADD_TEST(MinusSignExtra);
    ADD_TEST(JustPlus);
    ADD_TEST(Add);
    ADD_TEST(Add2);
    ADD_TEST(Sub);
    ADD_TEST(Sub2);
    ADD_TEST(AddAndSub);

    RunTests();
    
    return EXIT_SUCCESS;
}
