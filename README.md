# RAII-Stopwatch
RAII-Stopwatch is a single-header C++ library that provides a `Stopwatch` class,
that can be used to time the execution of a [scope][scope]. The `Stopwatch`
class uses the [RAII (Resource Acquisition Is Initialization)][raii] programming
technique. In other words, when a `Stopwatch` object is constructed, the timer
begins; and, when that `Stopwatch` object is destructed, the timer ends and the
elapsed duration is output to the provided logging stream (`std::cout`, by
default).

## Table of contents
- [Installation](#installation)
- [Usage](#usage)
  - [Quick start](#quick-start)
  - [Change the logging stream](#change-the-logging-stream)
  - [Change the unit of time](#change-the-unit-of-time)
  - [Advanced usage](#advanced-usage)
- [Examples](#examples)
- [Contribute](#contribute)
- [License](#license)
- [Acknowledgements](#acknowledgements)
- [TODO](#todo)

## Installation
The easiest way to install and use this library is to use CMake's
[`FetchContent`][FetchContent] module. With this module, you can use
`FetchContent_Declare` and `FetchContent_MakeAvailable` to integrate this
library with your CMake project.

```cmake
cmake_minimum_required(VERSION 3.14)  # For FetchContent_MakeAvailable

# Get the RAII-Stopwatch library
include(FetchContent)
FetchContent_Declare(
    RAII-Stopwatch
    GIT_REPOSITORY https://github.com/alexriegler/RAII-Stopwatch.git
    GIT_TAG        <most-recent-commit-sha>
)
FetchContent_MakeAvailable(RAII-Stopwatch)
```

Then you'll also need to link your target with this library:
```cmake
# Declare the imported target as a build requirement using PRIVATE
target_link_libraries(
    project_target PRIVATE
    RAII-Stopwatch::RAII-Stopwatch
)
```

For alternative installation methods, see [Building with CMake](./BUILDING.md).

## Usage
The `Stopwatch` class is contained in the `ar` namespace. This class is
conceptually similar to other RAII-based classes, like, `std::lock_guard` and
`std::fstream`. If you'd like to get an idea of how to use the `Stopwatch`
class, take a look at the examples below.

### Quick start
Create a `Stopwatch` object right before the code you'd like to time.

In the example below, the `Stopwatch` named `s` measures the execution time of
the `main` function. In this example, the `Stopwatch`'s name is `"main"` (the
first argument of `Stopwatch`'s constructor). This name is used when the
`Stopwatch` object outputs the elapsed time to the logging stream (`std::cout`,
by default).

#### Code:
```cpp
#include "RAII-Stopwatch/RAII-Stopwatch.h"

int main() {
    ar::Stopwatch s{ "main" };  // Timer starts
    // Do ~2s of work...
}                               // Timer ends
```

#### Output:
```sh
main: 2s
```

### Change the logging stream
By default, the `Stopwatch` class logs the elapsed time to `std::cout`. This
behavior can be overridden by passing a `std::ostream` object (for example,
`std::cout` or an instance of `std::stringstream` or `std::fstream`) as the
second parameter of the constructor. When a `Stopwatch` object is destroyed, it
outputs the elapsed time to the passed in `std::ostream` object.

In the example below, the `Stopwatch` object, `s`, measures the execution time
of the function `foo`. The `Stopwatch`, `s`, has the name `"foo"` and uses the
`logger`, a `std::stringstream`, as its output stream. In the `main` function,
there is a call to the `foo` function and then the contents of `logger` are
printed to `std::cout`.

#### Code:
```cpp
#include "RAII-Stopwatch/RAII-Stopwatch.h"

#include <iostream>  // std::cout
#include <sstream>   // std::stringstream

std::stringstream logger{};

void foo() {
    ar::Stopwatch s{ "foo", logger };  // Timer starts
    // Do ~2s of work...
}                                      // Timer ends

int main() {
    foo();
    std::cout << logger.str();  // Print the logger's contents
}
```

#### Output:
```sh
foo: 2s
```

### Change the unit of time
The `Stopwatch` class uses the second as the default unit of time when printing
the elapsed time. Since the `Stopwatch` class is a template class with the unit
of time as a template parameter, you can change the unit of time by creating an
instance of the `Stopwatch` class with a different template parameter. The class
expects the template argument to be a `std::ratio` type.

In the example below, `Stopwatch<std::milli>` is a template instantiation of the
`Stopwatch` class using `std::milli` (a convenience typedef for
`std::ratio<1, 1000>`) as the template argument. This template instantiation of
`Stopwatch` will output the elapsed time in milliseconds (ms) instead of the
default seconds (s).

#### Code:
```cpp
#include "RAII-Stopwatch/RAII-Stopwatch.h"

#include <ratio>  // std::milli

int main() {
    ar::Stopwatch<std::milli> s{ "main" };  // Timer starts
    // Do ~2s of work...
}                                           // Timer ends
```

#### Output:
```sh
main: 2000ms
```

See cppreference.com's page on [`std::ratio`][ratio] for other convenience
typedefs like `std::milli`.

### Advanced usage
You can combine many of the features of the `Stopwatch` class together to make
something that fits your specific needs.

In the example below, the `Stopwatch`, `s`, logs the execution times, in
milliseconds, to a `std::fstream`, `logger`.

#### Code:
```cpp
#include "RAII-Stopwatch/RAII-Stopwatch.h"

#include <fstream>   // std::fstream
#include <iostream>  // std::cout
#include <ratio>     // std::milli

std::fstream logger{ "log.txt", std::ios::out | std::ios::ate };

void foo() {
    ar::Stopwatch<std::milli> s{ "foo", logger };  // Timer starts
    // Do ~2s of work...
}                                                  // Timer ends

int main() {
    // Call foo() five times
    for (auto i = 0; i < 5; ++i) {
        foo();
    }
}
```

#### Output (`log.txt`):
```sh
foo: 2000ms
foo: 2000ms
foo: 2000ms
foo: 2000ms
foo: 2000ms
```

## Examples
Here's an example of using `ar::Stopwatch`.
* [Timing `std::endl` vs. `'\n'`](./example/example.cpp)

## Contribute
Feel free to create issues and/or pull requests!

## License
This project is licensed under the MIT license. See [License](./LICENSE) for
full details.

## Acknowledgements
This project used [`cmake-init`][cmake-init] to create the basic CMake structure
for the project.

[scope]: https://en.cppreference.com/w/cpp/language/scope
[raii]: https://en.cppreference.com/w/cpp/language/raii
[FetchContent]: https://cmake.org/cmake/help/latest/module/FetchContent.html
[ratio]: https://en.cppreference.com/w/cpp/numeric/ratio/ratio
[cmake-init]: https://github.com/friendlyanon/cmake-init

## TODO:
* Test "Usage" code examples.
* Add clang-format file.
* Add clang-tidy file.
