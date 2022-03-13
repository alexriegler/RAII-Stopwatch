// This example uses the Stopwatch class to illustrate the performance
// difference between using std::endl and '\n'.
#include "RAII-Stopwatch/RAII-Stopwatch.h"

#include <iostream>
#include <source_location>
#include <sstream>

using namespace ar;

// Global
auto ss = std::stringstream{};

template <typename Units>
void long_function_endl()
{
  const auto location = std::source_location::current();
  Stopwatch<Units> s{location.function_name(), ss};
  std::ios::sync_with_stdio(false);
  for (int i = 0; i < 10'000; ++i)
  {
    std::cout << "Hello world" << std::endl;
  }
}

template <typename Units>
void long_function_n()
{
  const auto location = std::source_location::current();
  Stopwatch<Units> s{location.function_name(), ss};
  std::ios::sync_with_stdio(false);
  for (int i = 0; i < 10'000; ++i)
  {
    std::cout << "Hello world\n";
  }
}

int main()
{
  long_function_endl<std::milli>();
  long_function_n<std::milli>();

  std::cout << ss.str();
}
