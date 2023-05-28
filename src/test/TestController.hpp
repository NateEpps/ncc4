/**
 * @file
 * @author Nathanael Epps
 */

#ifndef TEST_CONTROL_HPP
#define TEST_CONTROL_HPP

#include "Util.hpp"
#include <memory>
#include <optional>
#include <type_traits>

namespace ncc::test {
class Fixture;
class FixtureIterator;

/**
 * @brief Central test class
 *
 * Maintain the list of fixtures and test cases, support active testing
 */
class TestController {
  public:
    /**
     * @brief Constructor-- add fixtures to list
     */
    TestController();

    /**
     * @brief Run tests at the higest conceptual level, given command line args
     *
     * @return Return code suitable for main's return value
     */
    int run(args_t);

  private:
    // Run all test cases on an individual fixture. Return false on error
    bool runFixture(std::shared_ptr<Fixture>);

    // Run *just* the test pointed to by the given iterator, with passed index for printing
    bool runTest(FixtureIterator&, int);

    // Process command line arguments, return false on error
    bool processArgs(args_t&);

    // Add a fixture to the list
    template <class T>
    void add() {
        static_assert(std::is_base_of<Fixture, T>::value);
        testFixtures.push_back(T::factory());
    }

    std::vector<std::shared_ptr<Fixture>> testFixtures;

    // Command-line info
    std::optional<std::shared_ptr<Fixture>> specificFixture;
    std::optional<int> specificIndex;
    bool listFlag;
    bool helpFlag;
};
} // namespace ncc::test

#endif
