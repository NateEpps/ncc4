//
// test.cpp
// Nathanael Epps
//

#include "System.hpp"
#include "Util.hpp"

int main(int argc, const char** argv) {
    ncc::test::System s;
    return s.run(ncc::util::bundle(argc, argv));
}
