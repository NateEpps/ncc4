/**
 * @file
 * @author Nathanael Epps
 */

#ifndef EXPGEN_FIXTURE_HPP
#define EXPGEN_FIXTURE_HPP

#include "Fixture.hpp"

namespace ncc::test {

/**
 * @brief Bring out the big guns-- run `ncc` with input generated by `expgen`
 */
class ExpgenFixture : public Fixture {
  private:
    ExpgenFixture();

  public:
    /// @brief Create ExpgenFixture instances
    static std::shared_ptr<ExpgenFixture> factory();

    /// @brief Run a test case
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;

    /// @brief Get IO associated with the test
    virtual types::inputOutput_t getInputOutput() const override;
};

} // namespace ncc::test

#endif
