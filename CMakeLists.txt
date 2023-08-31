cmake_minimum_required(VERSION 3.22.1)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES 
    # src/main.cpp 
    src/matrix.hpp 
    src/color.cpp
    src/canvas.cpp
    src/transformations.cpp
    src/ray.cpp
    src/shapes.cpp
    src/light.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

# Get GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create tests
enable_testing()

set(TEST_SOURCES
    tests/matrix.test.cpp
    tests/color.test.cpp
    tests/canvas.test.cpp
    tests/transformations.test.cpp
    tests/ray.test.cpp
    tests/shapes.test.cpp
    tests/light.test.cpp
)

foreach(SRC IN LISTS TEST_SOURCES)
    cmake_path(GET SRC STEM TEST_NAME)
    list(APPEND TEST_EXECUTABLES ${TEST_NAME}.test)

    add_executable(${TEST_NAME}.test ${SRC} ${SOURCES})
    target_link_libraries(${TEST_NAME}.test GTest::gtest_main)
    target_include_directories(${TEST_NAME}.test PUBLIC src)
endforeach()

include(CTest)
include(GoogleTest)
foreach(TEST IN LISTS TEST_EXECUTABLES)
    gtest_discover_tests(${TEST})
endforeach()