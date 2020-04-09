cmake_minimum_required(VERSION 3.15)
project(concurrency)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-Wall -Werror -Wextra -pedantic -O2 -lpthread)

add_subdirectory(source)

add_executable(concurrency main.cpp)
target_link_libraries(concurrency pthread thread_utility)