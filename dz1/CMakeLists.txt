cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(FILES
        io.c
        mem.c
        func.c)
add_library(_files STATIC ${FILES})

add_executable(main.out main.c)
target_link_libraries(main.out _files)

add_executable(test.out test.cpp)
target_link_libraries(test.out _files)
target_link_libraries(tests.out ${GTEST_LIBRARIES} pthread)
