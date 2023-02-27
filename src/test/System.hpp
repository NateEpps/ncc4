/**
 * @file
 * @author Nathanael Epps
 */

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
 * @todo `System::add` should enforce type traits
 */
class System {
  public:
    /**
     * @brief Constructor-- add fixtures to list
     */
    System();

    /**
     * @brief Run tests at the higest conceptual level, given command line args
     *
     * @return Return code suitable for main's return value
     */
    int run(args_t);

  private:
    template <class T>
    void add() {
        testFixtures.push_back(T::factory());
    }

    std::vector<std::shared_ptr<Fixture>> testFixtures;
};
} // namespace ncc::test

#endif
