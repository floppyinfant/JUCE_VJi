# LEARN

## Libraries, Frameworks, Tools

@see LEARN_LIBRARIES.md

---

## CG Algorithms

OpenGL
- 3D models (mesh) -> Assimp Library
- Textures
- Buffers
- Vertex Shaders (position)
- Fragment Shaders (color)

---

OpenPBR (Physically Based Rendering)
- https://github.com/AcademySoftwareFoundation/OpenPBR
- https://academysoftwarefoundation.github.io/OpenPBR/

---

1. Ray Casting

2. Ray Tracing

Ray Tracing in One Weekend
- https://raytracing.github.io/books/RayTracingInOneWeekend.html
- https://github.com/RayTracing/raytracing.github.io/
- https://github.com/RayTracing/raytracing.github.io/wiki/Further-Readings

3. Ray Marching
- https://youtu.be/khblXafu7iA

SDF
- https://en.wikipedia.org/wiki/Signed_distance_function

4. Path Tracing
- https://www.youtube.com/watch?v=NIpC53vesHo

---

---

## Shader Programming

- GLSL (OpenGL Shading Language) for OpenGL and Vulkan
- HLSL (High-Level Shading Language) for DirectX
- MSL (Metal Shading Language)
- WGSL (WebGPU Shading Language) for WebGPU
- OSL for AutoDesk Arnold, Blender Cycles
- Cg deprecated since 2012


### OpenGL Shading Language (GLSL)

https://github.com/KhronosGroup/GLSL

https://www.khronos.org/opengl/

https://wikis.khronos.org/opengl/OpenGL_Shading_Language <==========

https://www.khronos.org/developers/reference-cards

https://www.opengl.org/

https://github.com/g-truc/ogl-samples (Shaders in Data/)

File Extensions: vert.glsl, frag.glsl, *.vert, *.frag, *.fs, *.vs, ... , *.geom, *.tesc, *.tese, *.comp, *.spv

#### Tutorials
- https://learnopengl.com/Getting-started/Shaders+
- https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
- https://wikis.khronos.org/opengl/Uniform_(GLSL)

#### Uniforms, Attributes
- https://registry.khronos.org/OpenGL-Refpages/gl4/html/gl_FragCoord.xhtml

```c++
gl_Position
gl_FragCoord  // is in pixels from 0 .. screen_width, 0 .. screen_height
gl_FragColor
```

#### Example Code

```c++
// vertex shader
attribute vec3 a_Position;
varying float pos;

void main() {
    gl_Position = projectionMatrix * modelViewMatrix * vec4(a_Position, 1.0);
}

// fragment shader
varying float pos;

uniform vec2 RENDERSIZE;

void main() {
    vec2 uv = gl_FragCoord.xy / RENDERSIZE.xy;
    uv -= vec2(pos);
    uv.x *= RENDERSIZE.x / RENDERSIZE.y;
    
    gl_FragColor = pixelAlpha * vec4(1.0, 0.0, 0.0, 1.0);
}
```

---

### Open Shading Language (OSL)

*.osl

Blender: Text Editor --> Script Node in Shader Editor

https://docs.blender.org/manual/en/latest/render/cycles/osl/index.html

https://open-shading-language.readthedocs.io/en/latest/

https://github.com/imageworks/OpenShadingLanguage

https://www.youtube.com/watch?v=H8nHxRO7eX0 (CGMatter Fractals)

---

### GLFW

https://www.glfw.org/

https://www.glfw.org/documentation.html

@see LEARN_LIBRARIES.md

Examples:
- @see Dear ImGui
  - https://github.com/ocornut/imgui
  - https://github.com/dfranx/SHADERed (SHADERed uses ImGui)
- @see The Cherno
  - https://github.com/StudioCherno/Walnut
  - https://github.com/TheCherno/Hazel
  - OpenGL Tutorials
- @see Black_Hole
  - https://github.com/kavan010/black_hole


---

### Juce

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

#### @see src/vj/ShderEditor.cpp

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

#### @see src/gui/components/OpenGLComponent.cpp

based on https://medium.com/@Im_Jimmi/using-opengl-for-2d-graphics-in-a-juce-plug-in-24aa82f634ff

