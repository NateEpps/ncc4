/**
 * @file
 * @author Nathanael Epps
 */

#ifndef SCAFFOLD_HPP
#define SCAFFOLD_HPP

namespace ncc {
class Controller;

/**
 * @brief What kind of scaffold are we using?
 */
enum class ScaffoldType {
    NONE, // No extra scaffolding
    PRINT_RAX // Print contents of `%rax` register
};

/**
 * @brief Handle setup / teardown code needed
 */
class Scaffold {
public:
    /// @brief Constructor
    Scaffold(Controller*);
    
    /// @brief Emit starting scaffold
    void start(ScaffoldType);
    
    /// @brief Emit ending scaffold
    void end();

private:
    Controller* parent;
    
    ScaffoldType scaffoldType;
};
}

#endif
