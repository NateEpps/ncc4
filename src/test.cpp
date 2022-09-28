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
ERROR_CASE(MinusSign, "-");
ERROR_CASE(MinusSignExtra, "-a");

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
    
    RunTests();
}
