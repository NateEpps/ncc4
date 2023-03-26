/**
 * @file
 * @author Nate Epps
 */

#ifndef FULL_MAIN_FIXTURE
#define FULL_MAIN_FIXTURE

#include "FullFixture.hpp"

namespace ncc::test {

/**
 * @brief Full fixture with main scaffolding
 */
class FullMainFixture : public FullFixture {
  private:
    FullMainFixture();

  public:
    /// @brief Create `FullPrintRaxFixture` instances
    static std::shared_ptr<FullMainFixture> factory();

    /// @brief Get the scaffolding type
    virtual ncc::ScaffoldType getScaffoldType() const override;

    /// @brief Get input/output data
    virtual types::inputOutput_t getInputOutput() const override;
};

} // namespace ncc::test

#endif
