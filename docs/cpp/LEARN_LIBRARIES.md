# LEARN C++ Libraries

## LICENSES

https://docs.github.com/de/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository#disclaimer

https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository

https://choosealicense.com/

https://opensource.guide/legal/#which-open-source-license-is-appropriate-for-my-project

Open Source Licenses for Commercial Products

// by Claude 4.5 Sonnet, 2025-11-29

### ✅ Permitted Licenses (commercial use unproblematic)

#### Permissive Licenses (best suited)

- **MIT License** - Very liberal, commercial use without restrictions
- **Apache 2.0** - Similar to MIT, additionally offers patent protection
- **BSD (2-Clause/3-Clause)** - Very permissive, minimal requirements
- **Boost Software License** - Specifically for C++ libraries, very developer-friendly
- **zlib/libpng License** - Very simple and permissive

**Requirements:** Usually only include copyright notice and license text (not in the product itself, but e.g. in documentation or About dialog).


### ⚠️ Licenses with Restrictions

#### LGPL (Lesser GPL)
- **Allowed:** Dynamic linking (as shared library/.dll/.so)
- **Not allowed:** Static linking (compiled into your binary)
- **Condition:** Users must be able to replace the library
- **Example:** Qt is LGPL (or commercially licensed)

#### MPL 2.0 (Mozilla Public License)
- Modifications to MPL code must be published
- Your own code remains proprietary
- File-level copyleft (not the entire project)


### 🚫 NOT Allowed Licenses for Commercial Closed-Source Products

#### GPL (v2/v3) - GNU General Public License
- **Copyleft license:** Forces you to publish the entire source code of your product
- **"Viral":** Infects your entire project
- **Not allowed for commercial closed-source software**

#### AGPL (Affero GPL)
- Like GPL, but even stricter
- Also applies when used over network (SaaS)

#### CC-BY-NC (Creative Commons Non-Commercial)
- Explicitly no commercial use allowed

---

Best Practices for Your Project

1. **Conduct License Audit:**
    - List all used libraries
    - Check each license

2. **Check Dependencies:**

3. **Documentation:**
    - Create a `LICENSES.txt` or `THIRD_PARTY_NOTICES.txt`
    - List all used libraries with their licenses

4. **When in Doubt:**
    - For commercial products: prefer MIT, Apache 2.0, BSD
    - Avoid GPL libraries or replace with alternatives
    - For LGPL: use dynamic linking

Practical Tips

- **JUCE Framework:** You have the choice between GPL or commercial license
- **Boost Libraries:** Boost License is very permissive and commercially usable
- Many popular C++ libraries (like fmt, spdlog, GLM) are MIT-licensed

---

## Link Libraries

### Command Line

```bash
g++ -lm -Llibs -Iincludes snippets.cpp -o snippets.exe
```

Compiler Flags:
- `-lm` link math library, -lpthread: link pthread library
- `-Llibs` link shared libraries (*.dll, *.so, *.dylib) in libs folder
- `-Iincludes` include headers in includes folder

### Visual Studio

https://www.youtube.com/watch?v=or1dAmUO8k0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=49 (The Cherno - Static Linking in Visual Studio)

https://www.youtube.com/watch?v=Wt4dxDNmDA8&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=51 (The Cherno - Solution Setup)

Example File Structure (Folder Hierarchy):
- `Dependencies\glfw\lib\glfw3.lib`
- `Dependencies\glfw\includes`

Project Properties (RMB on Project, Alt + Enter):
- Project Properties > C/C++ > General > Additional Include Directories: `$(SolutionDir)Dependencies\glfw\includes`
- Project Properties > Linker > General > Additional Library Directories: `$(SolutionDir)Dependencies\glfw\lib`
- Project Properties > Linker > Input > Additional Dependencies: `glfw3.lib`

Relative Paths: use Macro `$(SolutionDir)`

### CMake

```cmake
target_include_directories(VJi 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/includes
)

target_link_libraries(VJi PRIVATE glfw)

target_link_directories(VJi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/lib)

# conventional cmake targets
add_executable(VJi main.cpp)
add_library()
add_custom_target()
```

---

## Standard Libraries

### libc

---

### std (C++ Standard Library)

@see LEARN_CPP.md > Header Files > includes