```C++
// Snippets
--- GL ---
juce::OpenGLContext openGLContext;
----------------
juce::OpenGLAppComponent openGLAppComponent;  // is a OpenGLRenderer implements initialize(), render(), shutdown()
juce::OpenGLRenderer openGLRenderer;          // implements newOpenGLContextCreated(), renderOpenGL(), openGLContextClosing()
  openGLContext.setRenderer(this); openGLContext.attachTo(*this);
----------------
--- ::newOpenGLContextCreated() ---
std::unique_ptr<juce::OpenGLShaderProgram> shaderProgram;
  shaderProgram.reset(new OpenGLShaderProgram(openGLContext));
  if (shaderProgram->addVertexShader(...) && shaderProgram->addFragmentShader(...) && shaderProgram->link()) { shaderProgram->use() }
juce::String vertexShader;
juce::String fragmentShader;
attribute
juce::OpenGLShaderProgram::Uniform uniform;
shape
----------------
--- RAW OpenGL ---
std::vector<Vertex> vertexBuffer; std::vector<unsigned int> indexBuffer;
GLuint vbo; GLuint ibo;
openGLContext.extensions.glGenBuffers(1, &vbo);
openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, vbo);
openGLContext.extensions.glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexBuffer.size(), vertexBuffer.data(), GL_STATIC_DRAW);
--- ::renderOpenGL() ---
OpenGLHelpers::clear(Colours::black);
shaderProgram->use();
openGLContext.extensions.glBindBuffer(..., vbo);
openGLContext.extensions.glBindBuffer(..., ibo);
openGLContext.extensions.glVertexAttribPointer(...);
openGLContext.extensions.glEnableVertexAttribArray(0);  // position attribute
openGLContext.extensions.glVertexAttribPointer(...);
openGLContext.extensions.glEnableVertexAttribArray(1);  // color attribute
glDrawElements(...);
openGLContext.extensions.glDisableVertexAttribArray(0);
openGLContext.extensions.glDisableVertexAttribArray(1);
----------------
--- GLSL: vert, vs ---
position = pixelPos;
gl_Position = projectionMatrix * viewMatrix * position;
----------------
--- GLSL: frag, fs ---
fragColor = mix(...);
gl_FragColor = pixelAlpha * fragColor;
----------------

```

#### Uniforms and other Code Snippets

```C++
#ifdef GL_ES
precision mediump float;
#endif
```

```C++
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

```C++
// --- GLSL defined Attributes, Uniforms
gl_Position
gl_FragCoord
gl_FragColor

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
code.replace ("attribute", "in");
output.replace ("varying", "out");
// --- OpenGLHelpers::translateFragmentShaderToV3 ---
out vec4 fragColor;
code.replace ("varying", "in")
code.replace ("texture2D", "texture")
code.replace ("gl_FragColor", "fragColor");
```

---

### openFrameworks

https://openframeworks.cc/learning/

https://openframeworks.cc/documentation/
- https://openframeworks.cc///documentation/gl/ofShader/

https://openframeworks.cc/examples/
- https://github.com/openframeworks/openFrameworks/tree/master/examples/

https://openframeworks.cc/ofBook/chapters/shaders.html
- https://github.com/openframeworks/openFrameworks/tree/master/examples/shader

```c++
shader.load("shadersGL3/shader");  // loads shader.frag and shader.vert from bin/data/shadersGL3/
```

---

### Assimp

https://github.com/assimp/assimp

https://learnopengl.com/Model-Loading/Assimp

Mesh Loading Library

---

---

## Shader Tutorials and Web Coding

https://www.youtube.com/watch?v=3mfvZ-mdtZQ

Links in the Description:
- https://iquilezles.org/articles/distfunctions2d/ (SDF)

https://youtu.be/kfM-yu0iQBk (Freya Holmer - Unity)

---

### ShaderToy

https://www.shadertoy.com/

https://www.shadertoy.com/howto

https://www.shadertoy.com/view/mtyGWy (Example from Tutorial)

https://www.youtube.com/watch?v=f4s1h2YETNY (YouTube Tutorial)

https://www.youtube.com/watch?v=0ifChJ0nJfM (Tutorial linked by ShaderToy)

https://shadertoyunofficial.wordpress.com/ (Tutorial linked by ShaderToy)

Apps:
- https://steamcommunity.com/sharedfiles/filedetails/?id=1726697188 (Wallpaper)
- https://chromewebstore.google.com/detail/shadertoy-unofficial-plug/ohicbclhdmkhoabobgppffepcopomhgl (Chrome Extension)
- https://github.com/patuwwy/ShaderToy-Chrome-Plugin/
- https://addons.mozilla.org/firefox/addon/shadertoy-unofficial-plugin/ (Firefox Extension)

Tools (mentioned in the Tutorial):
- https://iquilezles.org/articles/
- https://iquilezles.org/articles/palettes/
- http://dev.thi.ng/gradients
- https://graphtoy.com/

#### Uniforms

- https://www.shadertoy.com/howto

```c++
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

### The Book of Shaders

https://thebookofshaders.com/

https://github.com/patriciogonzalezvivo/thebookofshaders

https://meesrutten.github.io/book-of-shaders/

#### Running Shaders

https://thebookofshaders.com/04/ 

https://editor.thebookofshaders.com/ (Online Editor)

https://github.com/patriciogonzalezvivo/glslCanvas

```html
<canvas class="glslCanvas" data-fragment-url=“yourShader.frag" data-textures=“yourInputImage.png” width="500" height="500"></canvas>
```

https://github.com/patriciogonzalezvivo/glslViewer

```bash
glslViewer yourShader.frag yourInputImage.png —w 500 -h 500 -E screenshot,yourOutputImage.png
```

#### Uniforms

- https://thebookofshaders.com/03/
- https://github.com/patriciogonzalezvivo/ofxshader

