#
# src/test/CMakeLists.txt
# Nathanael Epps
#

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BasicFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ErrorFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpgenFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Fixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FixtureIterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FullFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FullMainFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FullPrintRaxFixture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

add_executable(test ${TEST_SOURCES})

target_link_libraries(test ${PROJECT_NAME}-sources)

add_dependencies(test ${PROJECT_NAME} expgen)