### STL (Standard Template Library)

### Boost Libraries

---

---

## Graphics Libraries

@see LEARN_SHADERS.md

https://en.wikipedia.org/wiki/Graphics_library

https://en.wikipedia.org/wiki/3D_computer_graphics

https://en.wikipedia.org/wiki/2.5D

Backends (Rendering APIs / Renderers)
- DirectX9, DirectX10, DirectX11, DirectX12, Direct3D
- Metal (Apple)
- OpenGL, OpenGL >3.2, OpenGL ES, OpenGL ES2, (WebGL)
- Vulkan
- SDL_GPU, SDL_Renderer2/3
- WebGPU
- Wayland (Linux)
- Xorg / X11 (Linux)

- CUDA (Nvidia)
- ROCm (AMD)

---

### OpenGL

https://www.khronos.org/opengl/

https://registry.khronos.org/OpenGL-Refpages/

https://www.khronos.org/developers/reference-cards (PDFs)

https://www.opengl.org/

https://www.opengl.org/Documentation/Specs.html

https://www.khronos.org/developers/books/

- The OpenGL SuperBible
- The OpenGL Programming Guide
- Red Book
- Blue Book
- Orange Book

https://wikis.khronos.org/opengl/

Tutorials:

https://learnopengl.com/ <==========

https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 (The Cherno - OpenGL)
- https://hazelengine.com/
- https://github.com/StudioCherno
- https://github.com/TheCherno/Hazel
- https://github.com/TheChernoCommunity

https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M- (Victor Gordan)


#### OpenGL ES

https://en.wikipedia.org/wiki/OpenGL_ES

#### GLSL

OpenGL Shading Language (GLSL)

@see LEARN_SHADERS.md


#### GLFW

Windowing and Input

https://www.glfw.org/

https://github.com/glfw/glfw

https://en.wikipedia.org/wiki/GLFW

#### Glew

OpenGL Extension Wrangler

https://github.com/nigels-com/glew

https://en.wikipedia.org/wiki/OpenGL#Extension_loading_libraries

#### Glad


#### GLM

Math library

https://github.com/g-truc/glm

#### GLUT

https://en.wikipedia.org/wiki/OpenGL_Utility_Toolkit

https://www.opengl.org/resources/libraries/glut/glut_downloads.php

https://en.wikipedia.org/wiki/Freeglut

https://github.com/freeglut/freeglut

---

### Vulkan

https://www.vulkan.org/

https://www.khronos.org/vulkan/

https://en.wikipedia.org/wiki/Vulkan

https://developer.nvidia.com/vulkan

https://source.android.com/docs/core/graphics/arch-vulkan?hl=de

---

### Microsoft DirectX

DirectX 12

https://en.wikipedia.org/wiki/DirectX

https://microsoft.github.io/DirectX-Specs/

https://learn.microsoft.com/en-us/windows/win32/directx

Direct3D

---

---

## GUI Libraries

Frontends (Windowing APIs)
- Native
- ImGui
- GLUT
- GLFW
- SDL2
- SFML
- FLTK
- wxWidgets
- Qt

### Dear ImGui

Immediate Mode GUI

https://www.dearimgui.com/

https://github.com/ocornut/imgui

https://github.com/ocornut/imgui/wiki

https://pthom.github.io/imgui_bundle/

Docking Branch

https://github.com/ocornut/imgui/wiki/Docking

Backends (Rendering APIs)
- Renderers: DirectX9, DirectX10, DirectX11, DirectX12, Metal, OpenGL/ES/ES2, SDL_GPU, SDL_Renderer2/3, Vulkan, WebGPU
- Platforms: GLFW, SDL2/SDL3, Win32, Glut, OSX, Android
- Frameworks: Allegro5, Emscripten

#### Extensions

https://github.com/ocornut/imgui/wiki/Useful-Extensions

Node Graph Editors

https://github.com/ocornut/imgui/wiki/Useful-Extensions#node-editors

- https://github.com/thedmd/imgui-node-editor
- https://github.com/epezent/implot
- https://gboisse.github.io/posts/node-graph/

#### Tutorials

