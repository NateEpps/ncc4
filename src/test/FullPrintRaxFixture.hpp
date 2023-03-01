/**
 * @file
 * @author Nathanael Epps
 */

#ifndef PRINT_RAX_FIXTURE_HPP
#define PRINT_RAX_FIXTURE_HPP

#include "Fixture.hpp"

namespace ncc::test {

/**
 * @brief Full test fixture with "print rax" scaffolding
 *
 * Run input through ncc with "print rax" scaffolding, run assembly through gcc, run resulting
 * program and collect output
 */
class FullPrintRaxFixture : public Fixture {
  private:
    FullPrintRaxFixture();

  public:
    /// @brief Create `FullPrintRaxFixture` instances
    static std::shared_ptr<FullPrintRaxFixture> factory();

    /// @brief Run a test case
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;

    /// @brief Get input/output data
    virtual std::map<std::string, std::string> getInputOutput() const override;
};

} // namespace ncc::test

#endif
