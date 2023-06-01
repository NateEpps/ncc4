/**
 * @file
 * @author Nathanael Epps
 */

#ifndef FIXTURE_ITERATOR_HPP
#define FIXTURE_ITERATOR_HPP

#include "TestTypes.hpp"
#include <any>
#include <map>
#include <memory>

namespace ncc::test {
class Fixture;

/// @todo Detect test timeout, and add value here
enum class TestResult { Success, Failure, Exception };

/**
 * @brief Iterate over a fixture's test cases
 *
 * Given a pointer to the fixture and a starting iterator, this class removes the need to
 * differentiate between input-based tests and input/output-based tests.
 */
class FixtureIterator {
  public:
    /// @brief FixtureIterator's can be created at the beginning or end of a sequence
    enum Position { Begin, End };

    /// @brief Create a fixture iterator
    FixtureIterator(std::weak_ptr<Fixture>, Position);

    /// @brief Prefix increment
    FixtureIterator& operator++();

    /// @brief Postfix increment
    FixtureIterator operator++(int);

    /// @brief Compound add
    FixtureIterator& operator+=(int);

    /// @brief Logical equality operator
    bool operator==(const FixtureIterator&);

    /// @brief Logical not-equal operator
    bool operator!=(const FixtureIterator&);

    /// @brief Run the current input (and possibly output) against the test fixture
    TestResult runTest();

  protected:
    /// @brief Is the fixture input-only? Used to initialize `inputOnly`
    static bool isInputOnly(std::weak_ptr<Fixture>);

    /// @brief Initialize static stuff
    static void staticInit(std::weak_ptr<Fixture>);

  private:
    static std::map<std::string, std::any> storedContainers;

    const bool inputOnly;
    std::weak_ptr<Fixture> parentFixture;
    types::input_iterator_t inputItr;
    types::inputOutput_iterator_t inputOutputItr;
};

} // namespace ncc::test

#endif
