cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(_sequential STATIC static.c extra_func.c)
add_library(_parallel SHARED dynamic.c extra_func.c)
# add_library(_parallel MODULE dynamic.c extra_func.c)

add_executable(main.out main.c)
target_link_libraries(main.out _sequential)
target_link_libraries(main.out _parallel)
# set(CMAKE_MODULE_PATH, 
#    ${CMAKE_MODULE_PATH}, 
#    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/”)
# find_package(_parallel MODULE REQUIRED)
# target_include_directories(main.out ${MYLIB_INCLUDE_DIRS})
# target_link_libraries(main.out ${MYLIB_LIB})

add_executable(test.out test.cpp)
target_link_libraries(test.out _sequential)
target_link_libraries(test.out _parallel)
target_link_libraries(test.out ${GTEST_LIBRARIES} pthread)