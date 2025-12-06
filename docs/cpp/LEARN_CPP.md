# C++ Language

https://www.youtube.com/watch?v=7fGB-hjc2Gc <================

@see Google Docs: Development 2025, C++, Creative Coding

https://en.wikipedia.org/wiki/C%2B%2B

https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library (std)

https://en.wikipedia.org/wiki/Standard_Template_Library (STL)

https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries) (Boost Library)

## C++ Online Compiler

https://godbolt.org/

https://onecompiler.com/cpp

https://www.programiz.com/cpp-programming/online-compiler/

https://www.onlinegdb.com/online_c++_compiler

https://www.w3schools.com/c/c_compiler.php

https://cpp.sh/

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

https://github.com/isocpp/CppCoreGuidelines (C++ Core Guidelines - GitHub)

https://github.com/cpp-best-practices/cppbestpractices (C++ Best Practices - GitHub)

https://lefticus.gitbooks.io/cpp-best-practices/content/ (C++ Best Practices - read ebook)

https://leanpub.com/cppbestpractices (C++ Best Practices - buy ebook)

https://docs.nvidia.com/cuda/pdf/CUDA_C_Best_Practices_Guide.pdf (CUDA C++ Best Practices Guide)

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

https://www.youtube.com/user/CppCon/videos (CppCon)

---

https://www.w3schools.com/cpp/

https://www.cpp-tutor.de/ (deutsch)

https://www.programiz.com/cpp-programming/online-compiler/ (Programiz Online-Compiler)

---

## C++ Standards

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

1. program structure
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
// include guards
#ifndef VJI_MAIN_H
#define VJI_MAIN_H
// or #pragma once

// CAVE with includes: cyclic dependencies
// resolve by using forward declaration (include in source file)
#ifdef JUCE_ANDROID  // JUCE_MAC, ...
#include <android/log.h>
#endif

#define PI 3.14159265358979323846

// Makros
#define ADD(a, b) a + b

// typedefs
typedef int INT;

// declarations: 
// function prototypes

// include guards
#endif //VJI_MAIN_H
```

#### Macros

#### includes

https://en.cppreference.com/w/cpp/standard_library.html

```c++
#include <iostream>         // cout, endl, ...
#include <fstream>          // ifstream, ofstream (filestream)

#include <functional>       // std::function, std::bind, lambda
#include <utility>          // std::move
#include <memory>           // std::unique_ptr, std::shared_ptr, std::weak_ptr
#include <thread>           // std::thread
#include <future>           // std::future, std::async
#include <chrono>           // std::chrono::system_clock::now()
#include <type_traits>      // static_assert

#include <string>           // std::string, std::to_string, std::getline, std::stoi, ...
#include <vector>           // std::vector
#include <array>            // std::array
#include <map>

#include <algorithm>        // std::sort, std::find, ...


// C-libraries for compatibility (have a '.h' at the end)
#include <stdio.h>
#include <string.h>


