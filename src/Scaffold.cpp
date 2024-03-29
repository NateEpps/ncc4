//
// Scaffold.cpp
// Nathanael Epps
//

#include "Scaffold.hpp"
#include "Controller.hpp"
#include "io.hpp"
#include <sstream>
using namespace ncc;

Scaffold::Scaffold(Controller* pc) : parent(pc) {}

void Scaffold::start(ScaffoldType type) {
    scaffoldType = type;

    if (scaffoldType >= ScaffoldType::MAIN) {
        io::write(".globl _main");
        io::put("_main:\n");
        io::write("pushq %rbp");
        io::write("movq %rsp, %rbp");
        io::write("subq $16, %rsp");
        io::put("\n");
    }
}

void Scaffold::end() {
    auto printSeparator = []() {
        static bool printed = false;
        if (!printed) {
            io::put("\n");
            printed = true;
        }
    };

    if (scaffoldType == ScaffoldType::PRINT_RAX) {
        printSeparator();
        size_t index = parent->addStringData("%ld\\n");
        io::write("leaq S" + std::to_string(index) + "(%rip), %rdi");
        io::write("movq %rax, %rsi");
        io::write("callq _printf");
    }

    if (scaffoldType >= ScaffoldType::MAIN) {
        printSeparator();
        io::write("movq $0, %rax");
        io::write("addq $16, %rsp");
        io::write("popq %rbp");
        io::write("retq");
    }
}
