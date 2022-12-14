//
// Controller.cpp
// Nathanael Epps
//

#include "Controller.hpp"
#include "io.hpp"
#include <sstream>
using namespace ncc;

Controller::Controller() : scanner(this), scaffold(this) {}

void Controller::run(ScaffoldType type) {
    scaffold.start(type);
    
    scanner.expression();
    
    scaffold.end();
    
    io::put(getDataSection());
}

size_t Controller::addStringData(std::string str) {
    data.push_back(str);
    return data.size() - 1;
}

std::string Controller::getDataSection() {
    std::stringstream stream;
    stream << "\n";
    for (int x = 0; x < data.size(); x++)
        stream << "S" << x << ":\n" << io::getTab() << ".asciz \"" << data[x] << "\"\n";

    return stream.str();
}
