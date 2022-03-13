cmake_minimum_required(VERSION 3.14)

project(RAII-StopwatchTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(RAII-Stopwatch REQUIRED)
  enable_testing()
endif()

# Catch2
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

add_executable(RAII-Stopwatch_test RAII-Stopwatch_test.cpp)
target_include_directories(RAII-Stopwatch_test PRIVATE RAII-Stopwatch_test.h)
target_link_libraries(RAII-Stopwatch_test
  PRIVATE
    RAII-Stopwatch::RAII-Stopwatch
    Catch2::Catch2
)
target_compile_features(RAII-Stopwatch_test PRIVATE cxx_std_20)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/contrib)
include(Catch)
catch_discover_tests(RAII-Stopwatch_test)

add_folders(Test)
