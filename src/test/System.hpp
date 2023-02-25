//
// System.hpp
// Nathanael Epps
//

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Util.hpp"
#include <memory>

namespace ncc::test {
class Fixture;

/**
 * @brief Central test class
 *
 * Maintain the list of fixtures and test cases, support active testing
 */
class System {
  public:
    /**
     * @brief Constructor-- set everything up
     */
    System();

    /**
     * @brief Run tests, given command line args
     *
     * @return Return code suitable for main's return value
     */
    int run(args_t);

  private:
    /// @todo Detect test timeout, and add value here
    enum class TestResult { Success, Fail, Exception };

    TestResult runImpl(std::shared_ptr<Fixture>, std::string);
    TestResult runImpl(std::shared_ptr<Fixture>, std::string, std::string);

    /// @brief static_assert some type traits
    template <class T>
    void add() {
        testFixtures.push_back(std::make_shared<T>());
    }

    std::vector<std::shared_ptr<Fixture>> testFixtures;
};
} // namespace ncc::test

#endif
