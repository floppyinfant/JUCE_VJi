# VJi

A Music Visualizer Plugin (VST3) for DAWs

using GLSL Shaders

made with JUCE Framework

---

Terminal Commands:

```shell
# usage of this repository
git clone --recursive https://github.com/floppyinfant/JUCE_VJi.git
# alternative: --recurse-submodules
cd JUCE_VJi
# if you downloaded the repository without "--recursive" or got the zip-file:
# git submodule update --init --recursive

# ----------------------------------------------------------------------------
# Configure, Build, execute
# ----------------------------------------------------------------------------
cmake -S . -B build
cmake --build build
.\build\VJi_artefacts\Debug\Standalone\VJi.exe

# ----------------------------------------------------------------------------
# Install WebView2 on Windows (only) in PowerShell:
# ----------------------------------------------------------------------------
Register-PackageSource -provider NuGet -name nugetRepository -location https://www.nuget.org/api/v2
Install-Package Microsoft.Web.WebView2 -Scope CurrentUser -RequiredVersion 1.0.1901.177 -Source nugetRepository

# ----------------------------------------------------------------------------
# Development of this repository
# ----------------------------------------------------------------------------
# create local repo 
git init .
git submodule add https://github.com/juce-framework/JUCE.git libs/juce
#git submodule add https://github.com/assimp/assimp.git libs/assimp
git submodule --init --recursive

# stage and commit
git add .
git commit -m "initial commit"

# create remote repo
git remote add origin https://github.com/floppyinfant/JUCE_VJi.git
git push -u origin master
```

To build the Android APK: 

Open the Projucer project file (VJi.juce) and export to Android Studio.


---

## Development Environment

Microsoft Windows

---

### Jetbrains CLion

https://www.jetbrains.com/clion/

#### Settings:

- Settings | Build, Execution, Deployment | Toolchains: add "Visual Studio 2022"
- Settings | Build, Execution, Deployment | CMake: add CMake Profile "Debug-Visual Studio" (Generator Ninja)
- Settings | Editor | General | Appearance: uncheck the option "Show intention bulb" (Alt + Enter shows the same dialog)

#### Profiler:

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

### Visual Studio 2022 (compiler / toolchain: MSVC, cl.exe)

https://visualstudio.microsoft.com/vs/features/cplusplus/

Profiler:
- https://learn.microsoft.com/en-us/visualstudio/profiling/profiling-feature-tour?view=vs-2022&pivots=programming-language-cpp

---

### CMake

https://cmake.org/

---

### git

https://git-scm.com/

Git Bash (for Windows)

(Github Desktop)

---

### JUCE

https://juce.com/

Projucer (for Android Export), DemoRunner, AudioPluginHost

---

### Android Studio

https://developer.android.com/

https://developer.android.com/build/jdks

SDK Manager
- SDK Platforms (Android 8 / API 26, Android 12 / API 31)
- SDK Tools (NDK, CMake, Emulator)
- AVD, ADB

---

---

### Terminal

cmd.exe

(Powershell)

### WSL2

Bash / Shell

Ubuntu Linux

### Docker

https://www.docker.com/

https://docs.docker.com/desktop/windows/wsl/

### Python

https://www.jetbrains.com/pycharm/

https://www.python.org/

https://docs.astral.sh/uv/

https://www.anaconda.com/

Jetbrains PyCharm, Jupyter, Anaconda, Python, uv

---

### Kodelife

https://hexler.net/kodelife/manual/introduction

