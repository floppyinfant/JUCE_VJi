# VJi

A Music Visualizer Plugin (VST) for DAWs

made with JUCE Framework

---

Terminal Commands Protocol:

```shell
git init .
git submodule add https://github.com/juce-framework/JUCE.git libs/juce
git submodule --init --recursive
# ---
git add .
git commit -m "initial commit"
# create remote repo
git remote add origin https://github.com/floppyinfant/JUCE_VJi.git
git push -u origin master
# ---
# Install WebView2 on Windows
Register-PackageSource -provider NuGet -name nugetRepository -location https://www.nuget.org/api/v2
Install-Package Microsoft.Web.WebView2 -Scope CurrentUser -RequiredVersion 1.0.1901.177 -Source nugetRepository
# ---
# Configure, Build, execute
cmake -S . -B build
cmake --build build
.\build\VJi_artefacts\Debug\Standalone\VJi.exe
```

---

---

## Tutorials

@see docs/tools/README.md

### Jetbrains Tutorials

https://www.jetbrains.com/clion/learn/

- https://www.jetbrains.com/help/clion/clion-quick-start-guide.html
- https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html (CMake Tutorial)
- https://www.jetbrains.com/help/clion/junie.html
- https://www.jetbrains.com/help/junie/get-started-with-junie.html (Junie Coding Agent)

### CMake Tutorials

https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html

https://cmake.org/cmake/help/book/mastering-cmake/cmake/Help/guide/tutorial/

### JUCE Tutorials

https://www.youtube.com/watch?v=0ALLRitFE34&list=PLrJPU5Myec8ZGjG3dpd7ZH3TX4Wn6Z5RE&index=2 (JUCE WebView2)

https://github.com/JanWilczek/juce-webview-tutorial (Repo of the above video)

https://thewolfsound.com/how-to-build-audio-plugin-with-juce-cpp-framework-cmake-and-unit-tests/ (WolfSound)

https://juce.com/learn/tutorials/

- https://juce.com/tutorials/tutorial_choosing_projucer_template/
- Audio:
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
- https://juce.com/tutorials/tutorial_open_gl_application (OpenGL)  <=============
- Interface Design:
- Mobile:
- Utility Classes:
- https://juce.com/tutorials/tutorial_file_reading
- https://juce.com/tutorials/tutorial_value_tree (AVT)
- https://juce.com/tutorials/tutorial_undo_manager_value_tree (Undo)
- https://juce.com/tutorials/tutorial_osc_sender_receiver (OSC)
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

---

---

## APIs: Frameworks, Libraries, Software and Tools

### Rendering APIs / Backends

- OpenGL
- Vulkan
- DirectX  12, Direct3D (Microsoft)
- CUDA (Nvidia), ROCm (AMD)
- Metal (Apple)
- Wayland (Linux), Xorg / X11 (Linux)

OpenPBR (Physically Based Rendering)
- https://github.com/AcademySoftwareFoundation/OpenPBR
- https://academysoftwarefoundation.github.io/OpenPBR/

GLFW (OpenGL Framework)
- https://www.glfw.org/

Glew (OpenGL Extension Wrangler Library)
- https://github.com/nigels-com/glew

Dear ImGui (GUI Framework)
- https://github.com/ocornut/imgui

SDL (Simple DirectMedia Layer)
- https://www.libsdl.org/

---

### OpenGL Shading Language (GLSL)

https://github.com/KhronosGroup/GLSL

https://www.khronos.org/

https://www.khronos.org/opengl/

https://wikis.khronos.org/opengl/

https://wikis.khronos.org/opengl/OpenGL_Shading_Language

https://www.khronos.org/developers/reference-cards

https://www.opengl.org/

https://github.com/g-truc/ogl-samples (Shaders in Data/)

File Extensions: vert.glsl, frag.glsl, *.vert, *.frag, *.fs, *.vs, ... , *.geom, *.tesc, *.tese, *.comp, *.spv

Attribute

Uniform

Varying

---

### Open Shading Language (OSL)

*.osl

Blender: Text Editor --> Script Node in Shader Editor

https://docs.blender.org/manual/en/latest/render/cycles/osl/index.html

https://open-shading-language.readthedocs.io/en/latest/

https://github.com/imageworks/OpenShadingLanguage

https://www.youtube.com/watch?v=H8nHxRO7eX0 (CGMatter Fractals)

---

### Interactive Shader Format (ISF)

https://isf.video/

https://isf.video/developers/

https://docs.isf.video/ (Docs)

https://docs.isf.video/quickstart.html

https://isf.video/integrations/ (Software using ISF)  <=============

https://editor.isf.video/ (Online Editor with Examples)

https://docs.vidvox.net/isf-editor/ (Desktop Editor)

https://isf.vidvox.net/desktop-editor/ 

https://github.com/vidvox/isf

https://github.com/Vidvox/ISF-Files (Shader Repository)

