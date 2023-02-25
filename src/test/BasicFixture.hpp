//
// BasicFixture.hpp
// Nathanael Epps
//

#ifndef BASIC_FIXTURE
#define BASIC_FIXTURE

#include "Fixture.hpp"

namespace ncc::test {
/**
 * @brief Simplest fixture. No scaffolding, simply print resulting assembly.
 */
class BasicFixture : public Fixture {
  public:
    /// @brief Constructor
    BasicFixture();

    /// @brief Run test given input
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;

    /// @brief Get inputs associated with the test
    virtual std::vector<std::string> getInput() const override;
};
} // namespace ncc::test

#endif
