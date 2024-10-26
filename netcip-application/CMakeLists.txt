cmake_minimum_required(VERSION 3.10)

project(netcip-application)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_executable(netcip-test test/main.cpp)

target_compile_definitions(
    netcip-test PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test"
)

add_executable(netcip-speedtest speedtest/main.cpp)

target_link_libraries(netcip-speedtest PRIVATE cryptopp)

add_test(NAME netcip-test COMMAND netcip-test)
