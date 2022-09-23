//
// io.cpp
// Nathanael Epps
//

#include "io.hpp"
#include <stdexcept>
#include <stack>

static std::istream* pin = nullptr;
static std::ostream* pout = nullptr;
static bool format = true;
static bool wasInit = false;
static std::stack<char> pushback;

#define TAB "    "

void ncc::io::init(std::istream& in, std::ostream& out, bool fmt) {
    if (wasInit)
        throw std::runtime_error("calling \"init\" twice is prohibited");

    pin = &in;
    pout = &out;
    format = fmt;
    wasInit = true;
}

char ncc::io::read() {
    if (!wasInit)
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init");

    if (!pushback.empty()) {
        char c = pushback.top();
        pushback.pop();
        return c;
    } else {
        return pin->get();
    }
}

void ncc::io::unread(char c) {
    if (!wasInit)
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init");

    pushback.push(c);
}

void ncc::io::write(std::string instr) {
    if (!wasInit)
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init");

#warning Todo- formatting, also error formatting
    *pout << TAB << instr << "\n";
}

void ncc::io::put(std::string instr) {
    if (!wasInit)
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init");

    *pout << instr;
}


void ncc::io::error(std::string mssg) {
    if (!wasInit)
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init");
    
    *pout << TAB << "## " << mssg << "\n";
}

std::string ncc::io::getTab() {
    return TAB;
}
