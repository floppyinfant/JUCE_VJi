# LEARN C++ Libraries


---

## Standard Libraries

### libc

---

### std (C++ Standard Library)

### STL (Standard Template Library)

### Boost Libraries

---

## Graphics Libraries

- https://en.wikipedia.org/wiki/Graphics_library
- https://en.wikipedia.org/wiki/3D_computer_graphics
- https://en.wikipedia.org/wiki/2.5D

...

Metal (Apple)

Wayland (Linux)

Xorg / X11 (Linux)

CUDA (Nvidia)

ROCm (AMD)

### Microsoft DirectX

DirectX 12

https://en.wikipedia.org/wiki/DirectX

https://microsoft.github.io/DirectX-Specs/

https://learn.microsoft.com/en-us/windows/win32/directx

Direct3D

### Vulkan

https://www.vulkan.org/

https://www.khronos.org/vulkan/

https://en.wikipedia.org/wiki/Vulkan

https://developer.nvidia.com/vulkan

https://source.android.com/docs/core/graphics/arch-vulkan?hl=de

### OpenGL

https://www.khronos.org/opengl/

https://registry.khronos.org/OpenGL-Refpages/

https://www.khronos.org/developers/reference-cards (PDFs)

https://www.opengl.org/

https://www.opengl.org/Documentation/Specs.html

https://www.khronos.org/developers/books/

The OpenGL SuperBible

The OpenGL Programming Guide

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

#### GLM

Math library

https://github.com/g-truc/glm

#### GLUT

https://en.wikipedia.org/wiki/OpenGL_Utility_Toolkit

https://www.opengl.org/resources/libraries/glut/glut_downloads.php

https://en.wikipedia.org/wiki/Freeglut

https://github.com/freeglut/freeglut

---

## GUI Libraries

### Dear ImGui

https://github.com/ocornut/imgui

https://www.dearimgui.com/

https://pthom.github.io/imgui_bundle/

Dear ImGui Extensions

https://github.com/ocornut/imgui/wiki/Useful-Extensions

Node Graph Editors

https://github.com/ocornut/imgui/wiki/Useful-Extensions#node-editors

- https://github.com/thedmd/imgui-node-editor
- https://github.com/epezent/implot
- https://gboisse.github.io/posts/node-graph/

Tutorials
- https://www.youtube.com/watch?v=-vXSmDAmXS8 (ADC24 Talk) <========
    - https://www.github.com/free-audio/clap-imgui-support
    - https://www.github.com/schwaaa/clap-imgui
    - https://www.github.com/Krasjet/imgui_juce
    - https://www.github.com/noizebox/vstimgui

Examples
- https://github.com/ocornut/imgui/tree/master/examples
- 
The Cherno Walnut
- https://github.com/StudioCherno/Walnut
- https://github.com/TheCherno/Hazel

SHADERed
- https://github.com/dfranx/SHADERed

### Qt

### wxWidgets

https://en.wikipedia.org/wiki/WxWidgets

wxFormBuilder: GUI Designer Application

https://github.com/wxFormBuilder/wxFormBuilder

### SDL2

https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer

### SFML

https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library

### FLTK

https://en.wikipedia.org/wiki/FLTK

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

https://wikis.khronos.org/opengl/Uniform_(GLSL)

https://learnopengl.com/Getting-started/Shaders+

https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL

https://learnopengl.com/Model-Loading/Assimp

https://github.com/assimp/assimp

Code Examples:
- DemoRunner/GUI/OpenGLDemo2D.h (OpenGLGraphicsContextCustomShader)
- DemoRunner/GUI/OpenGLDemo.cpp
- DemoRunner/GUI/OpenGLAppDemo.cpp

Juce Documentation:
- https://docs.juce.com/master/classes.html#letter_O
- https://docs.juce.com/master/classjuce_1_1OpenGLAppComponent.html
- https://docs.juce.com/master/classjuce_1_1OpenGLHelpers.html
- https://docs.juce.com/master/classjuce_1_1OpenGLContext.html
- https://docs.juce.com/master/classjuce_1_1OpenGLRenderer.html
- https://docs.juce.com/master/structjuce_1_1OpenGLGraphicsContextCustomShader.html
- https://docs.juce.com/master/classjuce_1_1OpenGLShaderProgram.html
- https://docs.juce.com/master/classjuce_1_1OpenGLFrameBuffer.html
- https://docs.juce.com/master/classjuce_1_1OpenGLTexture.html
- https://docs.juce.com/master/classjuce_1_1OpenGLImageType.html
- https://docs.juce.com/master/classjuce_1_1OpenGLPixelFormat.html

##### @see src/vj/ShderEditor.cpp

```C++
juce::OpenGLContext openGLContext;
juce::String shaderCode;
std::unique_ptr<juce::OpenGLGraphicsContextCustomShader> shader;
juce::OpenGLShaderProgram* shaderProgram;

codeDocument.replaceAllContent(ShaderPresets::getPresets()[preset].fragmentShader);  // selectPreset()
shaderCode = convert(codeDocument.getAllContent());                                  // timerCallback()
codeDocument.replaceAllContent(shaderCode);

// paint(Graphics& g)
shader.reset(new juce::OpenGLGraphicsContextCustomShader(shaderCode));
auto result = shader->checkCompilation(g.getInternalContext());
shaderProgram = shader->getProgram(g.getInternalContext());
shaderProgram->use();

// set Uniforms:
shaderProgram->setUniform("iResolution", (float) getWidth(), (float) getHeight(), 1.0f);
shader->fillRect(g.getInternalContext(), getLocalBounds());

// other way to set Uniforms: OpenGLAppDemo.h > Uniforms (class):
std::unique_ptr<OpenGLShaderProgram::Uniform> projectionMatrix;
projectionMatrix.reset(new OpenGLShaderProgram::Uniform(shaderProgram, "projectionMatrix"));
```

