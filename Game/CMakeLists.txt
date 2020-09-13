cmake_minimum_required(VERSION 3.5)

project(hor-3-game)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(hor3 ${SOURCES})

target_link_libraries(hor3 PUBLIC General CONAN_PKG::spdlog CONAN_PKG::nlohmann_json)
target_link_libraries(hor3 PRIVATE project_options project_warnings)

target_include_directories(hor3 PUBLIC "./include")
