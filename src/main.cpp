//
// main.cpp
// Nathanael Epps
//

#include "Controller.hpp"
#include "io.hpp"
#include "Util.hpp"

int main(int argc, const char** argv) {
    auto args = ncc::util::bundle(argc, argv);
    if (ncc::util::getOpt(args, "--version", "-v") != args.end()) {
        std::cout << NCC_NAME << " v" << NCC_VERSION << "\n";
        return EXIT_SUCCESS;
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