https://www.youtube.com/watch?v=-vXSmDAmXS8 (ADC24 Talk) <========
- https://www.github.com/free-audio/clap-imgui-support
- https://www.github.com/schwaaa/clap-imgui
- https://www.github.com/Krasjet/imgui_juce
- https://www.github.com/noizebox/vstimgui

#### Examples

https://github.com/ocornut/imgui/tree/master/examples

The Cherno Walnut
- https://github.com/StudioCherno/Walnut
- https://github.com/TheCherno/Hazel

SHADERed
- https://github.com/dfranx/SHADERed

---

### GLFW

@see above

### SDL2

Simple DirectMedia Layer

https://www.libsdl.org/

https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer

### SFML

https://www.sfml-dev.org/

https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library

### FLTK

https://en.wikipedia.org/wiki/FLTK

---

### wxWidgets

https://en.wikipedia.org/wiki/WxWidgets

wxFormBuilder: GUI Designer Application

https://github.com/wxFormBuilder/wxFormBuilder

---

### Qt

---

## VSTGUI

https://steinbergmedia.github.io/vst3_doc/vstgui/html/

---

## JUCE

https://juce.com/

https://juce.com/learn/tutorials/

JUCE DemoRunner

https://github.com/juce-framework/JUCE/tree/master/examples

CMake JUCE

https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md

https://github.com/juce-framework/JUCE/tree/master/examples/CMake

Documentation

https://juce.com/learn/documentation/

https://docs.juce.com/master/classes.html

Modules:
- audio
- dsp
- events
- graphics
- animation
- box2d
- opengl
- gui
- javascript
- osc
- video
- cryptography


### Minimum System Requirements

Building JUCE Projects

    C++ Standard: 17
    macOS/iOS: Xcode 12.4 (Intel macOS 10.15.4, Apple Silicon macOS 11.0)
    Windows: Visual Studio 2019 (Windows 10)
    Linux: g++ 7.0 or Clang 6.0 (for a full list of dependencies, see here).
    Android: Android Studio (NDK 26) on Windows, macOS or Linux

Deployment Targets

    macOS: macOS 10.11 (x86_64, Arm64)
    Windows: Windows 10 (x86_64, x86, Arm64, Arm64EC)
    Linux: Mainstream Linux distributions (x86_64, Arm64/aarch64, (32 bit Arm systems like armv7 should work but are not regularly tested))
    iOS: iOS 12 (Arm64, Arm64e, x86_64 (Simulator))
    Android: Android 7 - Nougat (API Level 24) (arm64-v8a, armeabi-v7a, x86_64, x86)


### Code Snippets

#### OpenGL

@see LEARN_SHADERS.md

#### Outline / Snippets

```C++
#pragma once

#include <JuceHeader.h>

// Processor
class PluginAudioProcessor final : public juce::AudioProcessor
{
public:
    PluginAudioProcessor()
    {
        addParameter (gain = new juce::AudioParameterFloat ("gain", // parameterID
                      "Gain", // parameter name
                      0.0f, // minimum value
                      1.0f, // maximum value
                      0.5f)); // default value
    }
    
    ~PluginAudioProcessor() override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        juce::ignoreUnused (sampleRate, samplesPerBlock);
    }
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override
    {}
    
    juce::AudioProcessorEditor* createEditor() override;
    
private:
    juce::AudioProcessorValueTreeState apvts;
    // Parameters
    juce::AudioParameterFloat* gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessor)
};

// Editor
class PluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit PluginAudioProcessorEditor (PluginAudioProcessor&) : juce::AudioProcessorEditor(&p), processor(p)
    {
        // addChildComponent, setVisible
        addAndMakeVisible(component);
        
        setSize(500, 500);
        setResizable(true, true);
    }
    
    ~PluginAudioProcessorEditor() override;
    
    void paint (juce::Graphics& g) override
    {
        // graphics
        g.fillAll(juce::Colours::black.withAlpha(0.7f));
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("Hello Layer", getLocalBounds(), juce::Justification::centred);
        
        
    }
    
    void resized() override
    {
        auto area = getLocalBounds().reduced(4).removeFromTop(25).removeFromLeft(100);
        component.setBounds(area);
    }
    
private:
    PluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessorEditor)
};

```


#### Platforms

```C++
#if JUCE_ANDROID
#else

```

### Tutorials

