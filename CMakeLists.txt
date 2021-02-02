cmake_minimum_required(VERSION 3.17)
project(tarp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tarp 
    "src/main.cpp"
    "src/MakefileCreator.cpp"
    "src/ProjectDirCreator.cpp"
    "src/ProjectGenerator.cpp"
    "src/CodeGenerator.cpp"
)



target_include_directories(tarp PRIVATE "./include")