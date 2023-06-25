cmake_minimum_required(VERSION 3.18)

project(netcip-crypt-char)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W --std=c++11")

set(AI_SOURCES key.cpp
               netcip.cpp
               block.cpp
               lin-comb.cpp
               ai.cpp
               gaus.cpp
               main.cpp)

set(MDP_SOURCES key.cpp
                netcip.cpp
                block.cpp
                mdp.cpp)

set(__N 4)
set(__M 4)
set(__H 16)


add_executable(netcip-mdp-${__N}-${__M}-${__H} ${MDP_SOURCES})
add_executable(netcip-ai-${__N}-${__M}-${__H} ${AI_SOURCES})
