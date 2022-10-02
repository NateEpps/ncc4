//
// Scanner.cpp
// Nathanael Epps
//

#include "Scanner.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <sstream>
using namespace ncc;

// For general operation, we need two registers and the stack. I figured
// %rax and %rbx would be okay for this, however after some weird issues, I
// found that using %rbx causes programs to crash (???) So now we're using
// %rax, and... this
static const std::string r2 = "%r10";

Scanner::Scanner(Controller* pc) :
    parent(pc), next(io::read()), opType(OpType::None), tokenType(TokenType::None) {

    skipWs();
    io::misc(__PRETTY_FUNCTION__, "Scanner initialized, next = \'" + std::string(1, next) + "\'");
}

void Scanner::skipWs() {
    while (isspace(next) && next != EOF)
        next = io::read();
}

void Scanner::expected(std::string s) {
    io::error("expected " + s + " [next = \'" + std::string(1, next) + "\']");

    throw std::runtime_error("expected " + s);
}

void Scanner::stub(std::string s) {
    io::error(s + " stub");

    throw std::runtime_error(s + " stub");
}

void Scanner::match(char c) {
    if (c == next) {
        next = io::read();
        skipWs();
    } else {
        expected(std::string(1, c));
    }
}

void Scanner::parseNumber() {
    if (!isnumber(next) && next != '-')
        expected("number");

    token = "";
    
    do {
        token += next;
        next = io::read();
    } while (isnumber(next));

    // input was just "-"
    if (token == "-")
        expected("number");

    skipWs();
    io::write("movq $" + token + ", %rax");

    tokenType = TokenType::NumberLiteral;
}

void Scanner::parseOp() {
    token = "";

    if (next == '+') {
        match('+');
        token = "+";
        opType = OpType::Plus;
    } else if (next == '-') {
        match('-');
        token = "-";
        opType = OpType::Minus;
    } else {
        expected("operator");
    }
    
    tokenType = TokenType::Operator;
}

void Scanner::parse() {
    if (isnumber(next) || next == '-')
        parseNumber();
    else
        parseOp();
}

void Scanner::add() {
    io::write("pushq %rax");
    
    parse();
    if (tokenType != TokenType::NumberLiteral)
        expected("number");

    io::write("popq " + r2);
    io::write("addq " + r2 + ", %rax");
}

void Scanner::sub() {
    stub("subtraction");
}

void Scanner::t4() {
    parse();
    
    if (next == '+' || next == '-') {
        do {
            parseOp();
            if (opType == OpType::Plus)
                add();
            else if (opType == OpType::Minus)
                sub();
        } while (next == '+' || next == '-');
    }
}

void Scanner::expression() {
    t4();
}
