cmake_minimum_required(VERSION 3.5)

project(hor-3-general)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(General ${SOURCES})

target_link_libraries(General PUBLIC CONAN_PKG::spdlog CONAN_PKG::nlohmann_json)
target_link_libraries(General PRIVATE project_options project_warnings)

target_include_directories(General PUBLIC "./include")

file(GLOB_RECURSE CREATOR_SOURCES . creator_source/*.cpp)
add_executable(UnitCreator ${CREATOR_SOURCES})
target_include_directories(UnitCreator PUBLIC "./include")
target_link_libraries(UnitCreator PUBLIC CONAN_PKG::spdlog CONAN_PKG::nlohmann_json)
target_link_libraries(UnitCreator PRIVATE project_options project_warnings)
