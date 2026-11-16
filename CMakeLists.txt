cmake_minimum_required(VERSION 3.16)

project(RenzoSimCore)

include_directories(include)

add_executable(
    RenzoSimCore
    src/main.cpp
    src/Creature.cpp
)