cmake_minimum_required(VERSION 3.10)
project(RenzoSimCore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Main executable
add_executable(RenzoSimCore
    src/main.cpp
    src/core/Entity.cpp
    src/entities/Creature.cpp
    src/world/World.cpp
)

# Test executable
add_executable(test_creature
    tests/test_creature.cpp
    src/core/Entity.cpp
    src/entities/Creature.cpp
    src/world/World.cpp
)