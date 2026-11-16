cmake_minimum_required(VERSION 3.16)

project(RenzoSimCore)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    RenzoSimCore
    src/main.cpp
    src/Creature.cpp
    src/World.cpp
)