//
// test.hpp
// Nathanael Epps
//

#ifndef TEST_HPP
#define TEST_HPP

#include "Controller.hpp"
#include "io.hpp"
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

static std::vector<std::pair<std::string, std::function<void()>>> testVec;

#define TEST_CASE(name, in) \
void testCase##name () {\
std::stringstream input, output;\
input << in;\
ncc::io::init(input, output, false);\
ncc::Controller ctrl;\
ctrl.run(ncc::ScaffoldType::NONE);\
std::cout << "Test Case \"" << #name << "\"\n";\
std::cout << "Input:\n>>> " << in << "\n";\
std::cout << "Output:\n>>> " << output.str() << "\n";\
}

#define ERROR_CASE(name, in) \
void testCase##name () {\
std::stringstream input, output;\
input << in;\
ncc::io::init(input, output, false);\
ncc::Controller ctrl;\
try {\
ctrl.run(ncc::ScaffoldType::NONE);\
}\
catch (std::exception& ex) {\
std::cout << "Error Case \"" << #name << "\"\n";\
std::cout << "Input:\n>>> " << in << "\n";\
std::cout << "Error Message:\n>>> " << output.str() << "\n";\
return;\
}\
throw std::runtime_error("Test " #name " was expected to fail, and didn't");\
}

#define ADD_TEST(name) testVec.push_back(std::make_pair(#name, &testCase##name));

#define RUN_TESTS() \
int count = 0;\
for (const auto& pair : testVec) {\
try {\
pair.second();\
count++;\
}\
catch (std::exception& ex) {\
std::cerr << "Test \"" << pair.first << "\" threw an exception: " << ex.what() << "\n";\
break;\
}\
}\
std::cout << "Passed " << count << " / " << testVec.size() << " tests\n";


#endif
