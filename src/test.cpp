//
// test.cpp
// Nathanael Epps
//

#include "test.hpp"

TEST_CASE(ParseNumber, "5");
TEST_CASE(ParseNumberWithExtra, "5a");
TEST_CASE(ParseNumberLeadingWs, "     5");
ERROR_CASE(ParseNumberError, "Error");
TEST_CASE(ParseLongNumber, "90210");
TEST_CASE(MixedChars, "123abc456");
TEST_CASE(NegativeInt, "-5");
TEST_CASE(NegativeInt2, "-456");
#warning Unary minus
ERROR_CASE(MinusSign, "-"); // Note: this is a fail case, and "JustPlus" is not
ERROR_CASE(MinusSignExtra, "-a");
TEST_CASE(Add, "1+2");
TEST_CASE(JustPlus, "+");
TEST_CASE(Add2, "123 + 456");

TEST_CASE(Sub, "5 - 4");
TEST_CASE(Sub2, "10 - 15");

int main(int argc, const char** argv) {
    std::cout << argv[0] << " v" << NCC_VERSION << "\n\n";
    
    ADD_TEST(ParseNumber);
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

    RunTests();
}
