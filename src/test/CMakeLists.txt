#
# src/test/CMakeLists.txt
# Nathanael Epps
#

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BasicFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ErrorFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Fixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FixtureIterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

add_executable(test ${TEST_SOURCES})

target_link_libraries(test ${PROJECT_NAME}-sources)

add_dependencies(test ${PROJECT_NAME} expgen)
