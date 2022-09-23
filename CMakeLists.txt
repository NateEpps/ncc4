#
# CMakeLists.txt
# Nathanael Epps
#

cmake_minimum_required(VERSION 3.0)

project(ncc VERSION 0.0)

add_compile_definitions(NCC_VERSION="${PROJECT_VERSION}")
add_compile_definitions(NCC_NAME="${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

message(STATUS "Configuring ${CMAKE_BINARY_DIR}/Doxyfile...")
configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)

add_custom_target(docs
                  COMMAND doxygen ${CMAKE_BINARY_DIR}/Doxyfile
                  BYPRODUCTS ${CMAKE_BINARY_DIR}/docs)
