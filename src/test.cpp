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

int main(int argc, const char** argv) {
    std::cout << argv[0] << " v" << NCC_VERSION << "\n\n";
    
    ADD_TEST(ParseNumber);
    ADD_TEST(ParseNumberWithExtra);
    ADD_TEST(ParseNumberLeadingWs);
    ADD_TEST(ParseNumberError);
    ADD_TEST(ParseLongNumber);
    
    RUN_TESTS();
}
