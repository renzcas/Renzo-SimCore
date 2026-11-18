cmake_minimum_required(VERSION 3.12)
project(RenzoSimCore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(RenzoSimCore
    src/core/Entity.cpp
    src/entities/Creature.cpp
    src/world/World.cpp
    src/simcore/Agent.cpp
)

add_executable(test_creature tests/test_creature.cpp)
target_link_libraries(test_creature PRIVATE RenzoSimCore)

add_executable(test_simcore tests/test_simcore.cpp)
target_link_libraries(test_simcore PRIVATE RenzoSimCore)

add_executable(RenzoSimCoreApp src/main.cpp)
target_link_libraries(RenzoSimCoreApp PRIVATE RenzoSimCore)
