cmake_minimum_required(VERSION 3.22.1)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(SOURCES 
    src/main.cpp 
    src/matrix.hpp 
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Get GoogleTest
FetchContent_Declare(
    googletest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create tests
enable_testing()

add_executable(matrix_test src/matrix.test.cpp)
target_link_libraries(matrix_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_test)