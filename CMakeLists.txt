cmake_minimum_required(VERSION 3.9)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 11)

add_executable(HumansVsZombies main.cpp Organism.cpp Organism.h Human.cpp Human.h Zombie.cpp Zombie.h World.cpp World.h)