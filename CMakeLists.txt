cmake_minimum_required(VERSION 3.18)

project(netcip-crypt-char)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W --std=c++11")

set(SOURCE_FILES key.cpp
                 netcip.cpp
                 block.cpp
                 ai.cpp
                 gaus.cpp
                 lin-comb.cpp
                 main.cpp)

#add_library(netcip SHARED STATIC ${SOURCE_FILES})
#add_subdirectory(tests)

add_executable(netcip-test ${SOURCE_FILES})

#set(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR})
#set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

#set(INCLUDE_DIR    ${PROJECT_SOURCE_DIR}/include)
#include_directories(${GRAPH_INCLUDE_DIR})

#install(TARGETS netcip DESTINATION ${LIB_DIR})