#### JUCE Tutorials

https://juce.com/learn/tutorials/

- https://juce.com/tutorials/tutorial_choosing_projucer_template/
- Audio:
    - AudioAppComponent
    - https://docs.juce.com/master/classjuce_1_1AudioAppComponent.html
    - AudioProcessor
    - AudioProcessorEditor https://docs.juce.com/master/classjuce_1_1AudioProcessorEditor.html
- Synth:
    - https://juce.com/tutorials/tutorial_synth_using_midi_input/ (Keyboard)
- MIDI:
    - https://juce.com/tutorials/tutorial_midi_message/ (MIDI-Out: Arpeggiator)
    - https://juce.com/tutorials/tutorial_handling_midi_events/ (MIDI-In)
- Plugins:
    - https://juce.com/tutorials/tutorial_audio_parameter/ (Plugin Parameters)
- DSP:
- Graphics:
    - https://juce.com/tutorials/tutorial_main_window (Graphics)
    - Graphics Context https://docs.juce.com/master/classjuce_1_1Graphics.html
    - Animation:
        - https://juce.com/tutorials/tutorial_animation/
        - AnimatedAppComponent https://docs.juce.com/master/classjuce_1_1AnimatedAppComponent.html
    - OpenGL, Shader
        - https://juce.com/tutorials/tutorial_open_gl_application (OpenGL)  <=============
        - OpenGLAppComponent https://docs.juce.com/master/classjuce_1_1OpenGLAppComponent.html
        - OpenGLGraphicsContextCustomShader https://docs.juce.com/master/structjuce_1_1OpenGLGraphicsContextCustomShader.html
        - OpenGLContext https://docs.juce.com/master/classjuce_1_1OpenGLContext.html
        - OpenGLRenderer https://docs.juce.com/master/classjuce_1_1OpenGLRenderer.html
        - OpenGLShaderProgram https://docs.juce.com/master/classjuce_1_1OpenGLShaderProgram.html
            - Uniform https://docs.juce.com/master/structjuce_1_1OpenGLShaderProgram_1_1Uniform.html
        - OpenGLFrameBuffer https://docs.juce.com/master/classjuce_1_1OpenGLFrameBuffer.html
        - OpenGLImageType https://docs.juce.com/master/classjuce_1_1OpenGLImageType.html
        - OpenGLHelpers https://docs.juce.com/master/classjuce_1_1OpenGLHelpers.html
- Interface Design (GUI):
    - Component https://docs.juce.com/master/classjuce_1_1Component.html
    - WebView2 (JavaScript)
- Mobile:
- Utility Classes:
    - https://juce.com/tutorials/tutorial_file_reading
    - https://juce.com/tutorials/tutorial_osc_sender_receiver (OSC)
    - https://juce.com/tutorials/tutorial_value_tree (AVT)
    - https://juce.com/tutorials/tutorial_undo_manager_value_tree (Undo)
    - https://juce.com/tutorials/tutorial_app_plugin_packaging (Distribution)

http://docs.juce.com/master/index.html (Documentation)


#### YouTube Tutorials

WolfSound Audio

https://www.youtube.com/@JUCElibrary (JUCE / WolfSound)

https://www.youtube.com/watch?v=0ALLRitFE34&list=PLrJPU5Myec8ZGjG3dpd7ZH3TX4Wn6Z5RE&index=2 (JUCE WebView2)

https://github.com/JanWilczek/juce-webview-tutorial (Repo of the above video)

https://www.youtube.com/@WolfSoundAudio (WolfSound)

https://www.youtube.com/playlist?list=PLJLybGgHYEIeW8OaapEOVelSm-gP9d0MV (WolfSound - Wavetable Synthesis)

https://thewolfsound.com/how-to-build-audio-plugin-with-juce-cpp-framework-cmake-and-unit-tests/

Matcatmusic / freeCodeCamp

https://www.youtube.com/watch?v=i_Iq4_Kd7Rc (freeCodeCamp Matcatmusic: Learn Modern C++ with JUCE)

https://www.youtube.com/watch?v=Mo0Oco3Vimo (freeCodeCamp Matcatmusic: 3-Band-Compressor)

The Audio Programmer

