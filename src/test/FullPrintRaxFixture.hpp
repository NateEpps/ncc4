/**
 * @file
 * @author Nathanael Epps
 */

#ifndef PRINT_RAX_FIXTURE_HPP
#define PRINT_RAX_FIXTURE_HPP

#include "FullFixture.hpp"

namespace ncc::test {

/**
 * @brief Full test fixture with "print rax" scaffolding
 *
 * Run input through ncc with "print rax" scaffolding, run assembly through gcc, run resulting
 * program and collect output
 */
class FullPrintRaxFixture : public FullFixture {
  private:
    FullPrintRaxFixture();

  public:
    /// @brief Create `FullPrintRaxFixture` instances
    static std::shared_ptr<FullPrintRaxFixture> factory();

    /// @brief Get the scaffolding type
    virtual ncc::ScaffoldType getScaffoldType() const override;

    /// @brief Get input/output data
    virtual types::inputOutput_t getInputOutput() const override;
};

} // namespace ncc::test

#endif
