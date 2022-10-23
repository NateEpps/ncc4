#
# src/CMakeLists.txt
# Nathanael Epps
#

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/io.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scaffold.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/io.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scaffold.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.hpp)

add_library(${PROJECT_NAME}-sources SHARED ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/test.hpp)
add_dependencies(test ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-sources)
target_link_libraries(test ${PROJECT_NAME}-sources)

# For the IDE's...
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
