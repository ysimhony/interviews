cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

# Project name
project(ForSight)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(main main.cpp)
