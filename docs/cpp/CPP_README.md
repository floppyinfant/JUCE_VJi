# C++ Language

@see Google Docs: Development 2025, C++, Creative Coding

https://en.wikipedia.org/wiki/C%2B%2B

https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library (std)

https://en.wikipedia.org/wiki/Standard_Template_Library (STL)

https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries) (Boost Library)

## C++ Reference

https://cppreference.com/

https://cplusplus.com/reference/

Microsoft C++ Reference

https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170 (C/C++)

https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170 (Modern C++)

## Modern C++

https://isocpp.org/std/the-standard

C++ 1985 by Bjarne Stroustrup at AT&T Bell Labs

C++ 98, 03
- Standard Template Library (STL) 
- Strings 
- IO-Streams

Modern C++:

C++ 11, 14, 17

C++ 20, 23, (26) 

https://en.wikipedia.org/wiki/C%2B%2B11

C++11 standard
- smart pointers (std::shared_ptr, std::unique_ptr = ... std::make_unique)
- initializer lists
- move-semantics (std::move)
- auto keyword (type inference)
- constexpr
- threads
- regular expressions
- random number generation
- rational arithmetic (ratio)
- tuples
- range-based for loops
- lambda expressions: []() -> int { return 0; }
- virtual function override
- nullptr
- R"()" (raw string)

C++14 standard

C++17 standard
- file system API
- any types (std::any)
- option types (std::optional)
- variant types (std::variant)
- string views (std::string_view)

C++20 standard
- coroutines (async)
- modules
- ranges
- concepts

https://en.wikipedia.org/wiki/C%2B%2B23

C++ 23 standard
- println (import <print>;)

https://www.heise.de/blog/C-26-wir-der-naechste-grosse-C-Standard-9837334.html

C++26 standard
- std::execution (asynchron)
- reflection
- contracts

---

## Notes

### smart pointers

### RAII

### initializer lists

### function parameters

pass by value, pass by reference

pass by const reference
pass by value & std::move

### strings

const char* c-string // null-terminated
std::string stdString
juce::String juceString
R"()" // Raw-String (multiline)
Unicode Strings


```c++
#include <iostream>

int main()
{
std::cout << "Hello, world!\n";
}
```

```c++
// C++23
import std;

int main() {
    std::println("Hello, world!");
}
```

```c++

```
