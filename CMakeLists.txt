cmake_minimum_required(VERSION 3.17)
project(tarp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tarp main.cpp MakefileCreator.cpp ProjectDirCreator.cpp)