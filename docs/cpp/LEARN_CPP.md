# C++ Language

@see Google Docs: Development 2025, C++, Creative Coding

https://en.wikipedia.org/wiki/C%2B%2B

https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library (std)

https://en.wikipedia.org/wiki/Standard_Template_Library (STL)

https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries) (Boost Library)

## C++ Reference

https://cppreference.com/

https://cplusplus.com/reference/

https://isocpp.org/get-started

https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170 (Microsoft C++)

https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170 (Modern C++)

https://code.visualstudio.com/docs/languages/cpp (VScode)

## C++ Best Practices

https://google.github.io/styleguide/cppguide.html (Google C++ Style Guide)

https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines (C++ Core Guidelines, Bjarne Stroustrup, Herb Sutter)

https://github.com/isocpp/CppCoreGuidelines

https://github.com/cpp-best-practices/cppbestpractices (C++ Best Practices)

https://lefticus.gitbooks.io/cpp-best-practices/content/

https://leanpub.com/cppbestpractices

https://docs.nvidia.com/cuda/pdf/CUDA_C_Best_Practices_Guide.pdf

## C++ Books

https://github.com/yuchdev/CppBooks

https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list

https://medium.com/@Code_Analysis/collecting-the-best-c-practices-4b867006849f

https://github.com/rigtorp/awesome-modern-cpp

---

Modern C++ Tutorial: C++11/14/17/20 On the Fly

https://github.com/changkun/modern-cpp-tutorial

https://github.com/federico-busato/Modern-CPP-Programming

(Effective C++: 55 Specific Ways to Improve Your Programs and Designs, 3. Ed., Scott Meyers, 2005)

(More Effective C++: 35 New Ways to Improve Your Programs and Designs, Scott Meyers, 1996)

Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14, Scott Meyers, 2014

Modern C++ Design, Andrei Alexandrescu

Modern C++ Programming Cookbook: Master Modern C++ with comprehensive solutions for C++23 and all previous standards

C++ High Performance: Master the art of optimizing the functioning of your C++ code, Björn Andrist, Viktor Sehr

C++ Concurrency in Action, Anthony Williams, 2019

Beautiful C++: 30 Core Guidelines for Writing Clean, Safe, and Fast Code, 2021

Modern CMake for C++: Effortlessly build cutting-edge C++ code and deliver high-quality solutions, 2024

## C++ Tutorials

https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb (The Cherno - C++)

https://www.youtube.com/watch?v=MNeX4EGtR5Y (C++ in 100 Seconds)

https://www.youtube.com/watch?v=8jLOx1hD3_o (C++ in 31 hours)

https://www.youtube.com/watch?v=_apAsU9ROp0 (C++ in 60 minutes, deutsch)

(CppCon)

---

https://www.w3schools.com/cpp/

https://www.cpp-tutor.de/ (deutsch)

https://www.programiz.com/cpp-programming/online-compiler/ (Programiz Online-Compiler)

---

### C++ Standards

https://isocpp.org/std/the-standard

C++ 1985 by Bjarne Stroustrup at AT&T Bell Labs

C++ 98, 03
- Standard Template Library (STL) 
- Strings 
- IO-Streams

Modern C++ 11, 14, 17, 20, 23, (26) 

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
- lambda expressions: `[]() -> int { return 0; }`
- virtual function override
- nullptr
- R"()" (raw string)
- ...

C++14 standard

C++17 standard
- file system API
- any types (std::any)
- option types (std::optional)
- variant types (std::variant)
- string views (std::string_view)
- ...

C++20 standard
- coroutines (async)
- modules
- ranges
- concepts
- ...

https://en.wikipedia.org/wiki/C%2B%2B23

C++ 23 standard
- println (import <print>;)
- ...

https://www.heise.de/blog/C-26-wir-der-naechste-grosse-C-Standard-9837334.html

C++26 standard
- std::execution (asynchron)
- reflection
- contracts
- ...

---

## C++ Pocket Reference

1. program structure: 
   - header files, preprocessor, macros
   - source files, main function, compiler
   - linker, libraries
   - toolchain, IDE Setup, CMake --> [@see LEARN_TOOLS.md](LEARN_TOOLS.md)
2. identifiers, keywords, literals, operators, expressions
3. types
4. statements
5. exception handling
6. assertions
7. namespaces
8. functions
9. classes
10. object-oriented programming
11. templates
12. standard library --> [@see LEARN_LIBRARIES.md](LEARN_LIBRARIES.md)
    - concurrency

