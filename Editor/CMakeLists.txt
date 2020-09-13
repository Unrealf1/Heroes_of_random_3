cmake_minimum_required(VERSION 3.5)

project(hor-3-editor)

file(GLOB_RECURSE CREATOR_SOURCES . source/*.cpp)
add_executable(UnitCreator ${CREATOR_SOURCES})
target_include_directories(UnitCreator PUBLIC "./include")
target_link_libraries(UnitCreator PUBLIC General CONAN_PKG::spdlog CONAN_PKG::nlohmann_json)
target_link_libraries(UnitCreator PRIVATE project_options project_warnings)
