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

Microsoft C++ Reference

https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170 (C/C++)

https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170 (Modern C++)

https://code.visualstudio.com/docs/languages/cpp (VScode)

https://google.github.io/styleguide/cppguide.html (Google C++ Style Guide)

## C++ Tutorials

https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb (The Cherno)

https://www.youtube.com/watch?v=MNeX4EGtR5Y (C++ in 100 Seconds)

https://www.youtube.com/watch?v=8jLOx1hD3_o (C++ in 31 hours)

https://www.youtube.com/watch?v=_apAsU9ROp0 (C++ in 60 minutes, deutsch)

(CppCon)

https://www.w3schools.com/cpp/

https://www.cpp-tutor.de/ (deutsch)

https://www.programiz.com/cpp-programming/online-compiler/ (Programiz Online-Compiler)

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

### Standards

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

## Notes

### Objects, Instantiation, Memory

String str;

String str = String();

String* strPtr = new String();

delete str;

char** strPtr = nullptr;

void* ptr = malloc(1024);

### Smart Pointers

std::unique_ptr<String> strPtr = std::make_unique<String>();

std::shared_ptr<String> strPtr = std::make_shared<String>();

std::weak_ptr<String> strPtr = std::weak_ptr<String>();

### RAII

### Initializer Lists

### function parameters

pass by value

pass by reference

pass by const reference

pass by value & std::move

### Strings

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

---

### functions, function pointers, lambdas

functions are defined outside of classes or functions

methods are defined inside classes

#### function pointers

https://www.w3schools.com/c/c_functions_pointers.php

int (*ptr)(int, int);

ptr = &add;

(*ptr)(5, 3);

#### Lambdas

https://www.w3schools.com/cpp/cpp_functions_lambda.asp

auto l = []() { return 0; };

type: std::function<void()>

capture by reference: [&x](int a, int b){ cout << x(a, b) << endl; }

```c++
#include <iostream>
#include <functional> // Needed for std::function
using namespace std;

// A function that takes another function as parameter
void myFunction(function<void()> func) {
func();
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

---

### lvalues, rvalues

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

### move-semantics

use case of rvalue-references

https://www.youtube.com/watch?v=ehMg6zvXuMY

---

### const

const reference: accepts lvalues and rvalues

const with pointers:
- const char* ptr        // pointer to a constant char
- char* const ptr        // constant pointer to a char
- const char* const ptr  // constant pointer to a constant char

---

### static

static inside of classes: variable / function is independent of an instance; there is only one variable across all instances

static outside of classes: hides the variable

extern: variable is defined in another translation unit

---

```c++

```
