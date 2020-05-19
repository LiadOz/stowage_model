# CMakeList.txt : CMake project for Simulation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
# Add source to this project's executable.
add_executable (Simulation "${PROJECT_SOURCE_DIR}/Simulation/main.cpp")

target_link_libraries("Simulation" "Util" "-lstdc++fs")

add_compile_options(-stdlib=libc++)
add_compile_options(-std=c++17)
# TODO: Add tests and install targets if needed.