https://www.youtube.com/@TheAudioProgrammer (TheAudioProgrammer)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPxqkP5AgzZX9jKoKoBtRcu0 (TheAudioProgrammer - 2024)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPzu0H-n4cp8hJvBNjqhMCC0 (TheAudioProgrammer - CLion)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPxBKE-bWNPj1oq8k_upTWsa (TheAudioProgrammer - openFrameworks)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPwR6a2nG8XRvBkXbnKcexlO (TheAudioProgrammer - Unreal MetaSound)

### Projects, People and Code

https://github.com/sudara/awesome-juce (Awesome JUCE Projects) <================

The WolfSound

https://thewolfsound.com/

https://www.wolfsoundacademy.com/dsp-pro#

https://github.com/JanWilczek

https://www.youtube.com/c/WolfSoundAudio

https://www.youtube.com/watch?v=Ah4P-zOfdYc

https://www.youtube.com/@JUCElibrary

freeCodeCamp Matcatmusic

https://www.youtube.com/watch?v=i_Iq4_Kd7Rc

https://github.com/matkatmusic/SimpleEQ

https://www.programmingformusicians.com/

https://www.programmingformusicians.com/pfmcpp/

https://www.programmingformusicians.com/simpleeq/

The Audio Programmer

https://www.youtube.com/@TheAudioProgrammer

#### PluginGuiMagic

https://foleysfinest.com/developer/pluginguimagic/

https://github.com/ffAudio/PluginGuiMagic

https://github.com/ffAudio/foleys_gui_magic

---

## Assimp

https://github.com/assimp/assimp

https://learnopengl.com/Model-Loading/Assimp

Mesh Loading Library

---

## Visage

https://github.com/VitalAudio/visage

UI library meets creative coding

by Matt Tytel (Vital Synthesizer, Dexed, Helm)

active development!

https://www.youtube.com/watch?v=Lrj9R-h8bnA (The Audio Programmer: Interview with Matt Tytel and Demo)

---

### Setup

Git Submodule:

```shell
# add library as a submodule to the project
git submodule add https://github.com/VitalAudio/visage.git libs/visage
```

CMakeLists.txt:

```cmake
# add library to the build system
add_subdirectory(libs/visage)

# ...

target_link_libraries(VJi
        PRIVATE
        # ...
        visage
        # ...
)
```

Visual Studio:

```shell
# Build examples and library in Visual Studio: this is not necessary, because it can be directly added to CMakeLists.txt
cd libs/visage
mkdir build
cmake -G "Visual Studio 17 2022" -A x64 -S . -B build
#cmake --build build
# open the solution file in build/Visage.sln
# In Visual Studio: RMB Click on Example Project -> Set as Startup Project; F5 (Start Debugging)
```

Static Linking:

```cmake
# THIS IS NOT NECESSARY, JUST FOR REFERENCE (other libraries): @see ImGui
# Add a library for static linking to the build system (if the library does not have a CMakeLists.txt or you have the prebuild lib file)

# Add the pre-built visage library as an IMPORTED target
add_library(visage STATIC IMPORTED)
set_target_properties(visage PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/visage/build/Debug/visage.lib"  # Adjust path as needed
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/libs/visage"
)

# If you need release builds too:
set_target_properties(visage PROPERTIES
    IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/libs/visage/build/Debug/visage.lib"
    IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/libs/visage/build/Release/visage.lib"
)
```

---

### Usage Examples

There are two ways of Programming with Visage:

```c++
#include <visage/app.h>

// ExampleBasic:
int runExample() {
  visage::ApplicationWindow app;

  app.onDraw() = [&app](visage::Canvas& canvas) {
    canvas.setColor(0xff000066);
    canvas.fill(0, 0, app.width(), app.height());
    // ...
  };

  app.setTitle("Visage Basic Example");
  app.show(800, 600);
  app.runEventLoop();
  return 0;
}

// ---------------------------------------------

int main(int, char**) {
  return runExample();
}
```

Inheritance: inherit from Frame and override draw()

