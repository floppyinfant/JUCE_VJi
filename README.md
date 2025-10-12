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
# Configure and Build
cmake -S . -B build
cmake --build build
.\build\VJi_artefacts\Debug\Standalone\VJi.exe
# ---
# Install WebView2 on Windows
Register-PackageSource -provider NuGet -name nugetRepository -location https://www.nuget.org/api/v2
Install-Package Microsoft.Web.WebView2 -Scope CurrentUser -RequiredVersion 1.0.1901.177 -Source nugetRepository
```

---

## Tutorials

### Jetbrains Tutorials

https://www.jetbrains.com/clion/learn/

- https://www.jetbrains.com/help/clion/clion-quick-start-guide.html
- https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html (CMake Tutorial)

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

## OpenGL Shader Language (GLSL)

---

### ISF

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

---

## GLSL Sandbox

https://glslsandbox.com/

---

## ShaderToy

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

### Code

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

## OpenProcessing

https://openprocessing.org/

Learn: https://openprocessing.org/learn/

Create: https://openprocessing.org/sketch/create

Browse: https://openprocessing.org/browse

Shaders: https://openprocessing.org/discover/#/shader

Generative Art: https://openprocessing.org/discover/#/generativeart

Particles: https://openprocessing.org/discover/#/particles

https://openprocessing.org/browse?time=anytime&type=tags&q=particle&offset=0#

---

## P5.js

https://p5js.org/

### Example p5.js sketch

```javascript
function setup() {
	createCanvas(600, 500);
	background('#000000');
}

function draw() {
	
}
```

## WebGL

---

## openFrameworks

https://openframeworks.cc/learning/

https://openframeworks.cc/examples/
^- https://github.com/openframeworks/openFrameworks/tree/master/examples

https://openframeworks.cc/documentation/
- https://openframeworks.cc///documentation/gl/ofShader/

---

## Max/MSP Jitter

https://cycling74.com/products/jitter

https://cycling74.com/articles/jitter-resources-an-overview


---

## Pure Data GEM

---

## Synesthesia

https://www.synesthesia.live/

---

## TouchDesigner

---

