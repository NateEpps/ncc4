//
// main.cpp
// Nathanael Epps
//

#include "Controller.hpp"
#include "io.hpp"
#include "Util.hpp"

static void version() {
    std::cout << NCC_NAME << " v" << NCC_VERSION << "\n";
}

static void help(std::string command) {
    version();
    std::cout << "Usage:\n\t" << command << " [options OR see explanation]\n\n";
    
    std::cout << " -h / --help            Bring up this help info\n";
    std::cout << " -v / --version         Print version info\n\n";
    
    std::cout << "When options are not present, " << NCC_NAME << " reads from standard input and\n";
    std::cout << "writes to standard output. " << NCC_NAME << " can be run interactively, but file\n";
    std::cout << "redirection is generally used for normal operation.\n\n";
}

int main(int argc, const char** argv) {
    ncc::args_t args = ncc::util::bundle(argc, argv);
    if (ncc::util::getOpt(args, "--version", "-v") != args.end()) {
        version();
        return EXIT_SUCCESS;
    } else if (ncc::util::getOpt(args, "--help", "-h") != args.end()) {
        help(args.at(0));
        return EXIT_SUCCESS;
    }
    
    try {
        ncc::io::init(std::cin, std::cout);
        
        ncc::Controller ctrl;
        ctrl.run();

        ncc::io::metadata(__PRETTY_FUNCTION__, "Exiting successfully");
        return EXIT_SUCCESS;
    } catch (std::exception& ex) {
        std::cerr << "*** " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "*** Unknown exception\n";
    }
    
    return EXIT_FAILURE;
}

