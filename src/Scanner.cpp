//
// Scanner.cpp
// Nathanael Epps
//

#include "Scanner.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <cctype>
#include <sstream>
using namespace ncc;

// For general operation, we need two registers and the stack. I figured
// %rax and %rbx would be okay for this, however after some weird issues, I
// found that using %rbx causes programs to crash (???) So now we're using
// %rax, and... this
static const std::string r2 = "%r10";

Scanner::Scanner(Controller* pc)
    : parent(pc), next(io::read()), opType(OpType::None), tokenType(TokenType::None) {

    skipWs();
    io::metadata(__PRETTY_FUNCTION__,
                 "Scanner initialized, next = \'" + std::string(1, next) + "\'");
}

void Scanner::skipWs() {
    while (isspace(next) && next != EOF)
        next = io::read();
}

void Scanner::expected(std::string s) {
    io::error("expected " + s + " [next = \'" + std::string(1, next) + "\']");

    throw std::runtime_error("expected " + s);
}

void Scanner::require(bool cond, std::string condStr) {
    if (!cond)
        expected(condStr);
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

void Scanner::parseFunctionArgs() {
    if (next != '(')
        expected("open-(");

#warning parseFunctionArgs stub
    //...
}

void Scanner::parseNumber() {
    if (!isdigit(next) && next != '-')
        expected("number");

    token = "";

    do {
        token += next;
        next = io::read();
    } while (isdigit(next));

    // input was just "-"
    if (token == "-")
        expected("number");

    skipWs();
    io::write("movq $" + token + ", %rax");

    tokenType = TokenType::NumberLiteral;
}

void Scanner::parseIdent() {
    if (!isalpha(next))
        expected("identifier");

    token = "";

    do {
        token += next;
        next = io::read();
    } while (isalpha(next));

    skipWs();
    tokenType = TokenType::Identifier;
}

void Scanner::parseStringLiteral() {
    if (next != '\"')
        expected("string literal");

    token = "";

    char prev = next;
    next = io::read();

    if (prev == '\"' && next == '\"') {
        next = io::read();
        skipWs();
        io::metadata(__PRETTY_FUNCTION__, "Parsed empty string");
    } else {
#warning Todo- handle escaped quotes
        while (next != '\"') {
            token += next;
            next = io::read();
        }

        next = io::read();
        skipWs();

        io::metadata(__PRETTY_FUNCTION__, "Parsed string <<<" + token + ">>>");
    }

    size_t index = parent->addStringData(token);
    io::write("leaq S" + std::to_string(index) + "(%rip), %rax");
    tokenType = TokenType::StringLiteral;

    io::metadata(__PRETTY_FUNCTION__,
                 "prev = " + std::string(1, prev) + ", next = " + std::string(1, next));
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
    } else if (next == '*') {
        match('*');
        token = "*";
        opType = OpType::Multiply;
    } else if (next == '/') {
        match('/');
        token = "/";
        opType = OpType::Division;
    } else if (next == '%') {
        match('%');
        token = "%";
        opType = OpType::Modulus;
    } else {
        expected("operator");
    }

    tokenType = TokenType::Operator;
}

void Scanner::parse() {
    if (isdigit(next) || next == '-') {
        parseNumber();
    } else if (isalpha(next)) {
        parseIdent();
        if (next == '(') {
            std::string functionName = token;
            parseFunctionArgs();
            stub("functions (function call to \"" + functionName + "\")");
        } else {
            stub("variable");
        }
    } else if (next == '(') {
        match('(');
        expression();
        match(')');
    } else if (next == '\"') {
        parseStringLiteral();
    } else {
        parseOp();
    }
}

void Scanner::mult() {
    parse();
    require(tokenType != TokenType::Operator, "non-operator");

    io::write("popq " + r2);
    io::write("imulq " + r2);
}

void Scanner::div() {
    parse();
    require(tokenType != TokenType::Operator, "non-operator");

    io::write("pushq %rax");
    io::write("popq " + r2);
    io::write("popq %rax");

    io::write("movq $0, %rdx\t\t## idivq OP => %rax = %rdx:%rax / OP");
    io::write("idivq " + r2);
}

void Scanner::mod() {
    parse();
    require(tokenType != TokenType::Operator, "non-operator");

    io::write("pushq %rax");
    io::write("popq " + r2);
    io::write("popq %rax");

    io::write("movq $0, %rdx");
    io::write("idivq " + r2);
    io::write("movq %rdx, %rax\t\t## idivq OP => %rdx = %rdx:%rax % OP");
}

void Scanner::t3() {
    parse();

    if (next == '*' || next == '/' || next == '%') {
        do {
            io::write("pushq %rax");

            parseOp();
            if (opType == OpType::Multiply)
                mult();
            else if (opType == OpType::Division)
                div();
            else if (opType == OpType::Modulus)
                mod();
            else
                expected("multiplication, division, or modulus");

        } while (next == '*' || next == '/' || next == '%');
    }
}

void Scanner::add() {
    t3();
    require(tokenType != TokenType::Operator, "non-operator");

    io::write("popq " + r2);
    io::write("addq " + r2 + ", %rax");
}

void Scanner::sub() {
    t3();
    require(tokenType != TokenType::Operator, "non-operator");

    io::write("popq " + r2);
    io::write("subq " + r2 + ", %rax");
    io::write("negq %rax");
}

void Scanner::t4() {
    t3();

    if (next == '+' || next == '-') {
        do {
            io::write("pushq %rax");

            parseOp();
            if (opType == OpType::Plus)
                add();
            else if (opType == OpType::Minus)
                sub();
            else
                expected("addition or subtraction");

        } while (next == '+' || next == '-');
    }
}

void Scanner::expression() { t4(); }