```c++
#include <visage/app.h>

// ExampleBloom:
class AnimatedLine : public visage::Frame {
public:
  static constexpr int kNumPoints = 1200;

  AnimatedLine() : graph_line_(kNumPoints) {
    addChild(&graph_line_);
  }

  void resized() override { 
    graph_line_.setBounds(0, 0, width(), height()); 
  }
  void draw(visage::Canvas& canvas) override {
    // 
  }

private:
  visage::GraphLine graph_line_;
};

// ---------------------------------------------

class ExampleEditor : public visage::ApplicationWindow {
public:
  ExampleEditor() {
    addChild(&animated_line_);
    animated_line_.layout().setMargin(0);

    onDraw() = [this](visage::Canvas& canvas) {
      canvas.setColor(0xff22282d);
      canvas.fill(0, 0, width(), height());
    };
  }

private:
  AnimatedLine animated_line_;
};

// ---------------------------------------------

int runExample() {
  ExampleEditor editor;
  editor.setWindowDecoration(visage::Window::Decoration::Client);
  if (visage::isMobileDevice())
    editor.showMaximized();
  else
    editor.show(visage::Dimension::widthPercent(50.0f), visage::Dimension::widthPercent(14.0f));

  editor.runEventLoop();
  return 0;
}

// ---------------------------------------------

int main(int, char**) {
  return runExample();
}
```

---

## ImGui

@see GUI Libraries

What is immediate mode GUI vs. retained mode?

immediate mode GUI
- draw everything at once, e.g. in a render loop, every frame

retained mode GUI
- draw only what is visible
- callbacks
- widgets

https://youtu.be/LSRJ1jZq90k (CppCon)

https://github.com/ocornut/imgui/tree/docking

### Add ImGui to the Juce Project

`git submodule add -b docking https://github.com/ocornut/imgui.git libs/imgui`

#### Create a new file libs/imgui/CMakeLists.txt

Since you're using JUCE with OpenGL, you likely want imgui_impl_opengl3.cpp and possibly need to write a custom JUCE integration.

```cmake
cmake_minimum_required(VERSION 3.22)
project(imgui)

set(CMAKE_CXX_STANDARD 23)

# Core ImGui files
set(IMGUI_SOURCES
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

set(IMGUI_HEADERS
    imgui.h
    imgui_internal.h
    imconfig.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
)

# Choose which backend(s) you need based on your rendering system
# For OpenGL3 + your existing windowing system:
set(IMGUI_BACKEND_SOURCES
    backends/imgui_impl_opengl3.cpp
    # Add your platform backend:
    # backends/imgui_impl_win32.cpp    # Windows
    # backends/imgui_impl_osx.mm       # macOS
    # backends/imgui_impl_glfw.cpp     # if using GLFW
)

set(IMGUI_BACKEND_HEADERS
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_opengl3_loader.h
    # Add corresponding headers:
    # backends/imgui_impl_win32.h
    # backends/imgui_impl_osx.h
    # backends/imgui_impl_glfw.h
)

# Create the library
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

# Link OpenGL if using OpenGL backend
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Platform-specific linking
if(WIN32)
    target_link_libraries(imgui PUBLIC imm32)
endif()
```

Then in your main `CMakeLists.txt` add:

```cmake
add_subdirectory(libs/imgui)

# ...
target_link_libraries(VJi 
    PRIVATE
        # ...
        imgui
        # ...
)
```

#### ... because imgui is a git submodule

@see cmake/imgui.cmake

If you want to add the CMakeLists.txt to the repo, you can only commit it to the submodule.

To add it to the main repo, create a cmake-file and include it in the root CMakeLists.txt:

```cmake
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

set(IMGUI_BACKEND_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC
        ${IMGUI_SOURCES}
        ${IMGUI_BACKEND_SOURCES}
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}                # ${IMGUI_HEADERS}
        ${IMGUI_DIR}/backends       # ${IMGUI_BACKEND_HEADERS}
)

# Link OpenGL if using OpenGL backend
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Platform-specific linking
if(WIN32)
    target_link_libraries(imgui PUBLIC imm32)
endif()
```

```cmake
add_subdirectory(libs/juce)

include(cmake/imgui.cmake)
add_subdirectory(libs/imgui_juce)

# ...

target_link_libraries(VJi
    PRIVATE
        juce::juce_opengl
        imgui
        imgui_impl_juce
        # ...
)
```

---

https://github.com/ocornut/imgui/wiki

https://github.com/ocornut/imgui/wiki/Docking

