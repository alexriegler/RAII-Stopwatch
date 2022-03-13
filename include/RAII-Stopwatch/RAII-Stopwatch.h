#pragma once

#include <chrono>
#include <iostream>

namespace ar
{
    /**
     * @brief A simple RAII stopwatch for timing scope execution.
     *
     * This class starts a timer at construction and, at destruction, stops the
     * timer and prints the elapsed duration.
     *
     * @tparam Units The units of time to use. By default, seconds.
     */
    template <typename Units = std::ratio<1>>
    class Stopwatch
    {
    public:
        // Type aliases
        using Time = std::chrono::time_point<std::chrono::steady_clock>;

        // Constructor
        // TODO: Make the default name of the timer the name of the calling...
        //       function. Use <source_location>.
        /**
         * @brief Constructs a new Stopwatch object and starts its timer.
         *
         * @param name The name of the Stopwatch. Used when outputting the elapsed
         *             time.
         * @param os The output stream used to output the elapsed time. By default,
         *           std::cout.
         */
        Stopwatch(std::string name, std::ostream& os = std::cout)
            : m_name{ std::move(name) },
            m_os{ os },
            m_start{ std::chrono::steady_clock::now() } {}

        // Destructor
        /**
         * @brief Destroys the Stopwatch object, stops the timer, and outputs the
         *        elapsed time to the logging output stream.
         *
         */
        ~Stopwatch()
        {
            const Time m_end{ std::chrono::steady_clock::now() };
            // TODO: Is long double good here?
            const std::chrono::duration<long double, Units> elapsed_time = m_end - m_start;
            m_os << m_name << ": " << elapsed_time << '\n';
        }

        // Delete copy constructor and copy assignment operator (i.e., non-copyable object).
        // Delete means these functions cannot be called anywhere (compiler error will occur).
        Stopwatch(const Stopwatch& other) = delete;
        Stopwatch& operator=(const Stopwatch& other) = delete;

        // Default move constructor and move assignment operator.
        Stopwatch(Stopwatch&& other) noexcept = default;
        Stopwatch& operator=(Stopwatch&& other) noexcept = default;

    private:
        std::string m_name{};
        std::ostream& m_os{};
        Time m_start{};
    };
}
