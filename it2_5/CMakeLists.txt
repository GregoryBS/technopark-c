
cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES 
        file.c)

add_library(extra STATIC ${SOURCES})
add_library(sequential STATIC sequential.c)
add_library(parallel SHARED parallel.c)

add_executable(main.out main.c)
target_link_libraries(main.out -ldl)
target_link_libraries(main.out extra)
target_link_libraries(main.out sequential)
target_link_libraries(main.out parallel -lpthread)

add_executable(test.out test.cpp)
target_link_libraries(test.out -ldl)
target_link_libraries(test.out extra)
target_link_libraries(test.out sequential)
target_link_libraries(test.out parallel -lpthread)
target_link_libraries(test.out ${GTEST_LIBRARIES} pthread)