##### @see src/gui/components/OpenGLComponent.cpp

based on https://medium.com/@Im_Jimmi/using-opengl-for-2d-graphics-in-a-juce-plug-in-24aa82f634ff

```C++
```

##### Uniforms

###### GLSL

- https://learnopengl.com/Getting-started/Shaders+
- https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
- https://wikis.khronos.org/opengl/Uniform_(GLSL)

```C++
gl_Position
gl_FragCoord
gl_FragColor
```

###### JUCE

```C++
#ifdef GL_ES
precision mediump float;
#endif

// --- juce_OpenGLGraphicsContext.cpp ---
varying vec2 pixelPos;
#define pixelAlpha frontColour.a

attribute vec2 position;
attribute vec4 colour;
uniform vec4 screenBounds;
varying vec4 frontColour;

varying vec2 texturePos;
vec2 adjustedPos
vec2 scaledPos
uniform sampler2D maskTexture;
uniform ivec4 maskBounds;
uniform float matrix[6];
uniform sampler2D gradientTexture;
uniform vec4 gradientInfo;
gradientPos
uniform sampler2D imageTexture;
uniform vec2 imageLimits;

// --- juce_OpenGLHelpers.cpp  ---
if (getOpenGLVersion() >= Version (3, 2))
// --- OpenGLHelpers::translateVertexShaderToV3 ---
#if JUCE_ANDROID
#else
code.replace ("attribute", "in");
output.replace ("varying", "out");
// --- OpenGLHelpers::translateFragmentShaderToV3 ---
out vec4 fragColor;
code.replace ("varying", "in")
code.replace ("texture2D", "texture")
code.replace ("gl_FragColor", "fragColor");

// --- OpenGLHelpers::getGLSLVersionString() ---
if (getOpenGLVersion() >= Version (3, 2)) {
    #if JUCE_OPENGL_ES 
        return "#version 300 es"; 
    #else 
        return "#version 150"; }
else {
    return "#version 110";
}
```

###### ShaderToy

- https://www.shadertoy.com/howto

```C++
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform float     iFrameRate;            // shader frame rate
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)
```

###### The Book of Shaders

- https://thebookofshaders.com/03/
- https://github.com/patriciogonzalezvivo/ofxshader

```C++
uniform vec2 u_resolution;   // Canvas size (width,height) || viewport resolution (in pixels)
uniform vec2 u_mouse;        // mouse position in screen pixels || mouse pixel coords
uniform float u_time;        // Time in seconds since load || shader playback time (in seconds)

uniform float u_delta;       // delta time between frames (in seconds)
uniform vec4 u_date;         // year, month, day and seconds
```

###### p5.js

https://p5js.org/tutorials/#webgl

https://p5js.org/tutorials/intro-to-shaders/

https://p5js.org/reference/p5/p5.Shader/

https://p5js.org/reference/p5.Shader/setUniform/

https://p5js.org/reference/#Environment (Environment)

https://p5js.org/reference/#Events (Events)

https://github.com/processing/p5.js/blob/main/contributor_docs/webgl_mode_architecture.md#global

```C++
// WebGL
// For all objects in all contexts, the following global uniforms are available:
uniform mat4 uModelViewMatrix;   // A matrix to convert object-space positions into camera-space
uniform mat4 uProjectionMatrix;  // A matrix to convert camera-space positions into screen space
uniform mat3 uNormalMatrix;      // A matrix to convert object-space normals into camera-space
// Additionally, these per-vertex properties are available as attributes:
attribute vec3 aPosition;        // The position of the vertex in object space
attribute vec3 aNormal;          // For fills, a direction pointing outward from the surface
attribute vec2 aTexCoord;        // For fills, a coordinate between 0 and 1 in x and y referring to a location on a texture image
attribute vec3 aVertexColor;     // For fills, an optional per-vertex color
// Lights
// Materials
// ...
```

###### WebGL

https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API

https://developer.mozilla.org/en-US/docs/Web/API/WebGLShader

https://developer.mozilla.org/en-US/docs/Web/API/WebGLProgram

https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext/uniform

###### WebGPU

https://eliemichel.github.io/LearnWebGPU/basic-3d-rendering/shader-uniforms/a-first-uniform.html

###### ISF

- https://docs.isf.video/quickstart.html#automatically-created-uniforms-and-variables-in-isf
- https://docs.isf.video/ref_variables.html

```C++
isf_FragNormCoord    // which contains the normalized (0.0 to 1.0) coordinate
TIME
TIMEDELTA
FRAMEINDEX           // which can be used to animate compositions over time
RENDERSIZE           // which contains the pixel dimensions of the output being rendered
PASSINDEX
DATE
gl_FragCoord
```

###### GLSL Sandbox

- https://glslsandbox.com/
- https://github.com/mrdoob/glsl-sandbox/blob/master/static/index.html

```C++
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 surfaceSize;
attribute vec3 position;
attribute vec2 surfacePosAttrib;
varying vec2 surfacePosition;
uniform sampler2D texture;
backbuffer
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

## SQlite

https://www.sqlite.org/index.html

https://www.sqlite.org/howtocompile.html

https://github.com/sqlite/sqlite

