cmake_minimum_required(VERSION 3.17)

include(cmake/prelude.cmake)

project(
    RAII-Stopwatch
    VERSION 0.1.0
    DESCRIPTION "A simple RAII stopwatch for timing scope execution (e.g., functions, loops, etc.)"
    HOMEPAGE_URL "https://github.com/alexriegler/RAII-Stopwatch"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(RAII-Stopwatch_RAII-Stopwatch INTERFACE)
add_library(RAII-Stopwatch::RAII-Stopwatch ALIAS RAII-Stopwatch_RAII-Stopwatch)

set_property(
    TARGET RAII-Stopwatch_RAII-Stopwatch PROPERTY
    EXPORT_NAME RAII-Stopwatch
)

target_include_directories(
    RAII-Stopwatch_RAII-Stopwatch ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(RAII-Stopwatch_RAII-Stopwatch INTERFACE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${RAII-Stopwatch_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT RAII-Stopwatch_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of RAII-Stopwatch"
  )
endif()

include(cmake/dev-mode.cmake)
