project(json98)

cmake_minimum_required(VERSION 2.8)

enable_testing()

add_definitions(
    -std=c++11
    -fno-rtti
    -fno-exceptions
    -Wall
    -Wextra
    -Werror)

set(json98_SRCS json98.cpp)

add_library(json98 STATIC ${json98_SRCS})

add_test(json98_test json98_test)

add_executable(json98_test ${json98_SRCS} test.cpp)
