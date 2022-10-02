//
// io.cpp
// Nathanael Epps
//

#include "io.hpp"
#include <fstream>
#include <stdexcept>
#include <stack>

static std::istream* pin = nullptr;
static std::ostream* pout = nullptr;
static bool format = true;
static bool wasInit = false;
static std::stack<char> pushback;
static std::ofstream logfile;

static constexpr size_t MaxLogWidth = 45;

#define TAB "    "
#define TAB_STR std::string(TAB)

static void log(std::string src, std::string mssg) {
    static bool init = false;
    if (!init) {
        logfile.open(std::string(NCC_NAME) + ".log");
        if (!logfile.is_open())
            throw std::runtime_error("Unable to open/create logfile");
        init = true;
    }
    
    std::string sanitized;
    
    for (char c : mssg) {
        if (c == '\n')
            sanitized += "(newline)";
        else if (c == '\t')
            sanitized += "(tab)";
        else if (c == EOF)
            sanitized += "(EOF)";
        else if (iscntrl(c))
            sanitized += "(control)";
        else
            sanitized += c;
    }
    
    if (src.length() > MaxLogWidth)
        src = src.substr(0, MaxLogWidth - 3) + "...";
    
    logfile << std::setw(MaxLogWidth) << src << ": " << sanitized << "\n";
}

static std::string layout(std::string instr) {
    size_t index = instr.find(" ");
    if (index == std::string::npos) {
        return TAB_STR + instr;
    } else {
        static constexpr int Width = 9;
        std::string mnemonic = instr.substr(0, index);
        std::string ops = instr.substr(index + 1);
        
        std::string spaces;
        if (Width - mnemonic.size() > 0)
            spaces = std::string(Width - mnemonic.size(), ' ');
        else
            spaces = " ";
        
        return TAB_STR + mnemonic + spaces + ops;
    }
}

#define WRITE_LOG(str) log(__PRETTY_FUNCTION__, str)

#define INIT_CHECK() if (!wasInit) throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " requires init")

void ncc::io::init(std::istream& in, std::ostream& out, bool fmt) {
    pin = &in;
    pout = &out;
    format = fmt;
    
    if (wasInit) {
        std::stack<char> empty;
        pushback.swap(empty);
        
        if (logfile.is_open())
            logfile << "\n";

        WRITE_LOG("Re-initialized");
    } else {
        WRITE_LOG("Initialized");
    }
    
    wasInit = true;
}

char ncc::io::read() {
    INIT_CHECK();

    char c = '\0';
    if (!pushback.empty()) {
        c = pushback.top();
        pushback.pop();
    } else {
        c = pin->get();
    }
    
    WRITE_LOG("Read \'" + std::string(1, c) + "\' from input");
    return c;
}

void ncc::io::unread(char c) {
    INIT_CHECK();

    WRITE_LOG("Unreading \'" + std::string(1, c) + "\'");
    pushback.push(c);
}

/* void ncc::io::unread(std::string s) {
    INIT_CHECK();
    
    WRITE_LOG("Unreading \"" + s + "\"");

    for (int x = s.size() - 1; x >= 0; x--)
        pushback.push(s[x]);
} */

void ncc::io::write(std::string instr) {
    INIT_CHECK();

    WRITE_LOG("Writing instruction \"" + instr + "\"");
    
    *pout << (format ? layout(instr) : instr) << "\n";
}

void ncc::io::put(std::string instr) {
    INIT_CHECK();

    WRITE_LOG("Writing \"" + instr + "\"");
    *pout << instr;
}


void ncc::io::error(std::string mssg) {
    INIT_CHECK();
    
    WRITE_LOG("Error message: " + mssg);
    
    mssg = "## " + mssg;

    if (format)
        mssg = TAB_STR + mssg;
    
    *pout << mssg << "\n";
}

std::string ncc::io::getTab() {
    return TAB;
}

void ncc::io::misc(std::string src, std::string mssg) {
    log(src, mssg);
}
