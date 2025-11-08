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
# if you downloaded the repository without --recursive or the zip-file:
# git submodule update --init --recursive

# ---
# Configure, Build, execute
cmake -S . -B build
cmake --build build
.\build\VJi_artefacts\Debug\Standalone\VJi.exe

# ---
# Install WebView2 on Windows (only) in PowerShell:
Register-PackageSource -provider NuGet -name nugetRepository -location https://www.nuget.org/api/v2
Install-Package Microsoft.Web.WebView2 -Scope CurrentUser -RequiredVersion 1.0.1901.177 -Source nugetRepository

# ---
# development of this repository
# create local repo 
git init .
git submodule add https://github.com/juce-framework/JUCE.git libs/juce
git submodule --init --recursive
# ---
git add .
git commit -m "initial commit"

# create remote repo
git remote add origin https://github.com/floppyinfant/JUCE_VJi.git
git push -u origin master
```

---

## Development Environment

Microsoft Windows

---

### Jetbrains CLion

https://www.jetbrains.com/clion/

Settings:
- Settings | Build, Execution, Deployment | Toolchains: add "Visual Studio 2022"
- Settings | Build, Execution, Deployment | CMake: add CMake Profile "Debug-Visual Studio" (Generator Ninja)
- Settings | Editor | General | Appearance: uncheck the option "Show intention bulb" (Alt + Enter shows the same dialog)

Profiler:
- WSL2 toolchain for Profiling:
- https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html

```shell
# ubuntu@PC (WSL2)
sudo apt-get update
sudo apt-get install cmake gcc clang gdb build-essential
sudo apt-get install pkg-config
```

- Settings | Build, Execution, Deployment | Toolchains: add WSL2
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

```shell
cd /mnt/l/WORKSPACES/AUDIO_WS/Projects/VJi/cmake-build-profiling-wsl
make
```

- Settings | Build, Execution, Deployment | Dynamic Analysis Tools | Perf
- https://www.jetbrains.com/help/clion/cpu-profiler.html#Prerequisites
- https://perfwiki.github.io/main/

```shell
# install perf
# sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`
$ uname -r
4.15.0-36-generic
$ sudo apt-get install linux-tools-4.15.0-36-generic
```

---

### Visual Studio 2022 (compiler / toolchain: MSVC, cl.exe)

https://visualstudio.microsoft.com/vs/features/cplusplus/

---

### CMake

https://cmake.org/

### git

https://git-scm.com/

Git Bash (for Windows)

(Github Desktop)

### JUCE

https://juce.com/

Projucer (for Android Export), DemoRunner, AudioPluginHost

### Android Studio

https://developer.android.com/

https://developer.android.com/build/jdks

SDK Manager
- SDK Platforms (Android 8 / API 26, Android 12 / API 31)
- SDK Tools (NDK, CMake, Emulator)
- AVD, ADB

### Docker

https://www.docker.com/

https://docs.docker.com/desktop/windows/wsl/

### Terminal

cmd.exe

(Powershell)

### WSL2 (Ubuntu)

Bash / Shell

cmake gcc clang gdb build-essential

### Python

Jetbrains PyCharm, Jupyter, Anaconda, Python, uv

https://www.jetbrains.com/pycharm/

https://www.python.org/

https://docs.astral.sh/uv/

https://www.anaconda.com/

### Kodelife

https://hexler.net/kodelife/manual/introduction

