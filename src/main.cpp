//
// main.cpp
// Nathanael Epps
//

#include "io.hpp"
#include "Controller.hpp"

int main(int argc, const char** argv) {
    try {
        ncc::io::init(std::cin, std::cout);
        
        ncc::Controller ctrl;
        ctrl.run();
    } catch (std::exception& ex) {
        std::cerr << "*** " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "*** Unknown exception\n";
    }
}

