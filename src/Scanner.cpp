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

    while (next != '\"' || (next == '\"' && prev == '\\')) {
        token += next;
        prev = next;
        next = io::read();

        if (next == EOF)
            expected("end-of-string, not EOF");
    }

    next = io::read();
    skipWs();

    size_t index = parent->addStringData(token);
    io::write("leaq S" + std::to_string(index) + "(%rip), %rax");
    tokenType = TokenType::StringLiteral;
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
        expected("operator (next = \'" + std::string(1, next) + "\')");
    }

    tokenType = TokenType::Operator;
}

void Scanner::parseFunctionArgs() {
    if (next != '(')
        expected("open-(");

    match('(');

    static const std::vector<std::string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

    // first draft
    int regIndex = 0;
    while (next != ')') {
        if (regIndex >= argRegs.size())
            expected("less arguments");

        // save...
        for (int x = 0; x <= regIndex; x++)
            io::write("pushq " + argRegs[x]);

        expression();

        // ... and restore
        for (int x = regIndex; x >= 0; x--)
            io::write("popq " + argRegs[x]);

        // strange that we're not specifically aligning the stack to 16 bytes above, but what we
        // have here works. If weird things start causing segfaults, this is a good spot to
        // look... See issue #37

        io::write("movq %rax, " + argRegs[regIndex]);
        regIndex++;

        if (next == ',')
            match(',');
    }

    match(')');
}

void Scanner::parse() {
    if (isdigit(next) || next == '-') {
        parseNumber();
    } else if (isalpha(next)) {
        parseIdent();
        std::string identifier = token;

        if (next == '(') {
            parseFunctionArgs();
            io::write("callq _" + identifier);
        } else {
            stub("variable (named \"" + identifier + "\")");
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
