#include "RAII-Stopwatch/RAII-Stopwatch.h"
#include "RAII-Stopwatch_test.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>
#include <ratio>
#include <sstream>

// Namespace usings
using namespace ar;
using namespace std::string_view_literals;

// Type aliases
using StopwatchMs = Stopwatch<std::milli>;

// Constants
static inline constexpr auto s_name = "Stopwatch"sv;
static inline constexpr auto s_duration = std::chrono::milliseconds{ 42 };

/**
 * @brief Stopwatch elapsed time is accurate. Checks if the elapsed time is
 * equal to or greater than the expected duration, within a tolerance.
 */
TEST_CASE("Elapsed time is accurate", "[Stopwatch]")
{
    std::stringstream ss{ "" };
    {
        StopwatchMs s{ s_name.data(), ss };
        sleep(s_duration);
    }
    REQUIRE(approx_equal(ss.str(), s_duration));
}

/**
 * @brief Stopwatch output is formatted correctly. Checks if the output placed
 * into the logging stream is formatted correctly.
 */
TEST_CASE("Output is formatted correctly", "[Stopwatch]")
{
    std::stringstream ss{ "" };
    {
        StopwatchMs s{ s_name.data(), ss };
        sleep(s_duration);
    }
    // Using regex to check output format:
    // Format: "<name>: <floating-point>ms\n"
    // Example: "Stopwatch: 46.1595ms\n"
    // Floating point regex: https://stackoverflow.com/a/12643073
    constexpr auto floating_point_expr = "[+-]?([0-9]*[.])?[0-9]+"sv;
    constexpr auto units_expr = "ms"sv;
    auto regex_ss = std::stringstream{ "" };
    regex_ss << '^' << s_name << ": " << floating_point_expr << units_expr
             << "\\n$";
    const std::regex output_regex{ regex_ss.str() };
    REQUIRE(std::regex_match(ss.str(), output_regex));
}
