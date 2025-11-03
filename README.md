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

Jetbrains CLion

https://www.jetbrains.com/clion/

Visual Studio 2022 (compiler / toolchain: MSVC, cl.exe)

https://visualstudio.microsoft.com/vs/features/cplusplus/

CMake

https://cmake.org/

git

https://git-scm.com/

JUCE (Tutorials, Documentation, DemoRunner, Projucer for Android Export)

https://juce.com/

Android Studio, SDK Manager, SDK Platforms (Android 8 / API 26, Android 12 / API 31), SDK Tools (NDK, CMake, Emulator), AVD, ADB

https://developer.android.com/

https://developer.android.com/build/jdks

Docker, WSL2 (Ubuntu), Jetbrains PyCharm, Python, uv, Anaconda

https://www.docker.com/

https://docs.docker.com/desktop/windows/wsl/

https://www.jetbrains.com/pycharm/

https://www.python.org/

https://docs.astral.sh/uv/

https://www.anaconda.com/

Kodelife

https://hexler.net/kodelife/manual/introduction


