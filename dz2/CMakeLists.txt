cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(_parallel SHARED dynamic.c extra_func.c)
add_library(_sequential STATIC static.c extra_func.c)

add_executable(st_main.out main.c)
target_link_libraries(st_main.out _sequential)

add_executable(dyn_main.out main.c)
target_link_libraries(dyn_main.out _parallel)

add_executable(st_test.out st_test.cpp)
target_link_libraries(st_test.out _sequential)
target_link_libraries(st_test.out ${GTEST_LIBRARIES} pthread)

add_executable(dyn_test.out dyn_test.cpp)
target_link_libraries(dyn_test.out _parallel)
target_link_libraries(dyn_test.out ${GTEST_LIBRARIES} pthread)