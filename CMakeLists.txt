cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(heroes_of_random)

option(DEBUG "Build with debug flags" OFF)
option(TESTS "Build tests" OFF)
option(EXAMPLE "Build example" OFF)

add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

set_project_warnings(project_warnings)

#include(cmake/Doxygen.cmake)
#enable_doxygen()

set(CONAN_EXTRA_REQUIRES "spdlog/1.5.0" "fmt/6.2.0" "nlohmann_json/3.7.3")
include(cmake/Conan.cmake)
run_conan()

add_subdirectory("General")
add_subdirectory("Game")
add_subdirectory("Editor")
