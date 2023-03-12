/**
 * @file
 * @author Nathanael Epps
 */

#ifndef TEST_CONTROL_HPP
#define TEST_CONTROL_HPP

#include "Util.hpp"
#include <memory>
#include <type_traits>

namespace ncc::test {
class Fixture;

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
    template <class T>
    void add() {
        static_assert(std::is_base_of<Fixture, T>::value);
        testFixtures.push_back(T::factory());
    }

    std::vector<std::shared_ptr<Fixture>> testFixtures;
};
} // namespace ncc::test

#endif
