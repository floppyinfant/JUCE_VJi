# C++ Tools

- Editor with Syntax Highlighting, Code Completion, Refactoring, etc.
- Toolchain: Compiler, Linker, Assembler, etc.
- Debugger, Profiler, etc.
- Build Systems: Make, etc.
- Code Generator (configure): CMake, Premake, etc.
- Version Control System: git, svn, etc.
- Code Analysis Tools, Formatters, Code Linters, Documentation Tools, Code Coverage Tools, Metrics Tools

actual Interests:
- Jetbrains CLion
- Microsoft Visual Studio
- CMake
- Modern C++
- GLSL
- ImGui

@see ~/README.md/Tutorials

@see Google Docs: Development 2025, C++, Creative Coding

## C++ Reference

https://cppreference.com/

https://cplusplus.com/reference/

Microsoft C++ Reference

https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170 (C/C++)

https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170 (Modern C++)

...


## IDEs

### Microsoft Visual Studio

https://visualstudio.microsoft.com/

https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B

https://learn.microsoft.com/en-us/cpp/?view=msvc-170 (Learn)

https://learn.microsoft.com/en-us/visualstudio/ide/?view=vs-2022 (Visual Studio)

https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170 (C/C++)

https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170 (Modern C++)

https://learn.microsoft.com/en-us/cpp/build/projects-and-build-systems-cpp?view=msvc-170

MSVC toolset

IntelliSense

*.sln, *.vcxproj

*.pdb

Configuration: Debug, Release

Project Properties: Includes, Link Libraries

Compiler Flags: -D (CMake options), -I (include directories), -L (library directories), -l (libraries), -std (C++ standard)

### Apple Xcode

### JetBrains CLion

https://www.jetbrains.com/clion/

https://www.jetbrains.com/clion/learn/

@see Clion_README.md

### Code::Blocks

### Qt Creator

### Eclipse CDT

### NetBeans

### Dev C++

### DevLite

### Kite


## Editors

### VScode

https://code.visualstudio.com/docs/cpp/introvideos-cpp

### Sublime Text

### Notepad++

### vim

### NeoVim


## Toolchains & Compiler

C++  toolchain (build tools): compiler, linker, standard libraries

### Microsoft Visual Studio

https://learn.microsoft.com/en-us/visualstudio/ide/compiling-and-building-in-visual-studio?view=vs-2022

https://learn.microsoft.com/en-us/cpp/build/projects-and-build-systems-cpp?view=msvc-170

MSVC toolset, MSBuild , cl.exe

### GNU Toolchain

https://en.wikipedia.org/wiki/GNU_Compiler_Collection

https://en.wikipedia.org/wiki/GNU_Debugger

https://gcc.gnu.org/

gcc, g++.exe, GDB, make

#### MingGW

https://en.wikipedia.org/wiki/MinGW

##### MSYS2

https://www.msys2.org/

#### MinGW-w64

https://www.mingw-w64.org/

#### Cygwin

https://cygwin.com/

#### WSL2

Windows Subsystem for Linux

https://learn.microsoft.com/en-us/cpp/build/walkthrough-build-debug-wsl2?view=msvc-170

https://code.visualstudio.com/docs/cpp/config-wsl

### LLVM Clang

clang++.exe

#### Clang Tidy

https://clang.llvm.org/extra/clang-tidy/

https://www.jetbrains.com/help/clion/clang-tidy-checks-support.html

https://learn.microsoft.com/de-de/cpp/code-quality/clang-tidy?view=msvc-170

### Intel C++ Compiler

icpc.exe

### NVIDIA C++ Compiler

nvcc.exe

---

## Tools

### CMake

https://cmake.org/

https://cmake.org/getting-started/

https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html

https://cmake.org/cmake/help/book/mastering-cmake/cmake/Help/guide/tutorial/

CMakeLists.txt example files see:
- JUCE
- VST_SDK, Will Pirkle
- Genesis LuisaRender compute (Python WS)

```shell
# Configure, Build, execute
cmake -S . -B build
cmake --build build
.\build\VJi_artefacts\Debug\Standalone\VJi.exe
```

### Premake

### GNU Make

### git

---

## Libraries

### libc

### Vulkan


### OpenGL

https://www.khronos.org/opengl/

https://registry.khronos.org/OpenGL-Refpages/

https://www.khronos.org/developers/reference-cards (PDFs)

https://www.opengl.org/Documentation/Specs.html

https://www.khronos.org/developers/books/

The OpenGL SuperBible

The OpenGL Programming Guide


#### GLSL

#### GLFW

https://www.glfw.org/

https://github.com/glfw/glfw

https://en.wikipedia.org/wiki/GLFW

Windowing and Input

#### Glew

https://github.com/nigels-com/glew

OpenGL Extension Wrangler

#### GLM

https://github.com/g-truc/glm

Math library

### Dear ImGui

https://github.com/ocornut/imgui

https://www.dearimgui.com/

https://pthom.github.io/imgui_bundle/

https://github.com/thecherno

https://github.com/StudioCherno/Walnut


### wxWidgets

wxFormBuilder: GUI Designer Application

https://github.com/wxFormBuilder/wxFormBuilder