// for anything in your project folder use "double quotes"
#include "PluginEditor.h"  
```

#### Precompiled Header-Files (.pch)

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

### C-Language Code

@see LEARN_C.md

```c++
#ifdef __cplusplus
extern "C" {
#endif
// separate the C code from the C++ code
#ifdef __cplusplus
}
#endif
```

---

### Keywords

### Operators

#### Operator Precedence

#### Operator Overloading

```c++
class Entity {
public:
    Entity operator+(const Entity& other) const {
        return Entity(x + other.x, y + other.y);
    }
    Entity operator+=(const Entity& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
private:
    float x, y;
}
```

### Types

primitive types: 
- bool
- char, wchar_t, char16_t, char32_t
- short, int, long, long long
- uint32_t
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

@see Functions/Function Parameters

- References are aliases for objects
- They can't be reassigned
- pass by reference without creating a copy

#### const lvalue-References (const Type&)

- can bind to everything
- can't be modified (const-ness)
- in-parameters of functions

```c++
void foo(const Type&);
```

#### lvalues-References (Type&)

- only non-const named objects (lvalues)
- left side of assignment
- in-out-parameters of functions (write access)

```c++
void foo(Type&);
```

#### rvalue-References (Type&&)

- temporary objects 
- only objects without a name or std::move() passed as parameter to functions
- can't be assigned to

```c++
```

#### move-Semantics

https://www.youtube.com/watch?v=Bt3zcJZIalk

```c++
```

---

### Objects, Instantiation, Memory

#### Object Instantiation

@see snippets.cpp

Object creation (Instantiation):

```c++
// ... on the Stack
Entity e;
Entity e1(void);
Entity e2(1, 1);
Entity e3 = Entity(2, 2);

// ... on the Heap with raw pointers (must use 'delete' to free memory)
Entity* e4 = new Entity;
Entity* e5 = new Entity();  // Java style
Entity* e6 = (Entity*)malloc(sizeof(Entity));  // raw pointer C-style (use 'free' to free memory)
const Entity* e7 = new Entity();

// smart pointers
std::unique_ptr<Entity> e8 = std::make_unique<Entity>(1, 2);
e8.reset();
e8.reset(new Entity(2, 1));
Entity* e9 = e8.get();

// lvalue-References
Entity& e11 = Entity(3, 3);

// const References
const Entity& e12 = Entity(3, 3);

// rvalue-References
Entity&& e13 = Entity(3, 3);

// array instantiation
Entity a[3] = {Entity(1, 1), Entity(2, 2), Entity(3, 3)};
Entity* a2 = new Entity[3];
```

free memory, delete objects, call destructor, avoid memory leaks:

```c++
free(e6);       // does not call the destructor; always use delete
delete e5;
delete[] a;     // delete[] is only used for arrays
e8.reset();     // smart pointers: call destructor and free memory
```

#### Dynamic Memory Allocation

https://openframeworks.cc/ofBook/chapters/memory.html

https://www.geeksforgeeks.org/cpp/memory-layout-of-cpp-program/

- stack (local data)
- static memory (global data)
- heap (dynamically allocated data)

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

- Forward-Declaration of classes (without definition)
- Function without a Body is a Declaration (Prototype)
- static variables are initialized outside the class
- extern variables are defined in another translation unit
- typedef, using

#### Definition

most Declarations are Definitions (memory is allocated)

#### Initialization

##### RAII

Resource Acquisition Is Initialization

##### Initializer Lists

{}

() has pitfalls

```c++
int i = 0;
int i(0);
char c(260);    // Narrowing: char 8 bit == 256 values; hidden error not thrown
int i = {0};
int i{0};
int i{};        // default initialization: i = 0
```

```c++
int a[3] = {1,2,3};
int a[3]{1,2,3};

std::vector<int> v{1,2,3};

const int* pa = new const int[3]{1,2,3};
```

Constructor Initialization: member initializer list

```c++
class Entity {
public:
    Entity(float posX, float posY) : x{posX}, y{posY} {
        // constructor body
    }
private:
    float x;
    float y;
}
```

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

Closures: capture variables from the enclosing scope

```c++
[]          // capture nothing
[=]         // capture all by value (copy)
[&]         // capture all by reference
[this]      // capture this by reference
[*this]     // capture this by copy
[&x](int a, int b){ cout << x(a, b) << endl; }  // capture x by reference
[a]{a=5;};  // error, if a copy is modified
[a]() mutable {a=5;};  // ok, mutable allows a copy to be modified
```

Lamdas as function parameters:

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

##### lvalues, rvalues

@see References

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

##### move-semantics

use case of rvalue-references

https://www.youtube.com/watch?v=ehMg6zvXuMY

##### value-semantics

https://en.wikipedia.org/wiki/Value_semantics

https://isocpp.org/wiki/faq/value-vs-ref-semantics

copy-by-value semantics

##### copy-constructor

---

### const

const reference: accepts lvalues and rvalues

const with pointers:

```c++
const char* ptr        // pointer to a constant char
char* const ptr        // constant pointer to a char
const char* const ptr  // constant pointer to a constant char
```

const with functions / methods:

```c++
int f(const char* s) const {}
```

### static

static inside of classes: variable / function is independent of an instance; there is only one variable across all instances

static outside of classes: hides the variable

extern: variable is defined in another translation unit

### nullptr

### constexpr

### decltype

---

### expressions

### statements

- expression statements
- assignments
- for loops: `for (auto i = 0; i < 10; ++i)`
- foreach (range based for): `for (auto& element : vector)`
- while: while(true)
- do, while
- if, else
- switch, case, brake, continue
- return

### exceptions

- try, catch, throw
- noexcept

### templates

```c++
template <typename T>
T add(T& a, T& b) {
    return a + b;
}

template <typename T>
void print(T& value) {
    cout << value << endl;
}
```

---

### Standard Library

```c++
#include <iostream>
#include <memory>       // smart pointers
#include <functional>   // std::function

#include <string>
#include <vector>
#include <array>

std::string name;
std::cout << "Hello, World!" << std::endl;
std::cin >> name;
```

### Data Structures, Containers

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

https://www.programiz.com/cpp-programming/vectors

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

