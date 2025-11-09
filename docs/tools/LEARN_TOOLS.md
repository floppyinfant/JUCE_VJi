# LEARN Tools

## Development Environment

- Editor with Syntax Highlighting, Code Completion, Refactoring, ...
- Toolchain: Compiler, Linker, Assembler, ...
- Debugger, Profiler, ...
- Build Systems: Make, Ninja, Gradle, ...
- Code Generator (configure): CMake, Premake, ...
- Version Control System: git, svn, ...
- Code Analysis Tools, Formatters, Code Linters, Documentation Tools, Code Coverage Tools, Metrics Tools: clang-tidy, ...
- Package Manager: vcpkg, Pip, ...

tools used:
- Jetbrains CLion
- Microsoft Visual Studio
- Android Studio + NDK
- CMake
- git

---

## IDEs

---

### JetBrains CLion

https://www.jetbrains.com/clion/

https://www.jetbrains.com/clion/learn/

Tutorials
- https://www.jetbrains.com/help/clion/clion-quick-start-guide.html
- https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html (CMake Tutorial)
- https://www.jetbrains.com/help/clion/junie.html
- https://www.jetbrains.com/help/junie/get-started-with-junie.html (Junie Coding Agent)

#### Shortcuts

Menu Help > Keyboard Shortcuts.PDF

Shift Shift - Search everywhere

Ctrl + Shift + A - Show all actions

Alt + Enter - Quick fix

Ctrl + Space - Code completion

Ctrl + Shift Space - Parameter info

Alt + Insert -

Ctrl + Alt + J - Surround with Live Template



##### Editor Shortcuts

Shift + Alt + Click: select multiple lines



#### Settings

#### Plugins

---

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

https://www.youtube.com/watch?v=or1dAmUO8k0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb (The Cherno - C++ - Using Libraries)

Compiler Flags: -D (CMake options), -I (include directories), -L (library directories), -l (libraries), -std (C++ standard)



---

### Apple Xcode

### Code::Blocks

### Qt Creator

### Eclipse CDT

### NetBeans

### Dev C++

### DevLite

### Kite

---

## Editors

### VScode

https://code.visualstudio.com/docs/cpp/introvideos-cpp

### Sublime Text

### Notepad++

### vim

### NeoVim

---

## Toolchains & Compiler

C++ toolchain (build tools)
- compiler
- linker
- standard libraries

---

### Microsoft Visual Studio

https://learn.microsoft.com/en-us/visualstudio/ide/compiling-and-building-in-visual-studio?view=vs-2022

https://learn.microsoft.com/en-us/cpp/build/projects-and-build-systems-cpp?view=msvc-170

MSVC toolset, MSBuild , cl.exe

---

### LLVM Clang

clang++.exe

#### Clang Tidy

https://clang.llvm.org/extra/clang-tidy/

https://www.jetbrains.com/help/clion/clang-tidy-checks-support.html

https://learn.microsoft.com/de-de/cpp/code-quality/clang-tidy?view=msvc-170

---

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

Windows Subsystem for Linux (WSL2)

https://learn.microsoft.com/en-us/cpp/build/walkthrough-build-debug-wsl2?view=msvc-170

https://code.visualstudio.com/docs/cpp/config-wsl

---

### Intel C++ Compiler

icpc.exe

### NVIDIA C++ Compiler

nvcc.exe

---

## Generators and Build Systems

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

### Ninja

---

## Version Control Systems

### git

https://git-scm.com

https://git-scm.com/book/en/v2

@see Google Docs: Development 2025

#### Git Cheat Sheets
- https://education.github.com/git-cheat-sheet-education.pdfhttps://education.github.com/git-cheat-sheet-education.pdf
- https://git-scm.com/cheat-sheet
- https://www.atlassian.com/git/tutorials/atlassian-git-cheatsheet

---

#### Git Workflows

- Feature Branch Workflow
- Gitflow Workflow
- Forking Workflow
- ...
- Release branch
- Hotfix branch

https://www.atlassian.com/git/tutorials/comparing-workflows

https://docs.github.com/en/get-started/using-github/github-flow

https://uidaholib.github.io/get-git/3workflow.html (Beginner)

https://www.w3schools.com/git/git_workflow.asp (fix mistakes)

https://git-scm.com/book/de/v2/Git-Branching-Branching-Workflows

Pull requests (PR)

https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests

---

#### Git Hosting Services

Github
- https://github.com/
- Github Desktop
- Github Copilot
- Github Actions
- https://docs.github.com/en
- https://docs.github.com/en/get-started/learning-to-code
- https://github.com/collections/learn-to-code
- https://learn.github.com/
- https://docs.github.com/en/get-started/start-your-journey/git-and-github-learning-resources
- https://learn.microsoft.com/en-us/training/github/

GitLab
- https://about.gitlab.com/
- https://about.gitlab.com/install/ (self-hosted)

Bitbucket
- https://bitbucket.org/product/

Gitea (self-hosted)
- https://about.gitea.com/
- https://github.com/go-gitea/gitea

Gogs (self-hosted)
- https://gogs.io/

AWS CodeCommit

Google Cloud Source Repositories

---

### Subversion

svn

TortoiseSVN

Atlassian SourceTree

---

### Mercuial

hg

---

## CI/CD

Github Actions

Jenkins

?

---

