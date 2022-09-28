//
// Scanner.cpp
// Nathanael Epps
//

#include "Scanner.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <sstream>
using namespace ncc;

Scanner::Scanner(Controller* pc) : parent(pc), current(io::read()) {
    skipWs();
    io::misc(__PRETTY_FUNCTION__, "Scanner initialized, current = \'" + std::string(1, current) + "\'");
}

void Scanner::skipWs() {
    while (isspace(current) && current != EOF)
        current = io::read();
}

void Scanner::expected(std::string s) {
    io::error("expected " + s + " [current = \'" + std::string(1, current) + "\']");

    throw std::runtime_error("expected " + s);
}

void Scanner::match(char c) {
    if (c == current) {
        current = io::read();
        skipWs();
    } else {
        expected(std::string(1, c));
    }
}

void Scanner::parseNumber() {
    if (!isnumber(current) && current != '-')
        expected("number");
    
    std::string num;
    num += current;
    current = io::read();
    
    while (isnumber(current)) {
        num += current;
        current = io::read();
    }
    
    // input was just "-"
    if (num == "-")
        expected("number");
    
    skipWs();
    io::write("movq $" + num + ", %rax");
}

void Scanner::parse() {
    if (isnumber(current) || current == '-')
        parseNumber();
    else
        expected("number");
}

void Scanner::expression() {
    parse();
}
