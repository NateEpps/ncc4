//
// main.cpp
// Nathanael Epps
//

#include "Controller.hpp"
#include "Util.hpp"
#include "io.hpp"

// clang-format off
static void version() {
    std::cout << NCC_NAME << " v" << NCC_VERSION << "\n";
}

static void help(std::string command) {
    version();
    std::cout << "Usage:\n\t" << command << " [options OR see explanation]\n\n";
    
    std::cout << " -h / --help            Bring up this help info\n";
    std::cout << " -v / --version         Print version info\n";
    std::cout << " --print-rax            Use PRINT_RAX scaffold. Defaults to MAIN\n";
    std::cout << "                        without this option.\n\n";
    
    std::cout << "When options are not present, " << NCC_NAME << " reads from standard input and\n";
    std::cout << "writes to standard output. " << NCC_NAME << " can be run interactively, but file\n";
    std::cout << "redirection is generally used for normal operation.\n\n";
}
// clang-format on

int main(int argc, const char** argv) {
    ncc::args_t args = ncc::util::bundle(argc, argv);
    bool forcePrintRax = false;
    if (ncc::util::getOpt(args, "--version", "-v") != args.end()) {
        version();
        return EXIT_SUCCESS;
    } else if (ncc::util::getOpt(args, "--help", "-h") != args.end()) {
        help(args.at(0));
        return EXIT_SUCCESS;
    } else if (ncc::util::getOpt(args, "--print-rax") != args.end()) {
        forcePrintRax = true;
    }

    try {
        ncc::io::init(std::cin, std::cout);

        ncc::Controller ctrl;
        auto scaffoldType = forcePrintRax ? ncc::ScaffoldType::PRINT_RAX : ncc::ScaffoldType::MAIN;
        ctrl.run(scaffoldType);

        ncc::io::metadata(__PRETTY_FUNCTION__, "Exiting successfully");
        return EXIT_SUCCESS;
    } catch (std::exception& ex) {
        std::cerr << "*** " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "*** Unknown exception\n";
    }

    return EXIT_FAILURE;
}
