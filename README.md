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

