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
    types::inputOutput_t io;
    io.push_back({"printf(\"Hello, world\");", "Hello, world"});
    io.push_back({"printf(\"%ld\", 1 + 2);", "3"});
    io.push_back({R"(printf("%ld", strlen("MeltMyEyezSeeYourFuture"));)",
                  std::to_string(std::string("MeltMyEyezSeeYourFuture").size())});

    return io;
}
