# ShaderToy

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

## Code

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

