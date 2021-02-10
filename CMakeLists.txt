cmake_minimum_required(VERSION 3.17)
project(tarp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sourceDir "src")
set(sources 
    "${sourceDir}/MakefileGenerator/CMakeGenerator.cpp"
    "${sourceDir}/ProjectDirCreator/ProjectDirCreator.cpp"
    "${sourceDir}/ProjectGenerator.cpp"
    "${sourceDir}/MakefileGenerator/UnixMakefileGenerator.cpp" 
    "${sourceDir}/MakefileGenerator/MakefileGenerator.cpp"
    "${sourceDir}/CodeGenerator/CGenerator.cpp" 
    "${sourceDir}/CodeGenerator/CppGenerator.cpp"
    "${sourceDir}/Utilities/GitInit.cpp"
)

add_executable(tarp 
    "${sourceDir}/main.cpp"
    ${sources}
)

target_include_directories(tarp PRIVATE "./include")

#include(GNUInstallDir)
install(TARGETS tarp)

# Automatically generate docs when you use "cmake --build ."
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message("Doxygen found version: ${DOXYGEN_VERSION}")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")
    set(DOXYGEN_EXCLUDE_PATTERNS ".vs/" ".out/")
    doxygen_add_docs(doc ${CMAKE_SOURCE_DIR} ALL)
endif()

find_package(GTest CONFIG)
if(GTest_FOUND)
    message("Google test - found.")
    set(sourceDir "../src")
    include(test/CMakeLists.txt)
    target_include_directories(testing PRIVATE "./include")
else()
    message("Google Test - not found.")
endif()