---

### Compiler, Linker

https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html

```bash
g++ -std=c++17 -Wall -Wextra -pendantic -lm -Llibs -Iincludes -Dflag=1 snippets.cpp -o snippets.exe
```

-Wall: all warnings, -Wextra: extra warnings, -pendantic: all warnings as errors

-lm: link math library, -lpthread: link pthread library

-Llibs: link shared libraries (*.dll, *.so, *.dylib) in libs folder

-Iincludes: include headers in includes folder

-Dflag=1: #define flag=1 (preprocessor)

*.cpp: source files

-o snippets.exe: output file name

### Header Files

@see snippets.h

```c++
#pragma once
#define PI 3.14159265358979323846
// Makros
#define ADD(a, b) a + b
#ifdef JUCE_ANDROID
#include <android/log.h>
#endif
```

### Source Files

@see snippets.cpp

```c++
#include <iostream>
#include "snippets.h"
int main(int argc, char* argv[]){
    std::cout << "Program name: " << argv[0] << "\n";
    std::cout << "Program arguments: ";
    for(int i = 1; i < argc; i++){
        std::cout << argv[i] << " ";
    }
    std::cout << "\n";
    std::cin.get();
    return 0;
}
```

---

### Types

primitive types: 
- bool
- char, wchar_t, char16_t, char32_t
- short, int, long, long long
- float, double, long double
- void

reference types: 
- enum
- C-Arrays (a[])
- C-Strings (const char*, char*)
- Pointer (*ptr, std::unique_ptr, std::shared_ptr, std::weak_ptr)
- References (&ref)
- Classes, Structs, Unions
- Functions (std::function, std::bind, (*func)(...) = func, lambdas [](){})

---

### Pointers

#### RAW-Pointers (C-Pointers)

```c++
void* ptr = malloc(1024);
```

##### Pointer-Arithmetics

##### void-Pointer

can point to any type

`void* p = &c;`

##### Null-Pointer

`nullptr`

#### Smart Pointers

```c++
std::unique_ptr<String> strPtr = std::make_unique<String>();

std::shared_ptr<String> strPtr = std::make_shared<String>();

std::weak_ptr<String> strPtr = std::weak_ptr<String>();
```

### References

- References are aliases for objects
- They can't be reassigned

---

### Objects, Instantiation, Memory

Memory allocation
- stack
- heap

```c++
// Stack memory allocation
String str;
String str = String();
```

```c++
// Heap memory allocation
String* strPtr = new String();
delete str;

char** strPtr = nullptr;
```

#### Declaration

#### Initialization

##### RAII

Resource Acquisition Is Initialization

##### Initializer Lists

{}

() has pitfalls

constructor initialization

---

### Functions

- functions are defined outside of classes or functions
- methods are defined inside classes

#### Function Pointers

https://www.w3schools.com/c/c_functions_pointers.php

```c++
int (*ptr)(int, int);
ptr = &add;
(*ptr)(5, 3);
```

#### Lambdas

https://www.w3schools.com/cpp/cpp_functions_lambda.asp

type: `std::function<void()>`

```c++
auto l = []() { return 0; };

[]() { alert(); }                    // Basic lambda (no capture, no parameters, no explicit return type)
[this]() { alert(); }                // Lambda with capture (capturing this)
[]() -> void { alert(); }            // Lambda with explicit return type

// capture 'all by reference' can be risky if the lambda outlives the scope, as it might reference destroyed objects
[&](const juce::String& message) -> void { alert("Title", message); }

// [this] captures the this-pointer (needed to call the member function alert)
[this](const juce::String& title, const juce::String& message) { alert(title, message); }
// this lambda is essentially just forwarding the call to alert without doing anything else.
// In such cases, you might want to consider if you really need the lambda at all, or if you could pass a function pointer or use std::bind

// 1.
std::bind(&UI::alert, this, "Hello", "world!")
// 2.
std::mem_fn(&UI::alert)               // Using Member Function Pointer (If API Supports It)
// 3.
auto lam = [this](const juce::String& title){alert(title, "World!")};
subMenuHelp.addItem("about", lam("Hello "));
```

capture by reference: `[&x](int a, int b){ cout << x(a, b) << endl; }`

