#pragma once

#include <charconv>
#include <chrono>
#include <string_view>
#include <thread>

namespace ar
{
    // Constants
    /**
     * @brief Represents the numeric digits, 0-9.
     *
     */
    static inline constexpr auto digits = std::string_view{ "0123456789" };

    // Utilities
    /**
     * @brief Sleep for the specified duration.
     *
     * @tparam Rep      The type of the count of ticks
     * @tparam Period   The type of the tick period
     * @param duration  The duration to sleep for
     */
    template<typename Rep, typename Period>
    void sleep(const std::chrono::duration<Rep, Period>& duration)
    {
        std::this_thread::sleep_for(duration);
    }

    /**
     * @brief Checks if the passed in string contains a floating point value
     * that is approximately equal to the passed in floating point number.
     *
     * @param actual_str    The actual floating point value, in string form
     * @param expected_val  The expected floating point value as a floating
     *                      point number
     * @param max_error     The maximum difference between the actual and
     *                      expected floating point values
     * @return true, if the values are approximately equal; false, otherwise
     */
    bool approx_equal(std::string_view actual_str,
                      double expected_val,
                      double max_error = 20.0)
    {
        auto actual_stripped = actual_str.substr(
            actual_str.find_first_of(digits),
            actual_str.size()
        );
        double actual_val{};
        auto [ptr, ec] {
            std::from_chars(
                actual_stripped.data(),
                actual_stripped.data() + actual_stripped.size(),
                actual_val
            )
        };
        if (ec == std::errc())
        {
            const auto difference = actual_val - expected_val;
            return difference >= 0 && difference < max_error;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Checks if the passed in string contains a duration that is
     * approximately equal to the expected duration.
     *
     * @param actual_str    The actual duration, in string form
     * @param expected_val  The expected duration
     * @param max_error     The maximum difference between the actual and
     *                      expected durations
     * @return true, if the durations are approximately equal; false, otherwise
     */
    bool approx_equal(std::string_view actual_str,
                      const std::chrono::milliseconds& expected_val,
                      double max_error = 20.0)
    {
        return approx_equal(actual_str, expected_val.count(), max_error);
    }
}
