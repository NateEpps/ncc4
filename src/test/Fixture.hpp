/**
 * @file
 * @author Nathanael Epps
 */

#ifndef FIXTURE_HPP
#define FIXTURE_HPP

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace ncc::test {
/**
 * @brief Abstract base class for test fixtures
 *
 * Input-only tests need only override `getInput`, tests with input and output override
 * `getInputOutput`. Overriding neither is considered an error.
 */
class Fixture {
  public:
    /// @brief Create a fixture, given its name
    explicit Fixture(std::string);

    /// @brief Run this test fixture given an input string, and potentially an output string as well
    ///
    /// @return true/false based on success/failure
    virtual bool run(std::string input, std::optional<std::string> output = std::nullopt) = 0;

    /// @brief Get stored error information
    virtual std::string getErrata() const;

    /// @brief Retrieve all inputs
    virtual std::vector<std::string> getInput() const;

    /// @brief Return input/output pairs
    virtual std::map<std::string, std::string> getInputOutput() const;

    /// @brief Format compiler input or output so subclasses print data in a uniform way
    static std::string testFormat(std::string);

    /// @brief Fixture name, suitable for output
    const std::string name;
};
} // namespace ncc::test

#endif
