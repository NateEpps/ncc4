//
// Parser.cpp
// Nathanael Epps
//

#include "Parser.hpp"
#include "Controller.hpp"

using namespace ncc;

Parser::Parser(Controller* pc) : parent(pc), scanner(parent) {}

void Parser::program() {
    // minimum-viable case
    scanner.expression();
}