```c++
ImGui::NewFrame();

// -----------------------------------------------------------------------
// imgui Docking
// -----------------------------------------------------------------------

// Create a dockspace in main viewport.
// https://github.com/ocornut/imgui/wiki/Docking
// enable `Demo > Configuration > Docking > io.ConfigFlags: Docking Enabled`
ImGui::DockSpaceOverViewport();

// -----------------------------------------------------------------------
// imgui begin
// -----------------------------------------------------------------------
ImGui::Begin("Settings");
//ImGui::Begin("window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

ImGui::Button("Hello");
ImGui::Text("Hello, world");
ImGui::ShowDemoWindow();

ImGui::End();
// -----------------------------------------------------------------------
// imgui end
// -----------------------------------------------------------------------

ImGui::Render();
```

### Extensions

https://github.com/ocornut/imgui/wiki/Useful-Extensions

#### ImPlot

https://github.com/epezent/implot

#### ImGui-Node-Editor

https://github.com/thedmd/imgui-node-editor


### VSTImGui

https://youtu.be/-vXSmDAmXS8 (ADC - Audio Developers Conference; vstimgui)

https://github.com/noizebox/vstimgui

uses GLFW

### imgui_juce (module)

https://github.com/Krasjet/imgui_juce

https://github.com/Krasjet/imgui_juce/blob/master/examples/mwe/src/ImGuiComponent.h

### Walnut (The Cherno)

- https://github.com/TheCherno (Walnut and Hazel Engine are Dear ImGui example projects)
- https://github.com/StudioCherno/Walnut

- https://www.youtube.com/watch?v=vWXrFetSH8w (ImGui Examples)
- https://www.youtube.com/watch?v=5zS-DZhCA2g (Walnut uses Vulkan)
- https://www.youtube.com/watch?v=-NJDxf4XwlQ
- https://www.youtube.com/watch?v=WIe-ewLxHSY
- https://www.youtube.com/watch?v=5glH8dGoeCA (Setup Projects in Visual Studio)
- https://www.youtube.com/watch?v=WIe-ewLxHSY (How to Debug Graphics Issues)

---

## React Native

https://reactnative.dev/

https://github.com/facebook/react-native

Tutorials
- https://en.wikipedia.org/wiki/React_Native
- https://learn.microsoft.com/de-de/windows/dev-environment/javascript/react-native-for-android
- https://microsoft.github.io/react-native-windows/
- https://www.youtube.com/watch?v=J50gwzwLvAk
- https://www.geeksforgeeks.org/reactjs/introduction-react-native/
- https://docs.flutter.dev/get-started/flutter-for/react-native-devs (Flutter)

### React-Juce

https://docs.react-juce.dev/

https://github.com/JoshMarler/react-juce

https://github.com/JoshMarler/react-juce/blob/master/docs/guides/Integrating_Your_Project.md

dead project?

### WebView2

https://developer.microsoft.com/en-us/Microsoft-edge/webview2/?form=MA13LH

@see README.md for Installation on Windows

---

## JavaScript Frameworks and Stuff

Node.js

https://nodejs.org/

Ionic

https://ionicframework.com/

Capacitor

https://capacitorjs.com/

Vue

https://vuejs.org/

https://ionicframework.com/docs/vue/overview

---

## openFrameworks (of)

https://openframeworks.cc/learning/

https://openframeworks.cc/documentation/

https://openframeworks.cc/examples/
- https://github.com/openframeworks/openFrameworks/tree/master/examples/

https://openframeworks.cc/ofBook/chapters/foreword.html (Book of openFrameworks)

https://openframeworks.cc/ofBook/chapters/shaders.html
- https://github.com/openframeworks/openFrameworks/tree/master/examples/shader

```c++
```

---

## Unreal Engine

https://dev.epicgames.com/community/unreal-engine/learning

https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-7-documentation

https://dev.epicgames.com/documentation/de-de/unreal-engine/API (C++ API)

---

## SQlite

https://www.sqlite.org/index.html

https://github.com/sqlite/sqlite

C API

### Linux

`sudo apt-get install libsqlite3-dev`

https://stackoverflow.com/questions/10574933/compiling-of-sqlite3-in-c

### Windows

@see README.md

To build SQlite:

