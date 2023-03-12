/**
 * @file
 * @author Nathanael Epps
 */

#ifndef BASIC_FIXTURE
#define BASIC_FIXTURE

#include "Fixture.hpp"

namespace ncc::test {

/**
 * @brief Simplest fixture. No scaffolding, simply print resulting assembly.
 */
class BasicFixture : public Fixture {
  private:
    BasicFixture();

  public:
    /// @brief Create `BasicFixture` instances
    static std::shared_ptr<BasicFixture> factory();

    /// @brief Run test given input
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;

    /// @brief Get inputs associated with the test
    virtual types::input_t getInput() const override;
};

} // namespace ncc::test

#endif
