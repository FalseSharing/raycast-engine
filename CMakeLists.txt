cmake_minimum_required(VERSION 3.20)
project(raycast_engine VERSION 0.9.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(raycast_core src/raycaster.cpp)
target_include_directories(raycast_core PUBLIC include)

add_executable(raycast_demo src/main.cpp)
target_link_libraries(raycast_demo PRIVATE raycast_core)