```c++
#include <iostream>
#include <functional> // Needed for std::function
using namespace std;

// A function that takes another function as parameter
void myFunction(function<void()> func) {
    func();
}

int main() {
    auto message = []() {
        cout << "Hello World!\n";
    };

    myFunction(message);
    return 0;
}
```

#### Function Parameters

- pass by value
- pass by reference
- pass by const reference
- pass by rvalue reference
- pass by value & std::move

C-Functions always pass by value (if you pass a pointer, the pointer is copied, not the object it points to)

#### lvalues, rvalues

https://youtu.be/fbYknr-HPYE?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&t=749

lvalues are variables that have a memory address

rvalues are temporary objects

lvalue-references (&) can only take in lvalues (unless they are const)

rvalue-references (&&) can only take in rvalues

```c++
#include <iostream>
#include <string>

// pass by value (copy):
// this function can be called with both lvalues and rvalues
void printName(std::string name)
{
    std::cout << "[value]: " << name << std::endl;
}

// pass by reference:
// lvalue-references can only take in lvalues
void printName(std::string& name)
{
    std::cout << "[lvalue-ref]: " << name << std::endl;
}

// most common use case:
// const lvalue-references can take in lvalues and rvalues
void printName(const std::string& name)
{
    std::cout << "[const lvalue-ref]: " << name << std::endl;
}

// rvalue-references can only take in rvalues
void printName(std::string&& name)
{
    // name is an temporary object
    std::cout << "[rvalue-ref]: " << name << std::endl;
}

int& getValue() {
    static int value = 5;
    return value;
}

int main() {
    std::string s = "Hello ";
    std::string s2 = "World!";
    std::string s3 = s + s2;
    
    printName(s2);      // this is an lvalue
    printName(s + s2);  // this is an rvalue (temp object)
    
    int i = 10;         // i is an lvalue, 10 is an rvalue 
    // 10 = i;          // you can not assign something to an rvalue (because it has no memory address)
    getValue() = 10;    // you can assign something to an lvalue-reference
    
    // this is generated from AI:
    std::string& sRef = s;
    const std::string& sConstRef = s;
    std::string&& sRValue = std::move(s);
    
    printName(s);
    printName(sRef);
    printName(sConstRef);
    printName(sRValue);
    
    return 0;
}
```

#### move-semantics

use case of rvalue-references

https://www.youtube.com/watch?v=ehMg6zvXuMY

#### value-semantics

https://en.wikipedia.org/wiki/Value_semantics

https://isocpp.org/wiki/faq/value-vs-ref-semantics

copy-by-value semantics

#### copy-constructor

---

### const

const reference: accepts lvalues and rvalues

const with pointers:
- `const char* ptr`        // pointer to a constant char
- `char* const ptr`        // constant pointer to a char
- `const char* const ptr`  // constant pointer to a constant char

```c++
int f(const char* s) const {}
```

### static

static inside of classes: variable / function is independent of an instance; there is only one variable across all instances

static outside of classes: hides the variable

extern: variable is defined in another translation unit

---

### Data Structures

#### Strings

Strings in C++:

```c++
// C-String
const char* c-string // null-terminated
```

```c++
// C++-String
std::string stdString
```

```c++
// JUCE-String type
juce::String juceString
```

Unicode Strings

```c++
// Raw-Strings (multiline, may contain escape sequences)
R"(text is
here\n)"

// Raw-String with separator (may contain ")
R"separator(text with "")separator"
```

String Concatenation:

```c++
// String concatenation
std::string str = "void main()\n"
"{\n"
"    vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);\n"
"    vec4 colour2 = vec4 (0.0, 0.8, 0.6, 1.0);\n"
"    float alpha = pixelPos.x / 1000.0;\n"
"    gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);\n"
"}\n"

// String concatenation with +=
std::string str = "Hello, ";
str += name;

// String concatenation with +
std::string str = "Hello, " + name;

// String on multiple lines
std::string str = "Hello, \\
World!";
```

Print character streams to the console:

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

#### Vector

```c++
std::vector<T>
```

#### Arrays

C-Arrays

```c++
a[] = {1, 2, 3};
```

```c++
std::array<T>
```

---

### Paradigms

Procedural Programming (PP): C functions, loops, conditionals

Object Oriented Programming (OOP): Classes, Objects, Inheritance

Functional Programming (FP): Higher-Order Functions, Lambdas, Closures

Generic Programming (GP): Templates, Type Traits, Metaprogramming

---

```c++

```

---

```c++

```

---

