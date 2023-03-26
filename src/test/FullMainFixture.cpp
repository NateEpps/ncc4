//
// FullMainFixture.cpp
// Nate Epps
//

#include "FullMainFixture.hpp"

using namespace ncc::test;

FullMainFixture::FullMainFixture() : FullFixture("FullMain") {}

std::shared_ptr<FullMainFixture> FullMainFixture::factory() {
    return std::shared_ptr<FullMainFixture>(new FullMainFixture);
}

ncc::ScaffoldType FullMainFixture::getScaffoldType() const { return ncc::ScaffoldType::MAIN; }

types::inputOutput_t FullMainFixture::getInputOutput() const {
    return {{"printf(\"Hello, world\");", "Hello, world"}, {"printf(\"%ld\", 1 + 2);", "3"}};
}
