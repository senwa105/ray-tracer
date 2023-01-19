cmake_minimum_required(VERSION 3.22.1)
project(gtest_primer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

add_library(raytracer
    src/matrix.h 
    src/matrix.cpp 
)

add_executable(app src/main.cpp)
target_link_libraries(app raytracer)

# Get GoogleTest
FetchContent_Declare(
    googletest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create tests
# enable_testing()

# add_executable(hello_test hello_test.cpp)
# target_link_libraries(hello_test GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(hello_test)