https://www.sqlite.org/howtocompile.html

```shell
# open Developer Command Prompt for VS2022
# https://learn.microsoft.com/de-de/cpp/build/reference/running-nmake?view=msvc-170
cd libs
git clone https://github.com/sqlite/sqlite.git
cd sqlite
# remove git repo
rmdir /s /q .git
#mkdir build
#set OUTDIR=./build
nmake /f Makefile.msc
```

make targets:
- libsqlite3.lib (static library)
- sqlite3.lib (static library)
- sqlite3.dll (dynamic library)
- sqlite3.pdb (debug symbols)
- sqlite3.h (C-language interface header file)
- sqlite3.c (amalgamation source file)
- sqlite3.exe (command line tool)

or download the amalgamation library from https://www.sqlite.org/download.html and extract it into the "libs/sqlite3" folder.

```cmake
# Define the directory where you put the source files
set(SQLITE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite3)

# Add SQLite as a static library target
add_library(sqlite3 STATIC
${SQLITE_SOURCE_DIR}/sqlite3.c
)

# Set include directories
target_include_directories(sqlite3 PUBLIC
${SQLITE_SOURCE_DIR}
)

# Recommended: Set specific compiler flags if needed (e.g., thread safety)
# target_compile_definitions(sqlite3 PRIVATE SQLITE_THREADSAFE=1)

# Set properties for the library (optional but good practice)
set_target_properties(sqlite3 PROPERTIES
POSITION_INDEPENDENT_CODE ON
)

# ----------------------------------------------------------------------------

# Link the sqlite3 library to your main application target
target_link_libraries(VJi PRIVATE sqlite3)
```

Include SQlite in Code:

```c++
#include "sqlite3.h"
// ... use sqlite functions
```

https://sqlite.org/docs.html

https://sqlite.org/quickstart.html

https://sqlite.org/cintro.html

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

## VST3 SDK

https://www.steinberg.net/developers/

https://github.com/steinbergmedia/vst3sdk

https://github.com/steinbergmedia/vst3_example_plugin_hello_world

### VSTGUI

https://github.com/steinbergmedia/vstgui

---

## CLAP

https://github.com/free-audio/clap

https://github.com/free-audio/clap-juce-extensions

---

## Melatonin Inspector

https://github.com/sudara/melatonin_inspector

A JUCE module that gives you the ability to inspect and visually edit (non-destructively) components in your UI.

https://melatonin.dev/blog/

### Awesome Juce

https://github.com/sudara/awesome-juce

Awesome DSP

https://github.com/olilarkin/awesome-musicdsp

https://github.com/BillyDM/awesome-audio-dsp

...

https://github.com/COx2/glslEditor_AudioPlugin

https://github.com/ianacaburian/LiveShaderPalette

https://github.com/JanosGit/OpenGLRealtimeVisualization4JUCE

#### Surge Synthesizer

https://github.com/surge-synthesizer

https://github.com/surge-synthesizer/sst-effects

https://github.com/surge-synthesizer/sst-jucegui/tree/main

https://github.com/surge-synthesizer/OB-Xf (see libs/)

#### Mat Tytel

https://github.com/mtytel

https://github.com/mtytel/vital (Vital)

https://github.com/VitalAudio/visage (Visage)

https://github.com/mtytel/helm (Helm)

#### ffAudio

https://github.com/ffAudio

foleys gui magic

https://github.com/ffAudio/foleys_gui_magic

https://foleysfinest.com/foleys_gui_magic/

PluginGuiMagic (obsolete)

https://github.com/ffAudio/PluginGuiMagic

#### ChowDSP

https://github.com/Chowdhury-DSP

https://github.com/Chowdhury-DSP/chowdsp_utils

https://github.com/jatinchowdhury18

#### WoldSound

https://github.com/JanWilczek

https://thewolfsound.com/

https://www.youtube.com/c/WolfSoundAudio

https://www.youtube.com/watch?v=mjp4Xu1QA0w&list=PLrJPU5Myec8ZGjG3dpd7ZH3TX4Wn6Z5RE

---

## Will Pirkle

https://www.willpirkle.com/

https://www.willpirkle.com/fx-book/project-gallery/

https://github.com/willpirkleaudio

---

