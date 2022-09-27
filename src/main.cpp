//
// main.cpp
// Nathanael Epps
//

#include "io.hpp"
#include "Controller.hpp"

int main(int argc, const char** argv) {
    for (int x = 0; x < argc; x++) {
        if (strcmp(argv[x], "--version") == 0 || strcmp(argv[x], "-v") == 0) {
            std::cout << NCC_NAME << " v" << NCC_VERSION << "\n";
            return EXIT_SUCCESS;
        }
    }
    
    try {
        ncc::io::init(std::cin, std::cout);
        
        ncc::Controller ctrl;
        ctrl.run();

        ncc::io::misc(__PRETTY_FUNCTION__, "Exiting successfully");
        return EXIT_SUCCESS;
    } catch (std::exception& ex) {
        std::cerr << "*** " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "*** Unknown exception\n";
    }
    
    return EXIT_FAILURE;
}

