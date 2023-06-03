#
# src/CMakeLists.txt
# Nathanael Epps
#

## Source code ##

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/io.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scaffold.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/io.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scaffold.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser.hpp)

add_library(${PROJECT_NAME}-sources SHARED ${SOURCES} ${HEADERS})

## ncc ##

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-sources)

## expgen ##

add_compile_definitions(EXPGEN_NAME="expgen")

add_executable(expgen ${CMAKE_CURRENT_SOURCE_DIR}/tools/expgen.cpp)
target_link_libraries(expgen ${PROJECT_NAME}-sources)

## test ##

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

# For the IDE's...
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
