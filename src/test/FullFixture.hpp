/**
 * @file
 * @author Nate Epps
 */

#ifndef FULL_FIXTURE_HPP
#define FULL_FIXTURE_HPP

#include "Fixture.hpp"
#include "Scaffold.hpp"

namespace ncc::test {

/**
 * @brief Abstract class, pseudo-fixture for classes that do filesystem IO.
 *
 * Not used for _every_ IO-based fixture
 */
class FullFixture : public Fixture {
  protected:
    /// @brief Constructor
    FullFixture(std::string);

  public:
    /// @brief Abstract method to retrieve scaffolding type
    ///
    /// Subclasses should override this
    virtual ncc::ScaffoldType getScaffoldType() const = 0;

    /// @brief Run a test case
    ///
    /// Subclasses don't override this one
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) override;
};

} // namespace ncc::test

#endif
