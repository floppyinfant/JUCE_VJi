# LEARN C++ Libraries


---

## Standard Libraries

### libc

---

### std (C++ Standard Library)

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

#### Platforms

```C++
#if JUCE_ANDROID
#else

```

### JUCE Tutorials

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

https://www.youtube.com/@JUCElibrary (JUCE / WolfSound)

https://www.youtube.com/watch?v=0ALLRitFE34&list=PLrJPU5Myec8ZGjG3dpd7ZH3TX4Wn6Z5RE&index=2 (JUCE WebView2)

https://github.com/JanWilczek/juce-webview-tutorial (Repo of the above video)

https://www.youtube.com/@WolfSoundAudio (WolfSound)

https://www.youtube.com/playlist?list=PLJLybGgHYEIeW8OaapEOVelSm-gP9d0MV (WolfSound - Wavetable Synthesis)

https://thewolfsound.com/how-to-build-audio-plugin-with-juce-cpp-framework-cmake-and-unit-tests/

https://www.youtube.com/watch?v=i_Iq4_Kd7Rc (freeCodeCamp Matcatmusic: Learn Modern C++ with JUCE)

https://www.youtube.com/watch?v=Mo0Oco3Vimo (freeCodeCamp Matcatmusic: 3-Band-Compressor)

https://www.youtube.com/@TheAudioProgrammer (TheAudioProgrammer)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPxqkP5AgzZX9jKoKoBtRcu0 (TheAudioProgrammer - 2024)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPzu0H-n4cp8hJvBNjqhMCC0 (TheAudioProgrammer - CLion)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPxBKE-bWNPj1oq8k_upTWsa (TheAudioProgrammer - openFrameworks)

https://www.youtube.com/playlist?list=PLLgJJsrdwhPwR6a2nG8XRvBkXbnKcexlO (TheAudioProgrammer - Unreal MetaSound)


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

https://www.sqlite.org/howtocompile.html

https://github.com/sqlite/sqlite

C API

---

## Assimp

https://github.com/assimp/assimp

https://learnopengl.com/Model-Loading/Assimp

Mesh Loading Library

---

