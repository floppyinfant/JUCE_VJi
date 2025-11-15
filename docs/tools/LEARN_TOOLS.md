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

Menu | Help | Keyboard Shortcuts PDF

```
Ctrl + Shift + A            Find Action (Keyboard Shortcut)
Double Shift                Search Everywhere
Alt + Enter                 Show Intention Actions and Quick Fixes
Ctrl + Space                Code Completion

Shift + Alt + Mouse Click   Select Multiple Lines

Ctrl + Shift + Backspace    Last edit location
F10                         Toggle Header / Source
Ctrl + F12                  Structure View
Ctrl + Q                    Quick Documentation Lookup
Ctrl + D                    Duplicate Line  
Delete Line
Move Line
Tab                         Correct Indentation for selected lines
Ctrl + Alt + I              Auto-Indent Lines
Ctrl + Alt + L              Reformat Code
Ctrl + Alt + T              Surround with ...
Ctrl + O                    Override Functions
Ctrl + I                    Implement Functions
```

#### Settings

- Settings | Build, Execution, Deployment | Toolchains: add "Visual Studio 2022"
- Settings | Build, Execution, Deployment | CMake: add CMake Profile "Debug-Visual Studio" (Generator Ninja)
- Settings | Editor | General | Appearance: uncheck the option "Show intention bulb" (Alt + Enter shows the same dialog)

#### Plugins

#### Profiler

Profiler Support is not available for Windows. But Linux (WSL2).

WSL2 Toolchain:
- https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html

```shell
# ubuntu@PC (WSL2)
sudo apt-get update
sudo apt-get install cmake gcc clang gdb build-essential pkg-config
```

- Settings | Build, Execution, Deployment | Toolchains: add WSL2

JUCE Linux Dependencies:
- https://github.com/juce-framework/JUCE/blob/master/docs/Linux%20Dependencies.md

```shell
# packages needed by JUCE
sudo apt install libasound2-dev libjack-jackd2-dev \
ladspa-sdk \
libcurl4-openssl-dev  \
libfreetype-dev libfontconfig1-dev \
libx11-dev libxcomposite-dev libxcursor-dev libxext-dev libxinerama-dev libxrandr-dev libxrender-dev \
libwebkit2gtk-4.1-dev \
libglu1-mesa-dev mesa-common-dev
```

CMake Profile:
- Settings | Build, Execution, Deployment | CMake: add CMake Profile for WSL (Name: "Profiling-WSL", Generator: Let CMake decide)
- Project files are generated in "cmake-build-profiling-wsl"

Build Linux Project:

```shell
cd /mnt/l/WORKSPACES/AUDIO_WS/Projects/VJi/cmake-build-profiling-wsl
make
```

Perf:
- https://www.jetbrains.com/help/clion/cpu-profiler.html#Prerequisites
- https://github.com/microsoft/WSL/issues/8480 (Perf issues on WSL2)

```shell
# install Perf
uname -r
# 6.6.87.1-microsoft-standard-WSL2

# this does not work:
# sudo apt install linux-tools-generic linux-tools-common linux-tools-`uname -r`
# https://askubuntu.com/questions/1314136/installing-linux-perf-tools-on-ubuntu-20-04-lts-with-wsl2
# https://stackoverflow.com/questions/60237123/is-there-any-method-to-run-perf-under-wsl (contains an explanation and solution)
```

Compile Perf from source:
- https://gist.github.com/abel0b/b1881e41b9e1c4b16d84e5e083c38a13

```shell
# compile Perf
# ----------------------------------------------------------------------------
# Dependencies:
# ----------------------------------------------------------------------------
sudo apt install flex bison libdwarf-dev libelf-dev libnuma-dev libpython3-dev libunwind-dev libnewt-dev libdwarf++0 libelf++0 libdw-dev libbfb0-dev
# dependencies stated on microsoft github:
sudo apt install build-essential flex bison dwarves libssl-dev libelf-dev cpio qemu-utils
# dependencies stated by make command:
sudo apt install systemtap-sdt-dev libperl-dev python3-dev libcap-dev libbabeltrace-dev libbabeltrace-ctf-dev libpfm4-dev libtraceevent-dev

# "...you need to set JDIR= to point to the root of your Java directory"
# add Windows JDK to WSL2 environment:
$ sudo nano /etc/environment
#JDIR="/mnt/c/Program Files/Java/jdk-25/"
JDIR="/mnt/c/Programme/Java/jdk-25/"
#JAVA_HOME="/mnt/c/Program Files/Java/jdk-25/"
JAVA_HOME="/mnt/c/Programme/Java/jdk-25/"
# append java bin to the PATH
PATH="$PATH:$JAVA_HOME/bin"
$ source /etc/environment

$ nano ~/.profile
# create aliases, to use something like 'java -version'
alias java='java.exe'
alias javac='javac.exe'
$ source ~/.profile

$ echo $JAVA_HOME
$ echo $JDIR
$ java -version

# ----------------------------------------------------------------------------
# compile Perf
# ----------------------------------------------------------------------------
git clone https://github.com/microsoft/WSL2-Linux-Kernel --depth 1
cd WSL2-Linux-Kernel/tools/perf
make -j8  # parallel build
sudo cp perf /usr/local/bin
# check perf version
perf --version
# check perf list
perf list
```

- Settings | Build, Execution, Deployment | Dynamic Analysis Tools | Profilers | Perf executable: \\wsl.localhost\Ubuntu\usr\local\bin\perf
- https://www.jetbrains.com/help/clion/cpu-profiler.html
- https://perfwiki.github.io/main/

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

## Toolchains

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

## Generators, Build Systems, Package Managers

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

```shell
mkdir build
cd build
# Generate Visual Studio project files
cmake -G "Visual Studio 17 2022"
```

https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html

https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170

---

### Premake

https://premake.github.io/

Lua Scripting

### Ninja

https://ninja-build.org/

https://github.com/ninja-build/ninja

### Gradle

Build Automation Tool (for Android)

https://gradle.org/

https://github.com/gradle/gradle

https://developer.android.com/build/gradle-build-overview

### GNU Make

https://www.gnu.org/software/make/

### NMAKE

https://learn.microsoft.com/de-de/cpp/build/reference/running-nmake?view=msvc-170

Microsoft Makefiles

Use from "Developer Command Prompt for VS 2022"

---

### vcpkg

vc package - C/C++ package manager

https://vcpkg.io/en/

https://github.com/microsoft/vcpkg

https://www.jetbrains.com/help/clion/package-management.html

https://learn.microsoft.com/de-de/shows/pure-virtual-cpp-2024/an-overview-of-vcpkg-in-10-minutes

### cpm

CMake dependency management

https://github.com/cpm-cmake/CPM.cmake

### NuGet

https://www.nuget.org/

https://learn.microsoft.com/de-de/nuget/

.Net package distribution system

a NuGet-Package (*.nupkg) is a ZIP-file containing compiled code (dll) and other files

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