https://github.com/mrRay/vvisf-gl (C++ / OpenGL Library)  <=============

https://github.com/msfeldstein/interactive-shader-format-js (JS / WebGL Library)

https://github.com/headstash/synesthesia-scripts (ISF to Synesthesia Script Converter)

---

### GLSL Sandbox

https://glslsandbox.com/

### The Book of Shaders

https://thebookofshaders.com/

---

### ShaderToy

https://www.shadertoy.com/

https://www.shadertoy.com/howto

https://www.youtube.com/watch?v=f4s1h2YETNY (YouTube Tutorial)

https://www.youtube.com/watch?v=0ifChJ0nJfM (Tutorial linked by ShaderToy)

https://shadertoyunofficial.wordpress.com/ (Tutorial linked by ShaderToy)



Apps:

https://steamcommunity.com/sharedfiles/filedetails/?id=1726697188 (Wallpaper)

https://chromewebstore.google.com/detail/shadertoy-unofficial-plug/ohicbclhdmkhoabobgppffepcopomhgl (Chrome Extension)

https://github.com/patuwwy/ShaderToy-Chrome-Plugin/

https://addons.mozilla.org/firefox/addon/shadertoy-unofficial-plugin/ (Firefox Extension)

---

#### Code

Shader Inputs

```
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
```

---

### OpenProcessing

https://openprocessing.org/

https://openprocessing.org/learn/

https://openprocessing.org/sketch/create

https://openprocessing.org/browse

https://openprocessing.org/discover/#/shader

https://openprocessing.org/discover/#/generativeart

https://openprocessing.org/discover/#/particles

https://openprocessing.org/browse?time=anytime&type=tags&q=particle&offset=0#

---

### P5.js

https://p5js.org/

#### Example p5.js sketch

```javascript
function setup() {
	createCanvas(600, 500);
	background('#000000');
}

function draw() {
	
}
```

---

### Py5
based on Processing (needs Java)
https://py5coding.org/
https://github.com/py5coding/py5

---

### Three.js

https://threejs.org/

https://github.com/mrdoob/three.js

WebGL
WebGPU
WebAsm / WA
SVG
CSS3D

https://developer.chrome.com/docs/web-platform/webgpu/overview?hl=de
https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API
https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API

https://gpuweb.github.io/gpuweb/wgsl/ (WGSL - WebGPU Shading Language)

https://webassembly.org/ (WA)


#### Three.js Example: NASA Solar System

https://eyes.nasa.gov/apps/solar-system/#/home

---

### Processing

https://processing.org/

---

### openFrameworks

https://openframeworks.cc/learning/

https://openframeworks.cc/examples/
^- https://github.com/openframeworks/openFrameworks/tree/master/examples

https://openframeworks.cc/documentation/
- https://openframeworks.cc///documentation/gl/ofShader/

---

### Max/MSP Jitter

https://cycling74.com/products/jitter

https://cycling74.com/articles/jitter-resources-an-overview


---

### Pure Data GEM

https://puredata.info/

- https://gem.iem.at/documentation/manual
- https://puredata.info/downloads/gem/documentation/tutorial/particles/gem-outline_en.pdf

https://www.youtube.com/@SoundSimulator/playlists

- https://www.youtube.com/watch?v=y1rBa_STq64
- https://www.youtube.com/watch?v=Vyp6_SJlWAs

https://www.youtube.com/@cheetomoskeeto/playlists

- https://www.youtube.com/watch?v=cinOFA1pT1k&list=PLn3ODBv0ka5hS5areRFSTi2aydPMiUq3B (libPd for Android)

https://www.automatonism.com/

Andy Farnell

- https://mitpress.mit.edu/9780262014410/designing-sound/
- https://cycling74.com/projects/andy-farnell%27s-designing-sound-examples-for-maxmsp

https://www.evl.uic.edu/drew/courses/AD405/PDGEM_resources.htm

https://www.kreidler-net.de/theorie/pd-tutorial.htm

http://www.pd-tutorial.com/

---

---

### Synesthesia

https://www.synesthesia.live/

https://app.synesthesia.live/docs/ssf/ssf.html?referrer=synesthesia

https://app.synesthesia.live/docs/resources/glsl_resources.html

https://github.com/headstash/synesthesia-scripts

---

### TouchDesigner

---

### TouchVIZ (iPad)

https://hexler.net/touchviz

### KodeLife

https://hexler.net/kodelife

https://hexler.net/kodelife/manual/introduction

---

### Motion Graphics

- Blender (e.g. Ducky3D)
- Unreal Engine Motion Design
- DaVinci Resolve Fusion Compositor

---

---

### awesome
https://github.com/terkelg/awesome-creative-coding
https://github.com/LimeLimeW/awesome-vjing
https://github.com/toplap/awesome-livecoding

- Creative Coding
- Live Coding
- VJing
- Generative Visuals
- Music Visualizer
- Op Art (Optical Art)
- Optical Illusions
- ...

