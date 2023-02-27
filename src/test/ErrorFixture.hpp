/**
 * @file
 * @author Nathanael Epps
 */

#ifndef ERROR_FIXTURE_HPP
#define ERROR_FIXTURE_HPP

#include "Fixture.hpp"

namespace ncc::test {

/**
 * @brief No scaffolding. Inputs are expected to fail, NOT failing is considered an error.
 */
class ErrorFixture : public Fixture {
  private:
    ErrorFixture();

  public:
    /// @brief Create `ErrorFixture` instances
    static std::shared_ptr<ErrorFixture> factory();

    /// @brief Run a test case
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;

    /// @brief Get test inputs
    virtual std::vector<std::string> getInput() const override;
};

} // namespace ncc::test

#endif
