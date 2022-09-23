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
    io::misc(__PRETTY_FUNCTION__, "Scanner initialized, current = " + std::to_string((int) current) + " (ascii)");
}

void Scanner::skipWs() {
    while (isspace(current) && current != EOF)
        current = io::read();
}

void Scanner::expected(std::string s) {
    io::error("expected " + s + " [current = " + std::to_string((int) current) + " (ascii)]");

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
    if (!isnumber(current))
        expected("number");
    
    char num = current;
    match(current);
    
    io::write("movq $" + std::string(1, num) + ", %rax");
}

void Scanner::parse() {
    if (isnumber(current))
        parseNumber();
    else
        expected("number");
}

void Scanner::expression() {
    parse();
}
