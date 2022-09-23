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
    
    if (scaffoldType == ScaffoldType::PRINT_RAX) {
        io::write(".globl _main");
        io::put("_main:\n");
        io::write("pushq %rbp");
        io::write("movq %rsp, %rbp");
        io::write("subq $16, %rsp");
        io::put("\n");
    }
}

void Scaffold::end() {
    if (scaffoldType == ScaffoldType::PRINT_RAX) {
        io::put("\n");
#warning ToString
        std::stringstream ss;
        ss << parent->addStringData("%d\\n");
        io::write("leaq S" + ss.str() + "(%rip), %rdi");
        io::write("movq %rax, %rsi");
        io::write("callq _printf");
        
        io::write("movq $0, %rax");
        io::write("addq $16, %rsp");
        io::write("popq %rbp");
        io::write("retq");
    }
}