```C++
uniform vec2 u_resolution;   // Canvas size (width,height) || viewport resolution (in pixels)
uniform vec2 u_mouse;        // mouse position in screen pixels || mouse pixel coords
uniform float u_time;        // Time in seconds since load || shader playback time (in seconds)

uniform float u_delta;       // delta time between frames (in seconds)
uniform vec4 u_date;         // year, month, day and seconds
```

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

#### Uniforms

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

### Processing

https://processing.org/

Java Mode

Python Mode

#### Py5
based on Processing (needs Java)
https://py5coding.org/
https://github.com/py5coding/py5

---

### p5.js

https://p5js.org/

https://github.com/processing/p5.js/blob/main/contributor_docs/webgl_mode_architecture.md

#### Tutorials and Documentation

https://p5js.org/tutorials/#webgl

https://p5js.org/tutorials/intro-to-shaders/

https://p5js.org/reference/p5/p5.Shader/

#### Uniforms

https://p5js.org/reference/p5.Shader/setUniform/

https://p5js.org/reference/#Environment (Environment)

https://p5js.org/reference/#Events (Events)

https://github.com/processing/p5.js/blob/main/contributor_docs/webgl_mode_architecture.md#global

```c++
// For all objects in all contexts, the following global uniforms are available:
uniform mat4 uModelViewMatrix  // A matrix to convert object-space positions into camera-space 
uniform mat4 uProjectionMatrix // A matrix to convert camera-space positions into screen space 
uniform mat3 uNormalMatrix     // A matrix to convert object-space normals into camera-space

// Additionally, these per-vertex properties are available as attributes:
attribute vec3 aPosition       // The position of the vertex in object space 
attribute vec3 aNormal         // For fills, a direction pointing outward from the surface 
attribute vec2 aTexCoord       // For fills, a coordinate between 0 and 1 in x and y referring to a location on a texture image 
attribute vec3 aVertexColor    // For fills, an optional per-vertex color
// more for ...
// Lights
// Materials
```

#### Example Sketch

```javascript
function setup() {
	createCanvas(600, 500);
	background('#000000');
}

function draw() {
	
}
```

---

### Three.js

https://threejs.org/

https://github.com/mrdoob/three.js

#### Three.js Example: NASA Solar System

https://eyes.nasa.gov/apps/solar-system/#/home

---

### Web APIs

#### WebGL

https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API

https://developer.mozilla.org/en-US/docs/Web/API/WebGLShader

https://developer.mozilla.org/en-US/docs/Web/API/WebGLProgram

https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext/uniform

#### WebGPU

https://developer.chrome.com/docs/web-platform/webgpu/overview

https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API

https://eliemichel.github.io/LearnWebGPU/basic-3d-rendering/shader-uniforms/a-first-uniform.html

##### WGSL

WebGPU Shading Language (WGSL)

https://gpuweb.github.io/gpuweb/wgsl/

#### WebAsm / WA

https://webassembly.org/ (WA)

#### CSS3D

---

### more Galleries, Links, ...

#### GLSL Sandbox

https://glslsandbox.com/

##### Uniforms

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

#### One Shader

https://oneshader.net/

##### Uniforms

You can add adjustable uniforms to your shader by adding the following comment after the declaration of a uniform:

When one or more adjustable uniforms are defined, a block with input sliders is visible below your shader.

```c++
uniform float xxx; // value=y, min=y, max=y, step=y
uniform vec3 xxx;  // value=x,y,z
```

#### TurtleToy

https://turtletoy.net/

#### OpenFrame

https://openframe.io/

---

---

## Shader Editors

### SHADERed

https://shadered.org/

https://github.com/dfranx/SHADERed

Shader IDE with Debugger

### KodeLife

https://hexler.net/kodelife

https://hexler.net/kodelife/manual/introduction

### Synesthesia

see below

### ISF Editor

https://docs.vidvox.net/isf-editor/ (Desktop Editor)

https://isf.vidvox.net/desktop-editor/

https://editor.isf.video/ (Online Editor with Examples)

### ShaderToy Online Editor

https://www.shadertoy.com/new

### The Book of Shaders Online Editor

https://editor.thebookofshaders.com/

### p5.js Online Editor

https://editor.p5js.org/

---

## VJing - Creative Coding - Live Coding
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

---

### Synesthesia

https://www.synesthesia.live/

https://app.synesthesia.live/docs/ssf/ssf.html?referrer=synesthesia (Synesthesia Shader Format (SSF))

https://app.synesthesia.live/docs/resources/glsl_resources.html <========

https://github.com/headstash/synesthesia-scripts

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

### Cables.gl

https://cables.gl/

https://cables.gl/docs/faq/shadertoy/shadertoy

---

### TouchDesigner

https://derivative.ca/

### vvvv

https://vvvv.org/

### TouchVIZ (iPad)

https://hexler.net/touchviz

---

## Motion Graphics

- Blender (e.g. Ducky3D)
- Unreal Engine Motion Design
- DaVinci Resolve Fusion Compositor

---

