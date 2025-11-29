//
// Created by thorsten on 30.10.2025.
//
#pragma once

#include <JuceHeader.h>
#include <vector>
#include "../ShaderEditor.h"

#define ICHANNEL_IS_NOT_IMPLEMENTED 1

#define SHADER_2DDEMO_HEADER \
"/*  This demo shows the use of the OpenGLGraphicsContextCustomShader,\n" \
"    which allows a 2D area to be filled using a GL shader program.\n" \
"\n" \
"    Edit the shader program below and it will be \n" \
"    recompiled in real-time!\n" \
"*/\n\n"


class ShaderPresets {
public:

    struct ShaderPreset {
        const char *name;
        const char *fragmentShader;
        /*
        const char *vertexShader;
        const char *bufferA;
        const char *bufferB;
        const char *bufferC;
        const char *bufferD;
        const char *cubemapA;
        const char *commonBuffer;
        const char *soundBuffer;
        const char *iChannel0;
        const char *iChannel1;
        const char *iChannel2;
        const char *iChannel3;
        */
    };

    static juce::Array<ShaderPreset> getPresets() {

        /*
        // C-array
        ShaderPreset presetShaders[99];
        presetShaders[0] = { "ShaderToy - Plasma", "void mainImage(out vec4 fragColor, in vec2 fragCoord){}\n" };

        // std::vector
        std::vector<ShaderPreset> pre;
#define CODE "void mainImage(out vec4 fragColor, in vec2 fragCoord)"
        const char* CODE_STR = "void mainImage(out vec4 fragColor, in vec2 fragCoord)";
        static const juce::String CODE_STR_JUCER(CODE_STR);
        pre.push_back({"Plasma", CODE_STR_JUCER.toRawUTF8()});

        // Juce-Array
        juce::Array<ShaderPreset> shaderPresets;
        shaderPresets.add({"ShaderToy - Plasma",
            "void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
                "{\n"
                "    vec2 uv = fragCoord / iResolution.xy;\n"
                "    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
                "    fragColor = vec4(col, 1.0);\n"
                "}\n"
                "\n"
        });
        */

        // -----------------------------

        ShaderPreset presets[] =
        {
            {
                "ShaderToy - Plasma",

                "void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
                "{\n"
#if JUCER_OPENGL_ES
                "    " JUCE_MEDIUMP " vec2 uv = fragCoord / iResolution.xy;\n"
                "    " JUCE_MEDIUMP " vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
#else
                "    vec2 uv = fragCoord / iResolution.xy;\n"
                "    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
#endif
                "    fragColor = vec4(col, 1.0);\n"
                "}\n"
                "\n"
            },

            // ---------------------------------------------------------------------------

            {
                "Simple Gradient",

                SHADER_2DDEMO_HEADER
                "void main()\n"
                "{\n"
                "    " JUCE_MEDIUMP " vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);\n"
                "    " JUCE_MEDIUMP " vec4 colour2 = vec4 (0.0, 0.8, 0.6, 1.0);\n"
                "    " JUCE_MEDIUMP " float alpha = pixelPos.x / 1000.0;\n"
                "    gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);\n"
                "}\n"
            },

            {
                "Circular Gradient",

                SHADER_2DDEMO_HEADER
                "void main()\n"
                "{\n"
                "    " JUCE_MEDIUMP " vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);\n"
                "    " JUCE_MEDIUMP " vec4 colour2 = vec4 (0.3, 0.4, 0.4, 1.0);\n"
                "    " JUCE_MEDIUMP " float alpha = distance (pixelPos, vec2 (600.0, 500.0)) / 400.0;\n"
                "    gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);\n"
                "}\n"
            },

            // ---------------------------------------------------------------------------

            {
                "ShaderToy Tutorial",  // https://www.shadertoy.com/view/mtyGWy

                R"(/* https://www.shadertoy.com/view/mtyGWy */

vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        float d = length(uv) * exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

        d = sin(d*8. + iTime)/8.;
        d = abs(d);
        d = pow(0.01 / d, 1.2);
        finalColor += col * d;
    }
    fragColor = vec4(finalColor, 1.0);
}
            )"
            },

            // ---------------------------------------------------------------------------

            {
                "Raymarching Tutorial",  // https://www.shadertoy.com/view/lcs3DH

                R"(// This scene is taken from my second tutorial about shader coding,
// which introduces the concept of raymarching as well as some useful
// transforms and space-bending techniques.
//
//     Mouse interactive!
//                            Video URL: https://youtu.be/khblXafu7iA

// 2D rotation function
mat2 rot2D(float a) {
    return mat2(cos(a), -sin(a), sin(a), cos(a));
}

// Custom gradient - https://iquilezles.org/articles/palettes/
vec3 palette(float t) {
    return .5+.5*cos(6.28318*(t+vec3(.3,.416,.557)));
}

// Octahedron SDF - https://iquilezles.org/articles/distfunctions/
float sdOctahedron(vec3 p, float s) {
    p = abs(p);
    return (p.x+p.y+p.z-s)*0.57735027;
}

// Scene distance
float map(vec3 p) {
    p.z += iTime * .4; // Forward movement

    // Space repetition
    p.xy = fract(p.xy) - .5;     // spacing: 1
    p.z =  mod(p.z, .25) - .125; // spacing: .25

    return sdOctahedron(p, .15); // Octahedron
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 uv = (fragCoord * 2. - iResolution.xy) / iResolution.y;
    vec2  m = (iMouse.xy * 2. - iResolution.xy) / iResolution.y;

    // Default circular motion if mouse not clicked
    if (iMouse.z <= 0.) m = vec2(cos(iTime*.2), sin(iTime*.2));

    // Initialization
    vec3 ro = vec3(0, 0, -3);         // ray origin
    vec3 rd = normalize(vec3(uv, 1)); // ray direction
    vec3 col = vec3(0);               // final pixel color

    float t = 0.; // total distance travelled

    int i; // Raymarching
    for (i = 0; i < 80; i++) {
        vec3 p = ro + rd * t; // position along the ray

        p.xy *= rot2D(t*.15 * m.x);     // rotate ray around z-axis

        p.y += sin(t*(m.y+1.)*.5)*.35;  // wiggle ray

        float d = map(p);     // current distance to the scene

        t += d;               // "march" the ray

        if (d < .001 || t > 100.) break; // early stop
    }

    // Coloring
    col = palette(t*.04 + float(i)*.005);

    fragColor = vec4(col, 1);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "raymarching / sphere tracing tut",  // https://www.shadertoy.com/view/WsdXRS

                R"(
#define MAX_STEPS 1000
#define MAX_DIST 100.0
#define SURF_DIST 0.0001

float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float GetDist(vec3 p) {
    vec4 s = vec4(0.0, 1.0, 6.0, 1.0);
	s.y += sin(iTime);

    float sphereDist = length(p - s.xyz) - s.w;
    float planeDist = p.y;

    float d = smin(sphereDist, planeDist, 0.8);
    return d;

}

float RayMarch(vec3 ro, vec3 rd) {
	float dO = 0.0;

    for (int i = 0; i < MAX_STEPS; i++) {
    	vec3 p = ro + rd * dO;
        float dS = GetDist(p);
        dO += dS;

        if (dO > MAX_DIST || dS < SURF_DIST) {
            break;
        }
    }

    return dO;
}

vec3 GetNormal(vec3 p) {
	float d = GetDist(p);
    vec2 e = vec2(0.01, 0);

    vec3 n = d - vec3(
    	GetDist(p - e.xyy),
        GetDist(p - e.yxy),
        GetDist(p - e.yyx)
    );

    return normalize(n);
}


float GetLight(vec3 p) {
	vec3 lightPos = vec3(0.0, 5.0, 6.0);
    lightPos.xz += vec2(sin(iTime), cos(iTime)) * 2.0;
    vec3 l = normalize(lightPos - p);
    vec3 n = GetNormal(p);

    float dif = clamp(dot(n, l), 0.0, 1.0);

    return dif;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord - 0.5 * iResolution.xy) / iResolution.y;

    vec3 col = vec3(0.0);

    vec3 ro = vec3(0.0, 1.0, 0.0);
    vec3 rd = normalize(vec3(uv.x, uv.y, 1.0));

    float d = RayMarch(ro, rd);

    vec3 p = ro + rd * d;

    float dif = GetLight(p);
    col = vec3(dif);


    fragColor.rgb = col;
    fragColor.a = 1.0;
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "raymarching tutorial 2",  // https://www.shadertoy.com/view/XllyW4

                R"(

#define STEPS 48

float map(vec3 p, float r, float dist) {
    vec3 pos = p + vec3(0., 0.,0.);
    p = fract(pos) * 2.0 - 1.0;
    return length(p) - r;
}

float trace(vec3 o, vec3 r) {
    float t = 0.0;
    int i = 1;
    float rd = .6*(sin(iTime+(r.z*3.14))+1.);
    for(i = 1; i < STEPS; ++i) {
       vec3 p = o + r * t;
       float dist = length(p);
       float d = map(p, rd, dist);
       t += d * .5;
    }
    return t;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;
    vec3 r = normalize(vec3(uv, 1.0));
    vec3 o = vec3(0., 0., iTime*.5);
    float d = trace(o, r);
    vec3 c = 1.0 / vec3(1.0 + d * d * .3);
    fragColor = vec4(1.0 - c, 1.0);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Boing Ball (320x200)",  // https://www.shadertoy.com/view/4ssGWn

                R"(
#define PI 3.1415926536

const vec2 res = vec2(320.0,200.0);
const mat3 mRot = mat3(0.9553, -0.2955, 0.0, 0.2955, 0.9553, 0.0, 0.0, 0.0, 1.0);
const vec3 ro = vec3(0.0,0.0,-4.0);

const vec3 cRed = vec3(1.0,0.0,0.0);
const vec3 cWhite = vec3(1.0);
const vec3 cGrey = vec3(0.66);
const vec3 cPurple = vec3(0.51,0.29,0.51);

const float maxx = 0.378;

//                       _                                       _ _ _ _ _ _ _
//       /\             (_)                                     | | | | | | | |
//      /  \   _ __ ___  _  __ _  __ _  __ _  __ _  __ _  __ _  | | | | | | | |
//     / /\ \ | '_ ` _ \| |/ _` |/ _` |/ _` |/ _` |/ _` |/ _` | | | | | | | | |
//    / ____ \| | | | | | | (_| | (_| | (_| | (_| | (_| | (_| | |_|_|_|_|_|_|_|
//   /_/    \_\_| |_| |_|_|\__, |\__,_|\__,_|\__,_|\__,_|\__,_| (_|_|_|_|_|_|_)
//                          __/ |
//                         |___/

//By @unitzeroone
//Check out http://www.youtube.com/watch?feature=player_detailpage&v=ZmIf-5MuQ7c#t=26s for context.
//Decyphering the code&magic numbers and optimizing is left as excercise to the reader ;-)

//-1/5/2013 FIX : Windows was rendering "inverted z checkerboard" on entire screen.
//-1/5/2013 CHANGE : Did a modification for the starting position, so ball doesn't start at bottom right.
//-1/5/2013 CHANGE : Tweaked edge bounce.
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float asp = iResolution.y/iResolution.x;
	vec2 uv = (fragCoord.xy / iResolution.xy);
	vec2 uvR = floor(uv*res);
	vec2 g = step(2.0,mod(uvR,16.0));
	vec3 bgcol = mix(cPurple,mix(cPurple,cGrey,g.x),g.y);
	uv = uvR/res;
	float xt = mod(iTime+1.0,6.0);
	float dir = (step(xt,3.0)-.5)*-2.0;
	uv.x -= (maxx*2.0*dir)*mod(xt,3.0)/3.0+(-maxx*dir);
	uv.y -= abs(sin(4.5+iTime*1.3))*0.5-0.3;
	bgcol = mix(bgcol,bgcol-vec3(0.2),1.0-step(0.12,length(vec2(uv.x,uv.y*asp)-vec2(0.57,0.29))));
	vec3 rd = normalize(vec3((uv*2.0-1.0)*vec2(1.0,asp),1.5));
	float b = dot(rd,ro);
	float t1 = b*b-15.6;
    float t = -b-sqrt(t1);
	vec3 nor = normalize(ro+rd*t)*mRot;
	vec2 tuv = floor(vec2(atan(nor.x,nor.z)/PI+((floor((iTime*-dir)*60.0)/60.0)*0.5),acos(nor.y)/PI)*8.0);
	fragColor = vec4(mix(bgcol,mix(cRed,cWhite,clamp(mod(tuv.x+tuv.y,2.0),0.0,1.0)),1.0-step(t1,0.0)),1.0);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Amiga Boing Ball Demo",  // https://www.shadertoy.com/view/llsyzX

                R"(
const float BALL_RADIUS = 0.7;
const float RED = 0.0;
const float WHITE = 1.0;
const float SHADOW = 0.2;
const float SHADOW_RADIUS = BALL_RADIUS/2.0;
const float PI = 3.1415926535;

float boingBall(vec3 ro, float r) {
 	return length(ro)-r;
}

vec2 map(vec3 ro, vec3 p) {
    float r = sqrt(pow(BALL_RADIUS,2.0)-pow(p.y-ro.y,2.0));
    float vCoord = smoothstep(0.0,BALL_RADIUS/2.0,abs(ro.y-p.y));
    float horizontal = step(0.5,0.5+0.5*sin(15.0*(ro.y-p.y)));
    float vertical = step(0.5,0.5+0.5*sin(15.0*(ro.x-p.x+iTime)));
    float color = horizontal*vertical;
    horizontal = 1.0-step(0.5,0.5+0.5*sin(15.0*(ro.y-p.y)));
    vertical = 1.0-step(0.5,0.5+0.5*sin(15.0*(ro.x-p.x+iTime)));
    color += horizontal*vertical;
    vec2 dist = vec2(boingBall(ro-p,BALL_RADIUS), color);
    return dist;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    uv -= 0.5;
    uv *= 2.0;
    uv.x *= iResolution.x/iResolution.y;

    const float DIVISION = 0.105;
    const float GRID_THICKNESS = 0.01;
    vec3 color = vec3(0.5);

    for (float i = -1.0+DIVISION; i < 1.0-DIVISION; i += DIVISION) {
        if (abs(uv.x) > 0.8 || abs(uv.y) > 0.8) break;
    	if (uv.x >= i && uv.x < i+GRID_THICKNESS)
            color = vec3(0.7,0.0,0.5);
        for (float j = -1.0+DIVISION; j < 1.0-DIVISION; j += DIVISION) {
        if (uv.y < -0.8 || uv.y > 0.8) break;
    	if (uv.y >= j && uv.y < j+GRID_THICKNESS)
            color = vec3(0.7,0.0,0.5);
        }
    }

    const int MAX_STEPS = 50;
    const float MIN_DIST = 0.01;

    vec3 ro = vec3(0.0,0.0,-3.0);
    vec3 screen = vec3(uv.x,uv.y,0.0);
    vec3 rd = normalize(screen-ro);
    vec3 ballPos = vec3(abs(mod(iTime,6.0)-3.0)-1.5,abs(sin(iTime)*2.)-0.8,3.0);
    vec2 shadowPos = vec2(ballPos.xy)/2.;
    shadowPos.x += 0.2;

    if (distance(uv,shadowPos) < SHADOW_RADIUS) color = mix(color,vec3(SHADOW),0.9);

    for (int i = 0; i < MAX_STEPS; i++) {
    	vec2 d = map(ro, ballPos);
        if (d.x < MIN_DIST) {
        	color = vec3(1.0,d.y,d.y);
            color /= .01*pow(length(ro*2.),3.0);
            break;
        }
        ro += rd*d.x;
    }

	fragColor = vec4(color,1.0);
}
)"
            },

            // ---------------------------------------------------------------------------

            // TODO needs Buffers
            // L:\WORKSPACES\AUDIO_WS\Projects\VJi\src\vj\shaders/Presets.h(538):
            // error C2026: Zeichenfolge zu lang, Zeichen am Ende wurden entfernt

            /*
            {
                "State of the art",  // https://www.shadertoy.com/view/wsVcWd

                R"(
// Created by David Gallardo - xjorma/2020
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0
// https://www.shadertoy.com/view/wsVcWd

// ---------------------------------------------------------------------------
// Common
// ---------------------------------------------------------------------------
const int maxVert = 56;

const int AnbFrames = 13;
const int AnbVertices = 51;
const int Astride = 26;

const int BnbFrames = 10;
const int BnbVertices = 52;
const int Bstride = 26;

const int CnbFrames = 8;
const int CnbVertices = 55;
const int Cstride = 28;


// From https://www.shadertoy.com/view/4djSRW

float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

float hash13(vec3 p3)
{
	p3  = fract(p3 * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

// ---------------------------------------------------------------------------
// Buffer A
// ---------------------------------------------------------------------------
const uint vertices[338] = uint[](
0xa10d9c28U, 0x973c954aU, 0x90569d7bU, 0xa372b950U, 0xd44fd850U, 0xe556ec5fU, 0xe461cf5aU, 0xc559b867U, 0xa39893aeU, 0x96b99bc1U, 0x95cc89d9U, 0x72d96acbU, 0x65bc73abU, 0x61a855a2U, 0x3b9b2fb3U, 0x25b71eb9U, 0x11b60fb1U, 0x12af17adU, 0x1ead27a6U, 0x2e8e5d8dU, 0x60735d54U, 0x56485135U, 0x4c1e4a0dU, 0x6d0d7215U, 0x77217a17U, 0x7c0e00d9U,
0xa70da52aU, 0xa743a555U, 0xb077b98cU, 0xcc9cd494U, 0xdc91df89U, 0xe185e388U, 0xea90e89fU, 0xd7a8bfadU, 0xaab1a1b7U, 0x9fbf9ec9U, 0x9ad286d9U, 0x78d570ccU, 0x6ec278b7U, 0x7bad74a2U, 0x65965183U, 0x4587379aU, 0x3aab39b5U, 0x34b72eacU, 0x2c9d308fU, 0x48715d79U, 0x72747167U, 0x6a515e3cU, 0x5521510dU, 0x720d7617U, 0x7f23821aU, 0x860d00d9U,
0xab0da330U, 0xa2489e54U, 0x9b689d86U, 0xa69ebdabU, 0xcbb0cea8U, 0xca9ecf96U, 0xd89bdaaaU, 0xd9bbcec3U, 0xadb78cb0U, 0x8bbb91c4U, 0x91ca85d9U, 0x66d95fd3U, 0x5bcc6cb3U, 0x6fa858a0U, 0x5097476eU, 0x36631e62U, 0x1c6b1279U, 0x0e760d6aU, 0x12592b55U, 0x4d5b627aU, 0x6b626653U, 0x5d44592fU, 0x571b5b0dU, 0x7a0d7a13U, 0x81238618U, 0x880d00d9U,
0xb00da430U, 0x9d40964eU, 0x8e5e8b7eU, 0x938dba88U, 0xc48fcca6U, 0xd4a4d7a2U, 0xe2a4d6acU, 0xc7aeb997U, 0xa19b83a8U, 0x85b98fc1U, 0x89c883d9U, 0x66d961cfU, 0x5bc865b2U, 0x63ac51a4U, 0x459a377fU, 0x286d1656U, 0x0e44033cU, 0x03320a34U, 0x15402654U, 0x3e6f4d7bU, 0x5b615d54U, 0x5d445b33U, 0x581a590dU, 0x810d8012U, 0x81208715U, 0x890d00d9U,
0xa50d9d29U, 0x99378c50U, 0x845a8779U, 0x8e7fb16bU, 0xd278da7cU, 0xdc80de8fU, 0xda95d495U, 0xcf80b179U, 0x999187a7U, 0x86b595c0U, 0x8dcb83d9U, 0x66d961cfU, 0x5bc865b2U, 0x5faf4faaU, 0x41a13095U, 0x1a8d037dU, 0x0074005dU, 0x03510851U, 0x0e5e096fU, 0x3286488aU, 0x54605752U, 0x4f444b30U, 0x4a194d0dU, 0x740d7517U, 0x77237a1bU, 0x800d00d9U,
0x9b0d9429U, 0x903b8b4fU, 0x845a897aU, 0x917dac57U, 0xc94fd84fU, 0xe058e366U, 0xdd6dd156U, 0xc45baf6eU, 0x9e928eacU, 0x94c29bc8U, 0x8fd18ed9U, 0x6cd96aceU, 0x64c76db3U, 0x60b650b7U, 0x45b835baU, 0x1eba06aaU, 0x00930485U, 0x0b850a99U, 0x1ba924adU, 0x3ea85196U, 0x50624f54U, 0x4b484538U, 0x431c460dU, 0x680d6715U, 0x6b277418U, 0x780e00d9U,
0x9b0d9429U, 0x923c9048U, 0x8a579578U, 0x9b77ad51U, 0xd047da48U, 0xe74fec5bU, 0xe45ed052U, 0xc356b463U, 0xa19590abU, 0x96b99ec3U, 0x94ca8cd6U, 0x74d76cc8U, 0x65bc73abU, 0x62ad54acU, 0x41ad30b6U, 0x20bd10b9U, 0x05b503aeU, 0x06ac0baeU, 0x15b122acU, 0x359e5894U, 0x5b725852U, 0x50444a33U, 0x471c450dU, 0x690d6b16U, 0x6f217316U, 0x760d00d9U,
0x9c0d9d2fU, 0x9b469b56U, 0xa064ab79U, 0xbb84d083U, 0xe07cde69U, 0xe162e765U, 0xeb7ae986U, 0xdb8ac792U, 0xaf9d99adU, 0x9fb1a6c0U, 0x9cca99d7U, 0x7ed772c8U, 0x70bb7cb0U, 0x7ca86ea0U, 0x63994e8fU, 0x3f9b37a3U, 0x38b536c1U, 0x2fc42ab8U, 0x2aa73293U, 0x477d6a89U, 0x6e696457U, 0x5947522eU, 0x4d174b0dU, 0x6b0d6b12U, 0x76207917U, 0x7b0d00d9U,
0xa50da330U, 0xa2489e54U, 0xa464a77cU, 0xaf97bfa3U, 0xcda6d3a6U, 0xd19ad892U, 0xe097e1aeU, 0xdfb8d0bbU, 0xb1b494afU, 0x92b799c2U, 0x93cb8cd8U, 0x6fd869ceU, 0x63c870afU, 0x73a66ba2U, 0x60984670U, 0x3973257dU, 0x268d2199U, 0x1b981889U, 0x19782d68U, 0x4b5d6d7eU, 0x6e636653U, 0x5d44572eU, 0x5319530dU, 0x710d7214U, 0x7c268018U, 0x830d00d9U,
0xb00da731U, 0xa3449c51U, 0x95619082U, 0x9998c29fU, 0xc4a1cba8U, 0xd4a4d7a2U, 0xdda5cfbdU, 0xc4bfb7a9U, 0xa3a985aeU, 0x85b98fc2U, 0x8bc983d9U, 0x66d95bd3U, 0x59c768b3U, 0x67ab54a5U, 0x4a973973U, 0x295f1f4fU, 0x12490746U, 0x073e1238U, 0x20422e4dU, 0x4263527bU, 0x60606453U, 0x5f435c31U, 0x5b1b5b0dU, 0x810d8012U, 0x83248916U, 0x8f0d00d9U,
0xa90da02bU, 0x9b388d4fU, 0x885b8979U, 0x9184b475U, 0xca84d48fU, 0xd794db98U, 0xe0a3daa7U, 0xd39eb685U, 0x999184a5U, 0x86b591bdU, 0x89c883d9U, 0x66d961cfU, 0x5bc865b2U, 0x61ac50a4U, 0x459a348bU, 0x227c0e6bU, 0x06600156U, 0x05400837U, 0x10450e59U, 0x3a794980U, 0x575f5752U, 0x55415430U, 0x521b520dU, 0x7a0d7a17U, 0x7b1f8313U, 0x830d00d9U,
0xa10d9a2bU, 0x923a8b4fU, 0x845a8879U, 0x917daf63U, 0xd062d967U, 0xdb75db7cU, 0xd67dd37dU, 0xcd6bb271U, 0x99918babU, 0x90bb98c8U, 0x8dd08ed9U, 0x69d967cfU, 0x62c66bb6U, 0x5eb151b1U, 0x44ad38acU, 0x1aa50092U, 0x0086006dU, 0x04700574U, 0x0a880e91U, 0x3e964c8fU, 0x50625355U, 0x4f4b4938U, 0x461b460dU, 0x6c0d6d14U, 0x6f27761aU, 0x800d00d9U,
0x9b0d9429U, 0x903b8b4aU, 0x84579378U, 0x9777ac54U, 0xcd44da46U, 0xe74beb58U, 0xe25ad14eU, 0xc356b162U, 0x9e928eacU, 0x95c09bc6U, 0x8fd18cd6U, 0x70d86cc8U, 0x66c06db0U, 0x62b14eb3U, 0x43b632bdU, 0x20bd0fb1U, 0x07a50399U, 0x09910c9dU, 0x19ad23b1U, 0x3ea85796U, 0x53625154U, 0x4b484538U, 0x431c430dU, 0x640d6715U, 0x6c237016U, 0x730d00d9U);

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    fragCoord = floor(fragCoord);
    float frame = (fragCoord.y + float(iFrame)) / 8.;
    int vtxIdx = int(fragCoord.x);
    if( vtxIdx >= Astride)
    {
        discard;
    }
    uint cv0 = vertices[vtxIdx + (int(floor(frame + 0.)) % AnbFrames) * Astride];
    vec4 v0 = vec4(vec2(cv0>>24, (cv0>>16)&255U),vec2((cv0>>8)&255U, (cv0)&255U));
    uint cv1 = vertices[vtxIdx + (int(floor(frame + 1.)) % AnbFrames) * Astride];
    vec4 v1 = vec4(vec2(cv1>>24, (cv1>>16)&255U),vec2((cv1>>8)&255U, (cv1)&255U));
    vec4 v = mix(v0, v1, fract(frame));
    fragColor = v;
}

// ---------------------------------------------------------------------------
// Buffer B
// ---------------------------------------------------------------------------
const uint vertices[260] = uint[](
0x440d4d2aU, 0x59496662U, 0x716c7675U, 0x6d846b88U, 0x5960545fU, 0x31862a8cU, 0x148d1390U, 0x18942b93U, 0x348e4879U, 0x50785692U, 0x5dac68bcU, 0x66c45dd0U, 0x5ad75ad9U, 0x8bd98cd4U, 0x8cd29bd6U, 0xafd9b4d9U, 0xb9d9bed9U, 0xc2d9cdd9U, 0xd5d9c8cfU, 0xb1bdacb5U, 0xa87aa369U, 0xa45fac42U, 0xb61dba0dU, 0x990d8e1fU, 0x81397e39U, 0x7122630dU,
0x440d4d29U, 0x5848655bU, 0x726a7573U, 0x707b6b7fU, 0x56594f59U, 0x2c7e2586U, 0x1688128bU, 0x178e298cU, 0x33814e6cU, 0x51765791U, 0x5fa968bcU, 0x62c05fd0U, 0x5dd85ad9U, 0x8bd98bd7U, 0x8cce8fc7U, 0xb1ccc2d0U, 0xc3d4c2d9U, 0xc2d9cdd9U, 0xd5d9d8c5U, 0xb6b0aca9U, 0xab7aa767U, 0xa65fa945U, 0xa929b30dU, 0x8b0d861bU, 0x81297a2eU, 0x7020630dU,
0x440d4d29U, 0x5947655dU, 0x726a7573U, 0x6a88648bU, 0x4c664265U, 0x2f7f1e98U, 0x0e97089aU, 0x0d9c219dU, 0x35874276U, 0x497f5196U, 0x5dab6cc0U, 0x63c662d0U, 0x61d662d9U, 0x8bd98bd7U, 0x8cce90caU, 0xb6c6ccc4U, 0xd0d3d4d9U, 0xd7d9dbd9U, 0xdfd9dab2U, 0xb2acaaaaU, 0xa97ba569U, 0xa261a741U, 0xac27b30dU, 0x900d881bU, 0x822a7c32U, 0x6f21630dU,
0x490d4e29U, 0x56495e63U, 0x69746682U, 0x5ea158a0U, 0x438c3785U, 0x2f8916b6U, 0x0ebc00c0U, 0x04c317c0U, 0x25ad329bU, 0x389847a9U, 0x54b85ac2U, 0x5ec967cfU, 0x69d46bd9U, 0x8bd98bd7U, 0x93d79ad6U, 0xb6c5cdb8U, 0xe4d4ead7U, 0xfdd7ffd4U, 0xecced5a6U, 0xc9a4a5b4U, 0xa1849f76U, 0xa461ab40U, 0xb025b50dU, 0x9a0d9120U, 0x853b8140U, 0x6c22630dU,
0x490d4e29U, 0x56495e63U, 0x64756386U, 0x53ad4eb1U, 0x29a71da3U, 0x17a913b1U, 0x10bd0cd9U, 0x13d917d9U, 0x1bc71ebeU, 0x25b72fb9U, 0x36be3cc3U, 0x50d255d7U, 0x61d96bd9U, 0x8bd98bd7U, 0x93d79ad6U, 0xb4b6c7a7U, 0xe7bdf1beU, 0xffbbfeb7U, 0xf4b8c594U, 0xbb959db1U, 0x988d997bU, 0xa461ab40U, 0xb327ba0dU, 0x9e0d9622U, 0x8a3b8345U, 0x6e22680dU,
0x490d5528U, 0x5b485e63U, 0x61735983U, 0x4fab48b2U, 0x29b61bb7U, 0x13bc0fc1U, 0x0fcb11d9U, 0x15d91ed9U, 0x20ca25c7U, 0x2ac731c7U, 0x37c849cbU, 0x50d056d5U, 0x61d96bd9U, 0x85d98bd8U, 0x91cd97c7U, 0xb692c695U, 0xe0a0e99fU, 0xf995f992U, 0xe596b57eU, 0xab829798U, 0x9482997bU, 0xa660b140U, 0xb828c00eU, 0x9e0d9622U, 0x8f358940U, 0x781f6e0dU,
0x500d5721U, 0x5d306050U, 0x6363587bU, 0x499f40afU, 0x2bb722bbU, 0x19c117c5U, 0x14cc16d2U, 0x1ad929d9U, 0x29d12bccU, 0x2dcb31c9U, 0x37c84ac5U, 0x5dc761ccU, 0x61d996d9U, 0x95d191c7U, 0x94b39eaaU, 0xaa77c27cU, 0xd083d981U, 0xec73eb6fU, 0xd679a364U, 0x9b6c977dU, 0x926c9f67U, 0xa65cb140U, 0xb928c20dU, 0xa30da016U, 0x96269130U, 0x7e1c760eU,
0x4c0d5421U, 0x5a345e48U, 0x63635a7cU, 0x499f40afU, 0x2bb722bbU, 0x19be14c4U, 0x15cc16d2U, 0x1ad929d9U, 0x26d127ccU, 0x28ca2fc8U, 0x37c84bc6U, 0x60c964ceU, 0x61d996d9U, 0x95d18fc7U, 0x96b7a0acU, 0xaf85b77eU, 0xce86da8aU, 0xe98be786U, 0xd884b26bU, 0xa870978aU, 0x91739d68U, 0xa55cb140U, 0xb928c20dU, 0x9e0d981dU, 0x93298a30U, 0x791c730dU,
0x480d5026U, 0x553f5a5aU, 0x646c5b9dU, 0x55b541b2U, 0x2db120b0U, 0x1bb515c4U, 0x13cc12d4U, 0x12d921d9U, 0x23d125ccU, 0x27c32ec3U, 0x39c549cbU, 0x52d059d8U, 0x5dd996d9U, 0x95d19ec8U, 0xa7c5b5b3U, 0xc49fcc9eU, 0xe9bdefc9U, 0xf6c6f8bfU, 0xf0b8d38eU, 0xc58aa1a5U, 0x9778a068U, 0xa55cad3fU, 0xb424b80dU, 0x9e0d971aU, 0x91268542U, 0x75276a0fU,
0x480d5026U, 0x553f5965U, 0x677d66a4U, 0x5fb546a6U, 0x359a2e9bU, 0x1bb515c4U, 0x10cf04d3U, 0x02d712d5U, 0x16cf1cc9U, 0x27bb30b1U, 0x36ae4cc3U, 0x54cd5bd6U, 0x5dd99fd9U, 0xa5d7b2d0U, 0xbaccc9c4U, 0xd6bfdec3U, 0xe1cfe4d9U, 0xead9f1d9U, 0xe7b9e3b1U, 0xddacb2b6U, 0x9c79a069U, 0xa45da650U, 0xab28b30dU, 0x980d9517U, 0x8f237c43U, 0x6e28610dU);

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    fragCoord = floor(fragCoord);
    float frame = (fragCoord.y + float(iFrame)) / 8.;
    int vtxIdx = int(fragCoord.x);
    if( vtxIdx >= Bstride)
    {
        discard;
    }
    uint cv0 = vertices[vtxIdx + (int(floor(frame + 0.)) % BnbFrames) * Bstride];
    vec4 v0 = vec4(vec2(cv0>>24, (cv0>>16)&255U),vec2((cv0>>8)&255U, (cv0)&255U));
    uint cv1 = vertices[vtxIdx + (int(floor(frame + 1.)) % BnbFrames) * Bstride];
    vec4 v1 = vec4(vec2(cv1>>24, (cv1>>16)&255U),vec2((cv1>>8)&255U, (cv1)&255U));
    vec4 v = mix(v0, v1, fract(frame));
    fragColor = v;
}

// ---------------------------------------------------------------------------
// Buffer C
// ---------------------------------------------------------------------------
const uint vertices[224] = uint[](
0x610d6016U, 0x58205016U, 0x4c0d360dU, 0x35263a3eU, 0x404f456bU, 0x428734a4U, 0x2dc12dd2U, 0x2ed82dd9U, 0x30d935d9U, 0x34d135caU, 0x3ab7479eU, 0x519655a5U, 0x5baf61b3U, 0x6bb171abU, 0x749d7495U, 0x728b7686U, 0x7d838981U, 0x9a81a285U, 0xa492a59cU, 0xa3a3a5adU, 0xaaadada6U, 0xae96ab85U, 0xa67b9e76U, 0x95738372U, 0x776f6e65U, 0x6c517036U, 0x742d791fU, 0x7d0d00d9U,
0x650d6414U, 0x5b205215U, 0x4d0d360dU, 0x35203a3eU, 0x404f456bU, 0x428733a3U, 0x2dc12ed2U, 0x30d82dd9U, 0x30d938d9U, 0x36d137c8U, 0x3ab7479eU, 0x519655a5U, 0x5baf61b3U, 0x6bb171abU, 0x749d7499U, 0x718f7a8eU, 0x808d8d8dU, 0x9994a499U, 0xa5a2a5a9U, 0xa1b19dbcU, 0xa1bca7baU, 0xae98aa8fU, 0xa0899684U, 0x8e7f857aU, 0x7f75746bU, 0x70507236U, 0x772e7d1fU, 0x810d00d9U,
0x620d6116U, 0x5b285018U, 0x4d0d360dU, 0x35203a3eU, 0x4457496dU, 0x43892f9eU, 0x25b028c3U, 0x30d333d5U, 0x39d340cdU, 0x3ec636c6U, 0x33af3fa1U, 0x4f9851a9U, 0x54b65bbcU, 0x67bb6fb5U, 0x72a9729fU, 0x71937893U, 0x7e958d9bU, 0x97a09faaU, 0xa2b4a2baU, 0x99c297caU, 0x9dcca7c6U, 0xabafa7a0U, 0x9e96948eU, 0x8a878180U, 0x7d79776eU, 0x7251723cU, 0x77307b1fU, 0x7d0d00d9U,
0x620d6016U, 0x5a2a5019U, 0x4d0d360dU, 0x35213a3eU, 0x495d4b6eU, 0x43872e97U, 0x23a228bcU, 0x33cc39ceU, 0x41ca46c2U, 0x43bc36c1U, 0x31a53d9dU, 0x4d984fabU, 0x51b959c0U, 0x65c06ebaU, 0x71af71a3U, 0x71977697U, 0x7c9a89a2U, 0x92a898b3U, 0x9cbe9dc4U, 0x95ce95d3U, 0x9cd6a4ccU, 0xa5baa1aaU, 0x999d9094U, 0x888b8181U, 0x7e7a7a6fU, 0x7551733fU, 0x77317a1fU, 0x7c0d00d9U,
0x650d6016U, 0x58285118U, 0x4f0d360dU, 0x35233b3eU, 0x4d634c6eU, 0x4283308eU, 0x25972ebcU, 0x39c43fc3U, 0x47bd48b8U, 0x45b238b7U, 0x339b4293U, 0x4c954fabU, 0x51b959c0U, 0x65c06ebaU, 0x71af71a5U, 0x729a749aU, 0x7a9e81a4U, 0x8aac90b5U, 0x92bf96c8U, 0x95d496d9U, 0x9ed99fccU, 0x9dba97aeU, 0x909d8a96U, 0x888b847fU, 0x80767d6dU, 0x7750753fU, 0x77317b1fU, 0x7c0d00d9U,
0x630d6019U, 0x59285119U, 0x4c0d360dU, 0x36243e3dU, 0x4d5e4c6cU, 0x45793183U, 0x26892eb0U, 0x39bb3fbcU, 0x46b948b6U, 0x45b138b1U, 0x348f408cU, 0x4a934ca5U, 0x51b45cbaU, 0x65ba6db6U, 0x73ab73a3U, 0x7298759aU, 0x7a9e81a4U, 0x86ae8ab9U, 0x8bc28ecaU, 0x8ed48ed9U, 0x98d998ceU, 0x96c092b4U, 0x8d9f8a96U, 0x888b867fU, 0x84758067U, 0x7a557644U, 0x77317b1fU, 0x7c0d00d9U,
0x640d601aU, 0x5a275119U, 0x4b0d340dU, 0x3723413cU, 0x4f595166U, 0x4b6f2f7bU, 0x27812ea6U, 0x3ab440b6U, 0x46b648b3U, 0x44ae38a9U, 0x35863f85U, 0x49914ca2U, 0x53b05db5U, 0x65b56cb1U, 0x73a974a2U, 0x7399769bU, 0x7b9d7fa5U, 0x81af84bcU, 0x85c487cbU, 0x89d489d9U, 0x93d993d0U, 0x91c38eb7U, 0x8ba18998U, 0x888b877eU, 0x86748365U, 0x7e577746U, 0x77327b1fU, 0x7e0d00d9U,
0x670d611aU, 0x5c255119U, 0x4b0d320dU, 0x3720443cU, 0x53535b5eU, 0x54662b76U, 0x277d309fU, 0x3bae42b2U, 0x48b249b0U, 0x42a838a1U, 0x3580417eU, 0x489050a1U, 0x55ac5cafU, 0x64af6aadU, 0x70a873a2U, 0x759c779cU, 0x7b9d7ca6U, 0x7daf80bdU, 0x81c483ccU, 0x85d486d9U, 0x91d990d2U, 0x8dc58cb8U, 0x89a3889aU, 0x888b877eU, 0x86748665U, 0x82577945U, 0x78327c1fU, 0x820d00d9U);


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    fragCoord = floor(fragCoord);
    float frame = (fragCoord.y + float(iFrame)) / 8.;
    frame = (sin(frame) + 1.) * 3.5;
    int vtxIdx = int(fragCoord.x);
    if( vtxIdx >= Cstride)
    {
        discard;
    }
    uint cv0 = vertices[vtxIdx + (int(floor(frame + 0.)) % CnbFrames) * Cstride];
    vec4 v0 = vec4(vec2(cv0>>24, (cv0>>16)&255U),vec2((cv0>>8)&255U, (cv0)&255U));
    uint cv1 = vertices[vtxIdx + (int(floor(frame + 1.)) % CnbFrames) * Cstride];
    vec4 v1 = vec4(vec2(cv1>>24, (cv1>>16)&255U),vec2((cv1>>8)&255U, (cv1)&255U));
    vec4 v = mix(v0, v1, fract(frame));
    //vec4 v = v0;
    fragColor = v;
}

// ---------------------------------------------------------------------------
// Image
// ---------------------------------------------------------------------------

float dot2( in vec2 v ) { return dot(v,v); }
float cross2d( in vec2 v0, in vec2 v1) { return v0.x*v1.y - v0.y*v1.x; }


vec4 Load(in int vtxIdx, in int frame, in sampler2D s)
{
	return texelFetch(s, ivec2(vtxIdx, frame), 0);
}

// By IQ https://www.shadertoy.com/view/wdBXRW
float sdPoly( in vec2[maxVert] v, in vec2 p, in int num )
{
    float d = dot(p-v[0],p-v[0]);
    float s = 1.0;
    for( int i=0, j=num-1; i<num; j=i, i++ )
    {
        // distance
        vec2 e = v[j] - v[i];
        vec2 w =    p - v[i];
        vec2 b = w - e*clamp( dot(w,e)/dot(e,e), 0.0, 1.0 );
        d = min( d, dot(b,b) );

        // winding number from http://geomalgorithms.com/a03-_inclusion.html
        bvec3 cond = bvec3( p.y>=v[i].y, p.y<v[j].y, e.x*w.y>e.y*w.x );
        if( all(cond) || all(not(cond)) ) s*=-1.0;
    }

    return s*sqrt(d);
}

vec4 sdPoly(in vec2 p, in int frame, in sampler2D s, in int nbPt, in int stride)
{
    vec4 o;
    for(int j = 0; j < 4; j++)
    {
	    vec2[maxVert] v;
        for(int i = 0; i < stride; i++)
        {
            vec4 lv = Load(i, (3 - j) * 3, s);
            v[i*2 + 0] = (lv.xy - 127.) / 95. + vec2(0,0.1);
            v[i*2 + 1] = (lv.zw - 127.) / 95. + vec2(0,0.1);
        }
        o[j] = sdPoly(v, p, nbPt);
    }
    return o;
}

float distFilter(float v)
{
    return smoothstep(3. / iResolution.y, 0., v);
}

float triangleSignal(float x, float f)
{
    f = 1. / f;
    return (abs((f * x - 4. * floor(0.25 * f * x)) - 2.) - 1.) / f;
}

vec3 circle(in vec2 p, in float tp, in float tc)
{
    float v0 = distFilter(triangleSignal(length(p - vec2(sin(tp * 0.5 + 1.2), sin(tp * 0.7 + 3.2))), 0.01));
    float v1 = distFilter(triangleSignal(length(p - vec2(sin(tp * 0.6 + 0.3), sin(tp * 0.83 + 2.7))), 0.01));
    vec3 cb = vec3(sin(tc * 0.41 + 1.3),sin(tc * 0.52 + 2.4), sin(tc * 0.57 + 1.25)) / 2. + 0.5;
    vec3 c0 = vec3(sin(tc * 0.37 + 2.7),sin(tc * 0.39 + 3.9), sin(tc * 0.29 + 5.36)) / 2. + 0.5;;
    vec3 c1 = vec3(sin(tc * 0.39 + 1.6),sin(tc * 0.43 + 4.5), sin(tc * 0.47 + 6.23)) / 2. + 0.5;;
    return mix(mix(cb, c0, v0), c1, v1);
}

vec3 noisyCircle(in vec2 p, in float t)
{
    float h = hash13(vec3(floor(p * 100.),floor(t * 10.)));
    vec3 cb = vec3(sin(t * 0.28 + 5.3),sin(t * 0.48 + 2.4), sin(t * 0.43 + 2.25)) / 2. + 0.5;
    vec3 c0 = vec3(sin(t * 0.31 + 2.7),sin(t * 0.58 + 3.9), sin(t * 0.47 + 4.36)) / 2. + 0.5;
    float v = distFilter(triangleSignal(length(p) - iTime, 0.1) - 0.05);
    return vec3(h * v > 0.5?  cb : c0);
}

float seqLength = 2.f;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2	p = (2. * fragCoord - iResolution.xy) / iResolution.y;
    float	seqId = floor(iTime / seqLength);
    int		select;

    // Select Shape
    select = int(hash12(vec2(seqId, 0.)) * 3.);
    vec4 shapeDist;
    switch (select)
    {
        case 0:
            shapeDist = sdPoly(p, iFrame % 13, iChannel1, AnbVertices, Astride);
            break;
        case 1:
            shapeDist = sdPoly(p, iFrame % 13, iChannel2, BnbVertices, Bstride);
            break;
        case 2:
            shapeDist = sdPoly(p, iFrame % 13, iChannel3, CnbVertices, Cstride);
            break;
    }
    // select Shape Effect
    float shapeMask;
    select = int(hash12(vec2(seqId, 1.)) * 3.);
    switch (select)
    {
        case 0:
            shapeMask = distFilter(shapeDist.x);
            break;
        case 1:
            shapeMask = distFilter(abs(shapeDist.x) - 0.01);
            break;
        case 2:
            shapeMask = max(distFilter(shapeDist.x), max(distFilter(shapeDist.y) * 0.75, max(distFilter(shapeDist.z) * 0.50, distFilter(shapeDist.w) * 0.25)));
            break;
    }
    // Select backgroud
    vec3 backCol;
    select = int(hash12(vec2(seqId, 2.)) * 3.);
    switch (select)
    {
        case 0:
            backCol = circle(p, iTime, iTime);
            break;
        case 1:
            backCol = 0.5 + 0.5*cos(iTime + p.xyx + vec3(0,2,4));
            break;
        case 2:
            backCol = noisyCircle(p, iTime);
            break;
    }
    // Select foreground
    vec3 foreCol;
    select = int(hash12(vec2(seqId, 3.)) * 3.);
    switch (select)
    {
        case 0:
            foreCol = vec3(0);
            break;
        case 1:
            foreCol = vec3(1);
            break;
        case 2:
            foreCol = circle(p, iTime, iTime + 22.3);
            break;
    }

    vec3 col = mix(backCol, foreCol, shapeMask);
	fragColor = vec4(col,1.0);
}
)"
            },
            */

            // ---------------------------------------------------------------------------

            {
                "The Drive Home",

                R"(
out vec4 outColor;

// "The Drive Home" by Martijn Steinrucken aka BigWings - 2017
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// Email:countfrolic@gmail.com Twitter:@The_ArtOfCode
//
// I was looking for something 3d, that can be made just with a point-line distance function.
// Then I saw the cover graphic of the song I'm using here on soundcloud, which is a bokeh traffic
// shot which is a perfect for for what I was looking for.
//
// It took me a while to get to a satisfying rain effect. Most other people use a render buffer for
// this so that is how I started. In the end though, I got a better effect without. Uncomment the
// DROP_DEBUG define to get a better idea of what is going on.
//
// If you are watching this on a weaker device, you can uncomment the HIGH_QUALITY define
//
// Music:
// Mr. Bill - Cheyah (Zefora's digital rain remix)
// https://soundcloud.com/zefora/cheyah
//
// Video can be found here:
// https://www.youtube.com/watch?v=WrxZ4AZPdOQ
//
// Making of tutorial:
// https://www.youtube.com/watch?v=eKtsY7hYTPg
//


#define S(x, y, z) smoothstep(x, y, z)
#define B(a, b, edge, t) S(a-edge, a+edge, t)*S(b+edge, b-edge, t)
#define sat(x) clamp(x,0.,1.)

#define streetLightCol vec3(1., .7, .3)
#define headLightCol vec3(.8, .8, 1.)
#define tailLightCol vec3(1., .1, .1)

#define HIGH_QUALITY
#define CAM_SHAKE 1.
#define LANE_BIAS .5
#define RAIN
//#define DROP_DEBUG

vec3 ro, rd;

float N(float t) {
	return fract(sin(t*10234.324)*123423.23512);
}
vec3 N31(float p) {
    //  3 out, 1 in... DAVE HOSKINS
   vec3 p3 = fract(vec3(p) * vec3(.1031,.11369,.13787));
   p3 += dot(p3, p3.yzx + 19.19);
   return fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}
float N2(vec2 p)
{	// Dave Hoskins - https://www.shadertoy.com/view/4djSRW
	vec3 p3  = fract(vec3(p.xyx) * vec3(443.897, 441.423, 437.195));
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}


float DistLine(vec3 ro, vec3 rd, vec3 p) {
	return length(cross(p-ro, rd));
}

vec3 ClosestPoint(vec3 ro, vec3 rd, vec3 p) {
    // returns the closest point on ray r to point p
    return ro + max(0., dot(p-ro, rd))*rd;
}

float Remap(float a, float b, float c, float d, float t) {
	return ((t-a)/(b-a))*(d-c)+c;
}

float BokehMask(vec3 ro, vec3 rd, vec3 p, float size, float blur) {
	float d = DistLine(ro, rd, p);
    float m = S(size, size*(1.-blur), d);

    #ifdef HIGH_QUALITY
    m *= mix(0.7, 1., S(.8*size, size, d));
    #endif

    return m;
}



float SawTooth(float t) {
    return cos(t+cos(t))+sin(2.*t)*.2+sin(4.*t)*.02;
}

float DeltaSawTooth(float t) {
    return 0.4*cos(2.*t)+0.08*cos(4.*t) - (1.-sin(t))*sin(t+cos(t));
}

vec2 GetDrops(vec2 uv, float seed, float m) {

    float t = iTime+m*30.;
    vec2 o = vec2(0.);

    #ifndef DROP_DEBUG
    uv.y += t*.05;
    #endif

    uv *= vec2(10., 2.5)*2.;
    vec2 id = floor(uv);
    vec3 n = N31(id.x + (id.y+seed)*546.3524);
    vec2 bd = fract(uv);

    vec2 uv2 = bd;

    bd -= .5;

    bd.y*=4.;

    bd.x += (n.x-.5)*.6;

    t += n.z * 6.28;
    float slide = SawTooth(t);

    float ts = 1.5;
    vec2 trailPos = vec2(bd.x*ts, (fract(bd.y*ts*2.-t*2.)-.5)*.5);

    bd.y += slide*2.;								// make drops slide down

    #ifdef HIGH_QUALITY
    float dropShape = bd.x*bd.x;
    dropShape *= DeltaSawTooth(t);
    bd.y += dropShape;								// change shape of drop when it is falling
    #endif

    float d = length(bd);							// distance to main drop

    float trailMask = S(-.2, .2, bd.y);				// mask out drops that are below the main
    trailMask *= bd.y;								// fade dropsize
    float td = length(trailPos*max(.5, trailMask));	// distance to trail drops

    float mainDrop = S(.2, .1, d);
    float dropTrail = S(.1, .02, td);

    dropTrail *= trailMask;
    o = mix(bd*mainDrop, trailPos, dropTrail);		// mix main drop and drop trail

    #ifdef DROP_DEBUG
    if(uv2.x<.02 || uv2.y<.01) o = vec2(1.);
    #endif

    return o;
}

void CameraSetup(vec2 uv, vec3 pos, vec3 lookat, float zoom, float m) {
	ro = pos;
    vec3 f = normalize(lookat-ro);
    vec3 r = cross(vec3(0., 1., 0.), f);
    vec3 u = cross(f, r);
    float t = iTime;

    vec2 offs = vec2(0.);
    #ifdef RAIN
    vec2 dropUv = uv;

    #ifdef HIGH_QUALITY
    float x = (sin(t*.1)*.5+.5)*.5;
    x = -x*x;
    float s = sin(x);
    float c = cos(x);

    mat2 rot = mat2(c, -s, s, c);

    #ifndef DROP_DEBUG
    dropUv = uv*rot;
    dropUv.x += -sin(t*.1)*.5;
    #endif
    #endif

    offs = GetDrops(dropUv, 1., m);

    #ifndef DROP_DEBUG
    offs += GetDrops(dropUv*1.4, 10., m);
    #ifdef HIGH_QUALITY
    offs += GetDrops(dropUv*2.4, 25., m);
    //offs += GetDrops(dropUv*3.4, 11.);
    //offs += GetDrops(dropUv*3., 2.);
    #endif

    float ripple = sin(t+uv.y*3.1415*30.+uv.x*124.)*.5+.5;
    ripple *= .005;
    offs += vec2(ripple*ripple, ripple);
    #endif
    #endif
    vec3 center = ro + f*zoom;
    vec3 i = center + (uv.x-offs.x)*r + (uv.y-offs.y)*u;

    rd = normalize(i-ro);
}

vec3 HeadLights(float i, float t) {
    float z = fract(-t*2.+i);
    vec3 p = vec3(-.3, .1, z*40.);
    float d = length(p-ro);

    float size = mix(.03, .05, S(.02, .07, z))*d;
    float m = 0.;
    float blur = .1;
    m += BokehMask(ro, rd, p-vec3(.08, 0., 0.), size, blur);
    m += BokehMask(ro, rd, p+vec3(.08, 0., 0.), size, blur);

    #ifdef HIGH_QUALITY
    m += BokehMask(ro, rd, p+vec3(.1, 0., 0.), size, blur);
    m += BokehMask(ro, rd, p-vec3(.1, 0., 0.), size, blur);
    #endif

    float distFade = max(.01, pow(1.-z, 9.));

    blur = .8;
    size *= 2.5;
    float r = 0.;
    r += BokehMask(ro, rd, p+vec3(-.09, -.2, 0.), size, blur);
    r += BokehMask(ro, rd, p+vec3(.09, -.2, 0.), size, blur);
    r *= distFade*distFade;

    return headLightCol*(m+r)*distFade;
}


vec3 TailLights(float i, float t) {
    t = t*1.5+i;

    float id = floor(t)+i;
    vec3 n = N31(id);

    float laneId = S(LANE_BIAS, LANE_BIAS+.01, n.y);

    float ft = fract(t);

    float z = 3.-ft*3.;						// distance ahead

    laneId *= S(.2, 1.5, z);				// get out of the way!
    float lane = mix(.6, .3, laneId);
    vec3 p = vec3(lane, .1, z);
    float d = length(p-ro);

    float size = .05*d;
    float blur = .1;
    float m = BokehMask(ro, rd, p-vec3(.08, 0., 0.), size, blur) +
    			BokehMask(ro, rd, p+vec3(.08, 0., 0.), size, blur);

    #ifdef HIGH_QUALITY
    float bs = n.z*3.;						// start braking at random distance
    float brake = S(bs, bs+.01, z);
    brake *= S(bs+.01, bs, z-.5*n.y);		// n.y = random brake duration

    m += (BokehMask(ro, rd, p+vec3(.1, 0., 0.), size, blur) +
    	BokehMask(ro, rd, p-vec3(.1, 0., 0.), size, blur))*brake;
    #endif

    float refSize = size*2.5;
    m += BokehMask(ro, rd, p+vec3(-.09, -.2, 0.), refSize, .8);
    m += BokehMask(ro, rd, p+vec3(.09, -.2, 0.), refSize, .8);
    vec3 col = tailLightCol*m*ft;

    float b = BokehMask(ro, rd, p+vec3(.12, 0., 0.), size, blur);
    b += BokehMask(ro, rd, p+vec3(.12, -.2, 0.), refSize, .8)*.2;

    vec3 blinker = vec3(1., .7, .2);
    blinker *= S(1.5, 1.4, z)*S(.2, .3, z);
    blinker *= sat(sin(t*200.)*100.);
    blinker *= laneId;
    col += blinker*b;

    return col;
}

vec3 StreetLights(float i, float t) {
	 float side = sign(rd.x);
    float offset = max(side, 0.)*(1./16.);
    float z = fract(i-t+offset);
    vec3 p = vec3(2.*side, 2., z*60.);
    float d = length(p-ro);
	float blur = .1;
    vec3 rp = ClosestPoint(ro, rd, p);
    float distFade = Remap(1., .7, .1, 1.5, 1.-pow(1.-z,6.));
    distFade *= (1.-z);
    float m = BokehMask(ro, rd, p, .05*d, blur)*distFade;

    return m*streetLightCol;
}

vec3 EnvironmentLights(float i, float t) {
	float n = N(i+floor(t));

    float side = sign(rd.x);
    float offset = max(side, 0.)*(1./16.);
    float z = fract(i-t+offset+fract(n*234.));
    float n2 = fract(n*100.);
    vec3 p = vec3((3.+n)*side, n2*n2*n2*1., z*60.);
    float d = length(p-ro);
	float blur = .1;
    vec3 rp = ClosestPoint(ro, rd, p);
    float distFade = Remap(1., .7, .1, 1.5, 1.-pow(1.-z,6.));
    float m = BokehMask(ro, rd, p, .05*d, blur);
    m *= distFade*distFade*.5;

    m *= 1.-pow(sin(z*6.28*20.*n)*.5+.5, 20.);
    vec3 randomCol = vec3(fract(n*-34.5), fract(n*4572.), fract(n*1264.));
    vec3 col = mix(tailLightCol, streetLightCol, fract(n*-65.42));
    col = mix(col, randomCol, n);
    return m*col*.2;
}



void main( void ) {
	float t = iTime;
    vec3 col = vec3(0.);
    vec2 uv = gl_FragCoord.xy / iResolution.xy; // 0 <> 1

    uv -= .5;
    uv.x *= iResolution.x/iResolution.y;

    vec3 pos = vec3(.3, .15, 0.);

    float bt = t * 5.;
    float h1 = N(floor(bt));
    float h2 = N(floor(bt+1.));
    float bumps = mix(h1, h2, fract(bt))*.1;
    bumps = bumps*bumps*bumps*CAM_SHAKE;

    pos.y += bumps;
    float lookatY = pos.y+bumps;
    vec3 lookat = vec3(0.3, lookatY, 1.);
    vec3 lookat2 = vec3(0., lookatY, .7);
    lookat = mix(lookat, lookat2, sin(t*.1)*.5+.5);

    uv.y += bumps*4.;
    CameraSetup(uv, pos, lookat, 2., 0);

    t *= .03;
    //t += mouse.x;

    const float stp = 1./8.;


    for(float i=0.0; i<1.0; i+=stp) {
       col += StreetLights(i, t);
    }

    for(float i=0.0; i<1.0; i+=stp) {
        float n = N(i+floor(t));
    	col += HeadLights(i+n*stp*.7, t);
    }

    for(float i=0.0; i<1.0; i+=stp) {
       col += EnvironmentLights(i, t);
    }

    col += TailLights(0., t);
    col += TailLights(.5, t);

    col += sat(rd.y)*vec3(.6, .5, .9);

    outColor = vec4(col, 1.);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "another synthwave sunset thing",  //https://www.shadertoy.com/view/tsScRK

                R"(
//#define AA 2
//#define VAPORWAVE
//#define stereo 1. // -1. for cross-eyed (defaults to parallel view)
#define speed 10.
#define wave_thing
//#define city

//you can add any sound texture in iChannel0 to turn it into a cool audio visualizer
// (it looks better with lower speeds though)
//you should commment out or remove the following line to enable it (it's disabled mainly for performance reasons):
#define disable_sound_texture_sampling

#ifndef disable_sound_texture_sampling
    #undef speed
    // lower value of speed when using as audio visualizer
    #define speed 5.
#endif

//self-explainatory
#define audio_vibration_amplitude .125

float jTime;


#ifdef disable_sound_texture_sampling
#define textureMirror(a, b) vec4(0)
#else
vec4 textureMirror(sampler2D tex, vec2 c){
    vec2 cf = fract(c);
    return texture(tex,mix(cf,1.-cf,mod(floor(c),2.)));
}
#endif


float amp(vec2 p){
    return smoothstep(1.,8.,abs(p.x));
}

float pow512(float a){
    a*=a;//^2
    a*=a;//^4
    a*=a;//^8
    a*=a;//^16
    a*=a;//^32
    a*=a;//^64
    a*=a;//^128
    a*=a;//^256
    return a*a;
}
float pow1d5(float a){
    return a*sqrt(a);
}
float hash21(vec2 co){
    return fract(sin(dot(co.xy,vec2(1.9898,7.233)))*45758.5433);
}
float hash(vec2 uv){
    float a = amp(uv);
    #ifdef wave_thing
    float w = a>0.?(1.-.4*pow512(.51+.49*sin((.02*(uv.y+.5*uv.x)-jTime)*2.))):0.;
    #else
    float w=1.;
    #endif
    return (a>0.?
        a*pow1d5(
        //texture(iChannel0,uv/iChannelResolution[0].xy).r
        hash21(uv)
        )*w
        :0.)-(textureMirror(iChannel0,vec2((uv.x*29.+uv.y)*.03125,1.)).x)*audio_vibration_amplitude;
}

float edgeMin(float dx,vec2 da, vec2 db,vec2 uv){
    uv.x+=5.;
    vec3 c = fract((round(vec3(uv,uv.x+uv.y)))*(vec3(0,1,2)+0.61803398875));
    float a1 = textureMirror(iChannel0,vec2(c.y,0.)).x>.6?.15:1.;
    float a2 = textureMirror(iChannel0,vec2(c.x,0.)).x>.6?.15:1.;
    float a3 = textureMirror(iChannel0,vec2(c.z,0.)).x>.6?.15:1.;

    return min(min((1.-dx)*db.y*a3,da.x*a2),da.y*a1);
}

vec2 trinoise(vec2 uv){
    const float sq = sqrt(3./2.);
    uv.x *= sq;
    uv.y -= .5*uv.x;
    vec2 d = fract(uv);
    uv -= d;

    bool c = dot(d,vec2(1))>1.;

    vec2 dd = 1.-d;
    vec2 da = c?dd:d,db = c?d:dd;

    float nn = hash(uv+float(c));
    float n2 = hash(uv+vec2(1,0));
    float n3 = hash(uv+vec2(0,1));


    float nmid = mix(n2,n3,d.y);
    float ns = mix(nn,c?n2:n3,da.y);
    float dx = da.x/db.y;
    return vec2(mix(ns,nmid,dx),edgeMin(dx,da, db,uv+d));
}


vec2 map(vec3 p){
    vec2 n = trinoise(p.xz);
    return vec2(p.y-2.*n.x,n.y);
}

vec3 grad(vec3 p){
    const vec2 e = vec2(.005,0);
    float a =map(p).x;
    return vec3(map(p+e.xyy).x-a
                ,map(p+e.yxy).x-a
                ,map(p+e.yyx).x-a)/e.x;
}

vec2 intersect(vec3 ro,vec3 rd){
    float d =0.,h=0.;
    for(int i = 0;i<500;i++){ //look nice with 50 iterations
        vec3 p = ro+d*rd;
        vec2 s = map(p);
        h = s.x;
        d+= h*.5;
        if(abs(h)<.003*d)
            return vec2(d,s.y);
        if(d>150.|| p.y>2.) break;
    }

    return vec2(-1);
}


void addsun(vec3 rd,vec3 ld,inout vec3 col){

	float sun = smoothstep(.21,.2,distance(rd,ld));

    if(sun>0.){
        float yd = (rd.y-ld.y);

        float a =sin(3.1*exp(-(yd)*14.));

        sun*=smoothstep(-.8,0.,a);

        col = mix(col,vec3(1.,.8,.4)*.75,sun);
    }
}


float starnoise(vec3 rd){
    float c = 0.;
    vec3 p = normalize(rd)*300.;
	for (float i=0.;i<4.;i++)
    {
        vec3 q = fract(p)-.5;
        vec3 id = floor(p);
        float c2 = smoothstep(.5,0.,length(q));
        c2 *= step(hash21(id.xz/id.y),.06-i*i*0.005);
        c += c2;
        p = p*.6+.5*p*mat3(3./5.,0,4./5.,0,1,0,-4./5.,0,3./5.);
    }
    c*=c;
    float g = dot(sin(rd*10.512),cos(rd.yzx*10.512));
    c*=smoothstep(-3.14,-.9,g)*.5+.5*smoothstep(-.3,1.,g);
    return c*c;
}

vec3 gsky(vec3 rd,vec3 ld,bool mask){
    float haze = exp2(-5.*(abs(rd.y)-.2*dot(rd,ld)));


    //float st = mask?pow512(texture(iChannel0,(rd.xy+vec2(300.1,100)*rd.z)*10.).r)*(1.-min(haze,1.)):0.;
    //float st = mask?pow512(hash21((rd.xy+vec2(300.1,100)*rd.z)*10.))*(1.-min(haze,1.)):0.;
    float st = mask?(starnoise(rd))*(1.-min(haze,1.)):0.;
    vec3 back = vec3(.4,.1,.7)*(1.-.5*textureMirror(iChannel0,vec2(.5+.05*rd.x/rd.y,0.)).x
    *exp2(-.1*abs(length(rd.xz)/rd.y))
    *max(sign(rd.y),0.));
    #ifdef city
    float x = round(rd.x*30.);
    float h = hash21(vec2(x-166.));
    bool building = (h*h*.125*exp2(-x*x*x*x*.0025)>rd.y);
    if(mask && building)
        back*=0.,haze=.8, mask=mask && !building;
    #endif
    vec3 col=clamp(mix(back,vec3(.7,.1,.4),haze)+st,0.,1.);
    if(mask)addsun(rd,ld,col);
    return col;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    fragColor=vec4(0);
    #ifdef AA
    for(float x = 0.;x<1.;x+=1./float(AA)){
    for(float y = 0.;y<1.;y+=1./float(AA)){
    #else
        const float AA=1.,x=0.,y=0.;
    #endif
    vec2 uv = (2.*(fragCoord+vec2(x,y))-iResolution.xy)/iResolution.y;

    const float shutter_speed = .25; // for motion blur
	//float dt = fract(texture(iChannel0,float(AA)*(fragCoord+vec2(x,y))/iChannelResolution[0].xy).r+iTime)*shutter_speed;
    float dt = fract(hash21(float(AA)*(fragCoord+vec2(x,y)))+iTime)*shutter_speed;
    jTime = mod(iTime-dt*iTimeDelta,4000.);
    vec3 ro = vec3(0.,1,(-20000.+jTime*speed));

        #ifdef stereo
            ro+=stereo*vec3(.2*(float(uv.x>0.)-.5),0.,0.);
            const float de = .9;
            uv.x=uv.x+.5*(uv.x>0.?-de:de);
            uv*=2.;
		#endif

    vec3 rd = normalize(vec3(uv,4./3.));//vec3(uv,sqrt(1.-dot(uv,uv)));

    vec2 i = intersect(ro,rd);
    float d = i.x;

    vec3 ld = normalize(vec3(0,.125+.05*sin(.1*jTime),1));

    vec3 fog = d>0.?exp2(-d*vec3(.14,.1,.28)):vec3(0.);
    vec3 sky = gsky(rd,ld,d<0.);

    vec3 p = ro+d*rd;
    vec3 n = normalize(grad(p));

    float diff = dot(n,ld)+.1*n.y;
    vec3 col = vec3(.1,.11,.18)*diff;

    vec3 rfd = reflect(rd,n);
    vec3 rfcol = gsky(rfd,ld,true);

    col = mix(col,rfcol,.05+.95*pow(max(1.+dot(rd,n),0.),5.));
    #ifdef VAPORWAVE
    col = mix(col,vec3(.4,.5,1.),smoothstep(.05,.0,i.y));
    col = mix(sky,col,fog);
    col = sqrt(col);
    #else
    col = mix(col,vec3(.8,.1,.92),smoothstep(.05,.0,i.y));
    col = mix(sky,col,fog);
    //no gamma for that old cg look
    #endif
    if(d<0.)
        d=1e6;
    d=min(d,10.);
    fragColor += vec4(clamp(col,0.,1.),d<0.?0.:.1+exp2(-d));
     #ifdef AA
    }
    }
    fragColor/=float(AA*AA);
    #endif
}

/** SHADERDATA
{
	"title": "another synthwave sunset thing",
	"description": "I was thinking of a way to make pseudo tesselation noise and i made this to illustrate it, i might not be the first one to come up with this solution.",
	"model": "car"
}
*/
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Synthwave (atz)",  // https://www.shadertoy.com/view/tsfyzn

                R"(
// credits to @spalmer for grid smooth function https://www.shadertoy.com/view/wl3Sz2
#define MAX_STEPS 156
#define MIN_DISTANCE 0.01
#define MAX_DISTANCE 16.
#define GRID_SIZE 4.
#define speed 6.
#define MOUNTAIN_COLOR vec3(0.54, 0.11, 1.)
#define COLOR_PURPLE vec3(0.81, 0.19, 0.78)
#define COLOR_LIGHT vec3(0.14, 0.91, 0.98)
#define COLOR_SUN vec3(1., 0.56, 0.098)
#define MATERIAL_PLANE 1.
#define MATERIAL_BACK 2.
#define GRID_THICKNESS .2
#define COLOR_NIGHT_GRID vec3(0., .15, 0.)
#define COLOR_NIGHT_SUN vec3(0.5, .0, 0.)
#define COLOR_NIGHT_MOUNTAIN vec3(0.9, .3, 0.1)
#define SUNSET_SPEED 3.

vec3 lightPos = vec3(0., 3., -10.);

struct traceResult {
    bool  isHit;
    float distanceTo;
    float material;
    float planeHeight;
    vec3 planeNormal;
};

struct getDistResult {
    float distanceTo;
    float material;
    float planeHeight;
    vec3 planeNormal;
};

float sdPlane(vec3 p, float h) {
    return p.y - h;
}

float N21(vec2 p) {
    return fract(sin(p.x*223.32+p.y*5677.)*4332.23);
}

mat2 rot2d(float a) {
    float c = cos(a);
    float s = sin(a);
    return mat2(vec2(c,-s), vec2(s,c));
}

float getHeight(vec2 id) {
    //return 0.;
    float ax = abs(id.x);
    if (ax < GRID_SIZE) {
        return 0.;
    }

    float n = N21(id);

    float wave = sin(id.y/9. + cos(id.x/3.))*sin(id.x/9. + sin(id.y/4.));

    wave = clamp((wave * .5 + .5) + n*.15 - .6, 0., 1.);
    if (ax < (GRID_SIZE + 5.) && ax >= GRID_SIZE) {
        wave *= (ax - GRID_SIZE + 1.)*.2;
    }
    return (wave*10.);
}


getDistResult getDist(vec3 p) {
    float size = GRID_SIZE;
    vec3 nuv = p * size + vec3(0., 0., iTime * speed);
    vec2 uv = fract(nuv).xz;
    vec2 id = floor(nuv).xz;

    vec2 lv = uv;

    float bl = getHeight(id);
    float br = getHeight(id + vec2(1., 0.));
    float b = mix(bl, br, lv.x);

    float tl = getHeight(id + vec2(0., 1.));
    float tr = getHeight(id + vec2(1., 1.));
    float t = mix(tl, tr, lv.x);

    float height = mix(b,t, lv.y);

    float O = bl;
    float R = br;
    float T = getHeight(id + vec2(0. -1.));
    float B = tl;
    float L = getHeight(id + vec2(-1., 0));

    vec3 n = vec3(2.*(R-L), 2.*(B-T), -4.);


    float d = sdPlane(p, -.5 + 0.3*height);

    float db = -p.z + MAX_DISTANCE*.4;
    d = min(d, db);

    getDistResult result;

    result.distanceTo = d;
    result.material = MATERIAL_PLANE;
    result.planeHeight = height;
    result.planeNormal = normalize(n);

    if (d == db) {
        result.material = MATERIAL_BACK;
    }

    return result;
}

traceResult trace(vec3 ro, vec3 rd) {
    traceResult result;
    float ds, dt;
    getDistResult dist;
    for(int i = 0 ; i < MAX_STEPS ; i++) {
        vec3 p = ro + rd * ds;
        dist = getDist(p);
        dt = dist.distanceTo;
        ds += dt * .6;
        if (abs(dt) < MIN_DISTANCE || ds > MAX_DISTANCE) {
            break;
        }
    }
    result.isHit = abs(dt) < MIN_DISTANCE;
    result.distanceTo = ds;
    result.material = dist.material;
    result.planeHeight = dist.planeHeight;
    result.planeNormal = dist.planeNormal;
    return result;
}

float getLightDiffuse(vec3 p, float material, float height, vec3 normal) {
    vec3 l = normalize(lightPos - p);
    float dif = clamp(dot(normal, l), 0., 1.);
    return dif;
}

vec3 starsLayer(vec2 ouv) {
    vec3 col = vec3(0.);

    vec2 uv = fract(ouv) - .5;

    float d;

    for(int x = -1 ; x <= 1; x++) {
        for(int y = -1 ; y <= 1; y++) {
            vec2 offset = vec2(x,y);
            vec2 id = floor(ouv) + offset;
            float n = N21(id);
            if (n > .6) {
                float n1 = fract(n*123.432);
                float n2 = fract(n*1234.2432);

                float size = .01 + 0.05 * (n1 - .5);

                vec2 shift = vec2(n1 - .5, n2 - .5);
                d = max(d, size/length(uv - offset + shift));
            }
        }
    }


    return col + d*vec3(.1, .9, .1);
}

vec3 backgroundStars(vec2 uv) {
    vec3 col = vec3(0.);

    float t = iTime * (speed / 30.);

    float layers = 3.;

    for(float i = 0. ; i < 1. ; i+= 1./layers) {
        float depth = fract(i + t);
        float scale = mix(20., .5, depth);
        float fade = depth * smoothstep(1., .9, depth);

        col += starsLayer(uv * scale + i * 456.32) * fade;
    }
    return col;
}

vec3 getOthersideBackground(vec2 uv) {
    return backgroundStars(uv/8. + sin(iTime/(speed)));
}

vec3 getBackground(vec2 uv) {
    float set = 0. - clamp(sin(iTime/SUNSET_SPEED)*3., -1., 2.);

    float sunDist = length(uv + vec2(0., -2.5 - set));
    float sun = 1. - smoothstep(2.35, 2.5, sunDist);

    float gradient = sin(uv.y/4. - 3.14/32. + set/3.)*2.;
    float bands = abs(sin(uv.y * 8. + iTime*2.)) * (1. - step(2.5 + set, uv.y));

    float skyTop = 2.12/distance(uv, vec2(uv.x, 9.5));
    float skyBottom = 1.12/distance(uv, vec2(uv.x, -1.5));

    vec3 result;

    // sun

    if (set < -1.8) {
        result = vec3(sun) * (bands > 0. ? bands : 1.) * mix(vec3(0.), COLOR_NIGHT_SUN, ((abs(set) - 1.6) -.2) * 15.);
        float glow = smoothstep(.1, .5, (1.1)/sunDist);
        result += glow * COLOR_NIGHT_SUN;
    } else {
        result = vec3(sun * gradient * (bands > 0. ? bands : 1.)) * COLOR_SUN;
        //glow
        float glow = smoothstep(.1, .5, (1.1)/sunDist) + clamp(-1., 1., set);
        // result += glow * COLOR_PURPLE;

        // sky
        result += max(glow * COLOR_PURPLE, ((skyTop * MOUNTAIN_COLOR) + (skyBottom * COLOR_PURPLE))*(1. + set));
    }



    if (sun < .5) {
        // stars
        vec2 nuv = uv*2.;// + vec2(iTime, 0.);
        vec2 rize = vec2(-10., 12.);
        nuv -= rize;
        nuv *= rot2d(mod(-iTime/15., 6.28));
        nuv += rize;
        uv = fract(nuv);
        vec2 id = floor(nuv);
        uv -= .5;

        float n = N21(id);
        uv.x += fract(n*100.32) - .5;
        uv.y += fract(n*11323.432) - .5;

        float star = smoothstep(.5, 1., (0.03 + (0.02 * (fract(n*353.32) - .5)))/length(uv));

        result += star * step(.8, n);
    }

    return result;
}
float filterWidth2(vec2 uv)
{
     vec2 dx = dFdx(uv), dy = dFdy(uv);
    return dot(dx, dx) + dot(dy, dy) + .0001;
}

// (c) spalmer https://www.shadertoy.com/view/wl3Sz2
float gridPow(vec2 uv)
{
    vec2 p = uv * GRID_SIZE + vec2(0., iTime * speed);
    const float fadePower = 16.;
    vec2 f = fract(p);
    f = .5 - abs(.5 - f);
    f = max(vec2(0), 1. - f + .5*GRID_THICKNESS);
    f = pow(f, vec2(fadePower));
    float g = f.x+f.y; //max(f.x, f.y); //
    float s = sqrt(GRID_THICKNESS);
    return mix(g, s, exp2(-.01 / filterWidth2(p)));
}

vec3 getAlbedo(vec3 p, float material, float height, vec3 normal) {
    if (material == MATERIAL_BACK) {
        return getBackground(p.xy);
    }

    float sunSet = sin(iTime/SUNSET_SPEED)*.5 + .5;

    vec3 col = vec3(0.);
    float grid = gridPow(p.xz);

    float maxHeight = 2.5;

    vec3 grid_color = COLOR_PURPLE;
    vec3 cell_color = vec3(0.);
    vec3 mountain_color = MOUNTAIN_COLOR;
    mountain_color = mix(mountain_color, COLOR_NIGHT_MOUNTAIN, sunSet);



    if (height > 0.) {
        grid_color = mix(COLOR_PURPLE, COLOR_LIGHT, height/maxHeight);
        cell_color = mountain_color * mix(vec3(0.), mountain_color, height/maxHeight);
    }

    grid_color = mix(grid_color, COLOR_NIGHT_GRID, sunSet);

    col = mix(vec3(0.), grid_color, grid) + cell_color;

    return vec3(col);
}

float polarTriangle(vec2 uv, float offset) {
    float a = atan(uv.x, uv.y) + offset;
    float b = 6.28 / 3.;
    float l = length(uv);

    float d = cos(a - floor(.5 + a/b) * b) * l;

    return d;
}

float triangleMask(vec2 uv) {
    return polarTriangle(uv + vec2(0., -.1),3.14 + .5*sin(iTime));
}


void mainImage(out vec4 fragColor, in vec2 fragCoords) {
    vec2 uv = fragCoords.xy / iResolution.xy;
    uv -= .5;
    uv.x *= iResolution.x / iResolution.y;

    vec2 mouse = iMouse.xy / iResolution.xy;

    // lightPos.z = sin(iTime/3.)*100.;

    mouse.x = 0.5;
    mouse.y = 0.;

    vec3 col = vec3(0.);

    vec3 ro = vec3(0., .5, -.4);
    vec3 lookat = vec3(mouse.x*2.-1., 1. - mouse.y - .6, 0.);
    float zoom = .4;


    vec3 f = normalize(lookat - ro);
    vec3 r = normalize(cross(vec3(0., 1., 0), f));
    vec3 u = cross(f, r);
    vec3 c = ro + f * zoom;
    vec3 i = c + uv.x * r + uv.y * u;

    vec3 rd = normalize(i - ro);

    vec3 p = vec3(0.);

    traceResult tr = trace(ro, rd);

    if (tr.isHit) {

        p = ro + rd * tr.distanceTo;

        vec3 albedo = getAlbedo(p, tr.material, tr.planeHeight, tr.planeNormal);

        float diffuse = getLightDiffuse(p, tr.material, tr.planeHeight, tr.planeNormal);

        float fade = 1.;// - clamp((p.z-ro.z)/(MAX_DISTANCE * .8), 0., 1.);

        if (tr.material == MATERIAL_BACK) {
            col = albedo;
        } else {
            col = diffuse * albedo * fade;
        }

        float triangle = triangleMask(uv);
        float fd = fract(triangle - clamp(sin(iTime/3.), 0., 2.));
        float bc = (1. - step(.2, fd));

        col *= (tr.material == MATERIAL_BACK) ? bc : 1.;
        if (bc == 0.) {
            if (tr.material == MATERIAL_BACK) {
                col = getOthersideBackground(p.xy);
            } else {
                col *= vec3(.8);
            }
        }

        col += ((1. - step(.2, fd)) - (1. - step(.19, fd)))*.3;

    }


    fragColor = vec4(col, 1.);
    // fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2));
}
)"
            },

            // ---------------------------------------------------------------------------

#ifndef  ICHANNEL_IS_NOT_IMPLEMENTED
            // TODO needs iChannel

            {
                "Synthwave",

                R"(
#define TAU 6.2831853
struct M{float d;vec3 c;};M m;
void mmin(float d, vec3 c){if (d<m.d){m.d=d;m.c=c;}}

mat2 rz2(float a){float c=cos(a),s=sin(a);return mat2(c,s,-s,c);}

float amod(float a,float m){return mod(a,m)-m*.5;}

float random(float x){return fract(sin(x*13.+4375.));}

float height(vec2 iuv){
    return sin(sin(iuv.x+iTime*.1)*sin(iuv.y+iTime*.1)*5.)*(pow(abs(iuv.x),2.)*.02+0.1);
}

void map(vec3 p){
   	m.d=max(max(p.y,.0),max(p.z-6.,0.));
    vec2 uv=p.xz*2.;
    uv.y+=iTime;
    vec2 f=fract(uv)-.5;
    float fft=max(texture(iChannel0,vec2(0.01,0.25)).r*2.-1.8,0.005);
    float l=fft/(abs(f.x)*abs(f.y));
    l+=.1*fft/(abs(p.z-6.));
    m.c=mix(vec3(0.196, 0.003, 0.149),vec3(1, 0.019, 0.384),l);

    uv=p.xz-.5;
    vec2 iuv=floor(uv);
    vec2 fuv=fract(uv);
    float h=mix(
        mix(height(iuv+vec2(0.,0.)), height(iuv+vec2(1.,0.)), fuv.x),
        mix(height(iuv+vec2(0.,1.)), height(iuv+vec2(1.,1.)), fuv.x),
        fuv.y)-1.;
    float d=p.y-h;
    d=max(d,abs(p.z-10.)-4.);
    vec2 vuv=fuv*(1.-fuv);
    float v=vuv.x*vuv.y;
    l=.01*fft/v;
    mmin(d, vec3(0.,0.,1.)*l);
}

vec3 noise(vec2 uv){return texture(iChannel1,uv*.1).rgb;}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    vec2 v=uv*(1.-uv);
    uv-=.5;
    uv.x*=iResolution.x/iResolution.y;

    vec2 uvn=uv*2.5;
    vec2 iuvn=floor(uvn)+vec2(2.,0.);
    vec2 fuvn=fract(uvn);
    vec3 nb=mix(
        mix(noise(iuvn+vec2(0.,0.)), noise(iuvn+vec2(1.,0.)), fuvn.x),
        mix(noise(iuvn+vec2(0.,1.)), noise(iuvn+vec2(1.,1.)), fuvn.x),
        fuvn.y)*.1;
    vec3 c=(vec3(0.168, 0, 0.2)*.5+nb*3.);

    vec2 suv=uv;
    suv*=rz2(iTime*.02);
    c*=vec3(1./(1.-smoothstep(0.9,1.,texture(iChannel1,suv).r)));

    vec2 uvc=uv-vec2(.4,.2);
    float circle=1.-smoothstep(.25,.252,length(uvc));
    float raytime=uv.y*100.+iTime*2.;
    float thr=-uvc.y*5.-1.;
    float rays= step(thr,sin(raytime));
    circle=min(circle,rays);
    vec3 csun=mix(vec3(0.968, 0.137, 0.094),vec3(1, 0.819, 0.019),uvc.y*3.+.5);
    c=mix(c,csun,circle);

    vec3 ro=vec3(0.,2.,0.),rd=vec3(uv,1),mp=ro;
    rd.yz*=rz2(-.2);
    int i;
    for(i=0;i<50;++i){map(mp);if(m.d<.001){break;}mp+=rd*.5*m.d;}
    if(mp.z<14.)c=m.c;

    c=max(c,0.);
    float cren=fract(uv.y*200.+iTime*.5);
    c+=(smoothstep(.2,.3,cren)-smoothstep(.7,.8,cren))*0.01;
    c=pow(c,vec3(1./2.2));
    c *= pow(v.x*v.y * 25.0, 0.25);
	fragColor = vec4(c,1.);
}
)"
            },

            // ---------------------------------------------------------------------------

            // TODO needs iChannel

            {
                "Vaporwave Outrun",

                R"(
#define PI 3.14159265358979
#define SPEED 0.25
#define GRID_COUNT 32.
#define STEP 0.005
#define COUNT 256.
#define HEIGHT 0.25
#define SUN_SPEED 0.3

vec3 GetBackgroundColor(in vec3 ray)
{
    vec3 c0 = vec3(115. / 255., 25. / 255., 171. / 255.);
    vec3 c1 = vec3(235. / 255., 51. / 255., 201. / 255.);
    vec3 c2 = vec3(40. / 255., 7. / 255., 80. / 255.);
    float a = fract(iTime * 0.5) * 2.0;
    a = a > 1.0 ? 2.0 - a : a;
    vec3 c = c0 * a + c2 * (1.0 - a);
    a = pow(1.0 - abs(ray.y), 0.25);
    float b = abs(atan(ray.x / ray.z)) / PI;
    float m = texture(iChannel1, vec2(b * 0.05, fract(iTime * 0.00005))).x;
    a = 0.85 * a - 0.05 * m;

    c = c1 * a + c * (1.0 - a);
    return c;
}

bool GetHitWithPlane(in vec3 o, in vec3 ray, out vec3 hitPoint)
{
    bool hit = false;
    hitPoint = vec3(0.0, 0.0, 0.0);
    float realHeight = 0.;
    float preRealHeight = 0.;
    float _step = STEP;// min(STEP / abs(ray.y), 2. * STEP);
    for (float i = 1.; i <= COUNT; i++)
    {
        vec3 current = o + ray * _step * i;
        realHeight = texture(iChannel0, current.xz / 16.).x * HEIGHT;
        float s = abs(current.x - o.x) / 0.5;
        s = clamp(s * s, 0., 1.);
        realHeight *= s;
        if (current.y < realHeight)
        {
            vec3 last = current - ray * _step;
            float preDiff = last.y - preRealHeight;
            float curDiff = realHeight - current.y;
            float t = preDiff / (preDiff + curDiff);
            current = last + ray * _step * t;
            hitPoint = current;
            return true;
        }
        preRealHeight = realHeight;
    }
    return hit;
}

vec3 GetHitPointColor(in vec3 cameraPos, in vec3 hitPoint, in vec3 background)
{
    float fx = abs(fract(hitPoint.x * GRID_COUNT + 0.5) - 0.5);
    float fz = abs(fract(hitPoint.z * GRID_COUNT + 0.5) - 0.5);

    vec3 b = vec3(0.2, 0.6, 0.9);
    vec3 r = background;
    r.x = pow(r.x, 3.3);
    r.y = pow(r.y, 0.7);
    r.z = pow(r.z, 0.5);
    float d = length(hitPoint.xz - cameraPos.xz) * 0.15;
    d = clamp(d, 0., 1.);
    vec3 col = r * d + b * (1. - d);
    float li = texture(iChannel0, hitPoint.xz / 64. + vec2(0, -iTime * 0.005)).x * 0.5 + 0.5;
    float lo = abs(hitPoint.z - cameraPos.z) + 0.3;
    col /= min(li, lo);


    d = min(fx, fz);
    d = smoothstep(d, 0., 0.02);

    return r * d + col * (1. - d);
}

vec4 GetSun(in vec3 cameraPos, in vec3 ray)
{
    if (dot(ray, normalize(vec3(0.0, 0.035, 1.0))) > 0.96)
    {
        vec4 r = vec4(1., 0., 0., 1.);
        vec4 y = vec4(2., 2., 0., 1.);
        float a = abs(ray.y);
        vec4 col = y * a + r * (1. - a);

        float ft = fract(iTime * SUN_SPEED) * 0.25;
        vec2 l0 = vec2(-ft + 0.05, ft * 0.2);
        ft = fract(iTime * SUN_SPEED + 0.25) * 0.25;
        vec2 l1 = vec2(-ft + 0.05, ft * 0.2);
        ft = fract(iTime * SUN_SPEED + 0.5) * 0.25;
        vec2 l2 = vec2(-ft + 0.05, ft * 0.2);
        ft = fract(iTime * SUN_SPEED + 0.75) * 0.25;
        vec2 l3 = vec2(-ft + 0.05, ft * 0.2);
        return col * (1. -
                      step(l0.x - l0.y, ray.y) * step(ray.y, l0.x + l0.y) -
                      step(l1.x - l1.y, ray.y) * step(ray.y, l1.x + l1.y) -
                      step(l2.x - l2.y, ray.y) * step(ray.y, l2.x + l2.y) -
                      step(l3.x - l3.y, ray.y) * step(ray.y, l3.x + l3.y)
                      );

        return col *
                (step(ray.y, -0.03) +
                 step(0., ray.y) * step(ray.y, 0.04) +
                 step(0.06, ray.y) * step(ray.y, 0.11) +
                 step(0.13, ray.y) * step(ray.y, 0.18) +
                 step(0.195, ray.y)
                 );
    }
    return vec4(0.0, 0.0, 0.0, 0.0);
}

vec4 GetScreenColor(in vec3 ray, in vec3 cameraPos)
{
    vec3 background = GetBackgroundColor(ray);
    bool hit;
    vec3 hitPoint;
    hit = GetHitWithPlane(cameraPos, ray, hitPoint);
    vec3 plane = GetHitPointColor(cameraPos, hitPoint, background);
    if (hit)
        return vec4(plane, 1);
    vec4 sun = GetSun(cameraPos, ray);

    return vec4(background * (1.0 - sun.w) + sun.xyz * sun.w, 1.);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord/iResolution.xy;
    vec2 cuv = uv * 2.0 - 1.0;
    cuv.x *= iResolution.x / iResolution.y;
    vec3 ray = normalize(vec3(cuv.x, cuv.y, 1.2));

    float ix = PI * 0.5 + (iMouse.x / iResolution.x) * PI;
    float iy = iMouse.y / iResolution.y * PI * 0.25;

    vec3 f = vec3(
        cos(ix) * cos(iy),
        sin(iy),
        sin(ix) * cos(iy)
    );
    f = normalize(f);
    vec3 u = vec3(0.0, 1.0, 0.0);
    vec3 r = normalize(cross(f, u));
    u = normalize(cross(r, f));


    fragColor = GetScreenColor(normalize(f * ray.z + u * ray.y + r * ray.x), vec3(0.0, 0.1, iTime * SPEED));
}
)"
            },

            // ---------------------------------------------------------------------------

            // TODO needs iChannel

            {
                "Synthwave Triangles",

                R"(
// credits to @spalmer for grid smooth function https://www.shadertoy.com/view/wl3Sz2
#define MAX_STEPS 156
#define MIN_DISTANCE 0.01
#define MAX_DISTANCE 16.
#define GRID_SIZE 4.
#define speed 6.
#define MOUNTAIN_COLOR vec3(0.54, 0.11, 1.)
#define COLOR_PURPLE vec3(0.81, 0.19, 0.78)
#define COLOR_LIGHT vec3(0.14, 0.91, 0.98)
#define COLOR_SUN vec3(1., 0.56, 0.098)
#define MATERIAL_PLANE 1.
#define MATERIAL_BACK 2.
#define GRID_THICKNESS .2
#define COLOR_NIGHT_GRID vec3(0., .15, 0.)
#define COLOR_NIGHT_SUN vec3(0.5, .0, 0.)
#define COLOR_NIGHT_MOUNTAIN vec3(0.9, .3, 0.1)
#define SUNSET_SPEED 3.


#define beatScale 3.7
#define beatBias 0.


vec3 lightPos = vec3(0., 3., -10.);

struct traceResult {
    bool  isHit;
    float distanceTo;
    float material;
    float planeHeight;
    vec3 planeNormal;
};

struct getDistResult {
    float distanceTo;
    float material;
    float planeHeight;
    vec3 planeNormal;
};

float sdPlane(vec3 p, float h) {
    return p.y - h;
}

float N21(vec2 p) {
    return fract(sin(p.x*223.32+p.y*5677.)*4332.23);
}

mat2 rot2d(float a) {
    float c = cos(a);
    float s = sin(a);
    return mat2(vec2(c,-s), vec2(s,c));
}

float getHeight(vec2 id) {
    //return 0.;
    float ax = abs(id.x);
    if (ax < GRID_SIZE) {
        return 0.;
    }

    float n = N21(id);

    float wave = sin(id.y/9. + cos(id.x/3.))*sin(id.x/9. + sin(id.y/4.));

    wave = clamp((wave * .5 + .5) + n*.15 - .6, 0., 1.);
    if (ax < (GRID_SIZE + 5.) && ax >= GRID_SIZE) {
        wave *= (ax - GRID_SIZE + 1.)*.2;
    }
    return (wave*10.);
}


getDistResult getDist(vec3 p) {
    float size = GRID_SIZE;
    vec3 nuv = p * size + vec3(0., 0., iTime * speed);
    vec2 uv = fract(nuv).xz;
    vec2 id = floor(nuv).xz;

    vec2 lv = uv;

    float bl = getHeight(id);
    float br = getHeight(id + vec2(1., 0.));
    float b = mix(bl, br, lv.x);

    float tl = getHeight(id + vec2(0., 1.));
    float tr = getHeight(id + vec2(1., 1.));
    float t = mix(tl, tr, lv.x);

    float height = mix(b,t, lv.y);

    float O = bl;
    float R = br;
    float T = getHeight(id + vec2(0. -1.));
    float B = tl;
    float L = getHeight(id + vec2(-1., 0));

    vec3 n = vec3(2.*(R-L), 2.*(B-T), -4.);


    float d = sdPlane(p, -.5 + 0.3*height);

    float db = -p.z + MAX_DISTANCE*.4;
    d = min(d, db);

    getDistResult result;

    result.distanceTo = d;
    result.material = MATERIAL_PLANE;
    result.planeHeight = height;
    result.planeNormal = normalize(n);

    if (d == db) {
        result.material = MATERIAL_BACK;
    }

    return result;
}

traceResult trace(vec3 ro, vec3 rd) {
    traceResult result;
    float ds, dt;
    getDistResult dist;
    for(int i = 0 ; i < MAX_STEPS ; i++) {
        vec3 p = ro + rd * ds;
        dist = getDist(p);
        dt = dist.distanceTo;
        ds += dt * .6;
        if (abs(dt) < MIN_DISTANCE || ds > MAX_DISTANCE) {
            break;
        }
    }
    result.isHit = abs(dt) < MIN_DISTANCE;
    result.distanceTo = ds;
    result.material = dist.material;
    result.planeHeight = dist.planeHeight;
    result.planeNormal = dist.planeNormal;
    return result;
}

float getLightDiffuse(vec3 p, float material, float height, vec3 normal) {
    vec3 l = normalize(lightPos - p);
    float dif = clamp(dot(normal, l), 0., 1.);
    return dif;
}

vec3 starsLayer(vec2 ouv) {
    vec3 col = vec3(0.);

    vec2 uv = fract(ouv) - .5;

    float d;

    for(int x = -1 ; x <= 1; x++) {
        for(int y = -1 ; y <= 1; y++) {
            vec2 offset = vec2(x,y);
            vec2 id = floor(ouv) + offset;
            float n = N21(id);
            if (n > .6) {
                float n1 = fract(n*123.432);
                float n2 = fract(n*1234.2432);

                float size = .01 + 0.05 * (n1 - .5);

                vec2 shift = vec2(n1 - .5, n2 - .5);
                d = max(d, size/length(uv - offset + shift));
            }
        }
    }


    return col + d*vec3(.1, .9, .1);
}

vec3 backgroundStars(vec2 uv) {
    vec3 col = vec3(0.);

    float t = iTime * (speed / 30.);

    float layers = 3.;

    for(float i = 0. ; i < 1. ; i+= 1./layers) {
        float depth = fract(i + t);
        float scale = mix(20., .5, depth);
        float fade = depth * smoothstep(1., .9, depth);

        col += starsLayer(uv * scale + i * 456.32) * fade;
    }
    return col;
}

vec3 getOthersideBackground(vec2 uv) {
    return backgroundStars(uv/8. + sin(iTime/(speed)));
}

vec3 getBackground(vec2 uv) {
    float set = 0. - clamp(sin(iTime/SUNSET_SPEED)*3., -1., 2.);

    float sunDist = length(uv + vec2(0., -2.5 - set));
    float sun = 1. - smoothstep(2.35, 2.5, sunDist);

    float gradient = sin(uv.y/4. - 3.14/32. + set/3.)*2.;
    float bands = abs(sin(uv.y * 8. + iTime*2.)) * (1. - step(2.5 + set, uv.y));

    float skyTop = 2.12/distance(uv, vec2(uv.x, 9.5));
    float skyBottom = 1.12/distance(uv, vec2(uv.x, -1.5));

    vec3 result;

    // sun

    if (set < -1.8) {
        result = vec3(sun) * (bands > 0. ? bands : 1.) * mix(vec3(0.), COLOR_NIGHT_SUN, ((abs(set) - 1.6) -.2) * 15.);
        float glow = smoothstep(.1, .5, (1.1)/sunDist);
        result += glow * COLOR_NIGHT_SUN;
    } else {
        result = vec3(sun * gradient * (bands > 0. ? bands : 1.)) * COLOR_SUN;
        //glow
        float glow = smoothstep(.1, .5, (1.1)/sunDist) + clamp(-1., 1., set);
        // result += glow * COLOR_PURPLE;

        // sky
        result += max(glow * COLOR_PURPLE, ((skyTop * MOUNTAIN_COLOR) + (skyBottom * COLOR_PURPLE))*(1. + set));
    }



    if (sun < .5) {
        // stars
        vec2 nuv = uv*2.;// + vec2(iTime, 0.);
        vec2 rize = vec2(-10., 12.);
        nuv -= rize;
        nuv *= rot2d(mod(-iTime/15., 6.28));
        nuv += rize;
        uv = fract(nuv);
        vec2 id = floor(nuv);
        uv -= .5;

        float n = N21(id);
        uv.x += fract(n*100.32) - .5;
        uv.y += fract(n*11323.432) - .5;

        float star = smoothstep(.5, 1., (0.03 + (0.02 * (fract(n*353.32) - .5)))/length(uv));

        result += star * step(.8, n);
    }

    return result;
}
float filterWidth2(vec2 uv)
{
     vec2 dx = dFdx(uv), dy = dFdy(uv);
    return dot(dx, dx) + dot(dy, dy) + .0001;
}

// (c) spalmer https://www.shadertoy.com/view/wl3Sz2
float gridPow(vec2 uv)
{
    vec2 p = uv * GRID_SIZE + vec2(0., iTime * speed);
    const float fadePower = 16.;
    vec2 f = fract(p);
    f = .5 - abs(.5 - f);
    f = max(vec2(0), 1. - f + .5*GRID_THICKNESS);
    f = pow(f, vec2(fadePower));
    float g = f.x+f.y; //max(f.x, f.y); //
    float s = sqrt(GRID_THICKNESS);
    return mix(g, s, exp2(-.01 / filterWidth2(p)));
}

vec3 getAlbedo(vec3 p, float material, float height, vec3 normal) {
    if (material == MATERIAL_BACK) {
        return getBackground(p.xy);
    }

    float sunSet = sin(iTime/SUNSET_SPEED)*.5 + .5;

    vec3 col = vec3(0.);
    float grid = gridPow(p.xz);

    float maxHeight = 2.5;

    vec3 grid_color = COLOR_PURPLE;
    vec3 cell_color = vec3(0.);
    vec3 mountain_color = MOUNTAIN_COLOR;
    mountain_color = mix(mountain_color, COLOR_NIGHT_MOUNTAIN, sunSet);



    if (height > 0.) {
        grid_color = mix(COLOR_PURPLE, COLOR_LIGHT, height/maxHeight);
        cell_color = mountain_color * mix(vec3(0.), mountain_color, height/maxHeight);
    }

    grid_color = mix(grid_color, COLOR_NIGHT_GRID, sunSet);

    col = mix(vec3(0.), grid_color, grid) + cell_color;

    return vec3(col);
}

float polarTriangle(vec2 uv, float offset) {
    float a = atan(uv.x, uv.y) + offset;
    float b = 6.28 / 3.;
    float l = length(uv);

    float d = cos(a - floor(.5 + a/b) * b) * l;

    return d;
}

float triangleMask(vec2 uv) {
    return polarTriangle(uv + vec2(0., -.1),3.14 + .5*sin(iTime));
}


void mainImage(out vec4 fragColor, in vec2 fragCoords) {
    vec2 uv = fragCoords.xy / iResolution.xy;
    uv -= .5;
    uv.x *= iResolution.x / iResolution.y;

    vec2 mouse = iMouse.xy / iResolution.xy;

    // lightPos.z = sin(iTime/3.)*100.;

	float freqs[6];
	//Sound
	freqs[0] = texture( iChannel0, vec2( 0.01, 0.25 ) ).x;
	freqs[1] = texture( iChannel0, vec2( 0.03, 0.25 ) ).x;
	freqs[2] = texture( iChannel0, vec2( 0.05,  0.25 ) ).x;
	freqs[3] = texture( iChannel0, vec2( 0.07, 0.25 ) ).x;
	freqs[4] = texture( iChannel0, vec2( 0.17, 0.25 ) ).x;
	freqs[5] = texture( iChannel0, vec2( 0.25, 0.25 ) ).x;

    //////////////////

    float beat = 0.25*freqs[0]*freqs[0]
                +0.35*freqs[1]*freqs[1]
                +0.25*freqs[2]*freqs[2]
                +0.15*freqs[3]*freqs[3];
    beat = sqrt(beat) * beatScale + beatBias;


    float beat2 = 0.3*freqs[3]*freqs[3]
                 +0.4*freqs[4]*freqs[4]
                 +0.3*freqs[5]*freqs[5];
    beat2 = sqrt(beat2) * beatScale + beatBias;

    //////////////////

    mouse.x = 0.5;
    mouse.y = 0.;

    vec3 col = vec3(0.);

    vec3 ro = vec3(0., .5, -.4);
    vec3 lookat = vec3(mouse.x*2.-1., 1. - mouse.y - .6, 0.);
    float zoom = .4;


    vec3 f = normalize(lookat - ro);
    vec3 r = normalize(cross(vec3(0., 1., 0), f));
    vec3 u = cross(f, r);
    vec3 c = ro + f * zoom;
    vec3 i = c + uv.x * r + uv.y * u;

    vec3 rd = normalize(i - ro);

    vec3 p = vec3(0.);

    traceResult tr = trace(ro, rd);

    if (tr.isHit) {

        p = ro + rd * tr.distanceTo;

        vec3 albedo = getAlbedo(p, tr.material, tr.planeHeight, tr.planeNormal);

        float diffuse = getLightDiffuse(p, tr.material, tr.planeHeight, tr.planeNormal)*beat2;

        float fade = 1.;// - clamp((p.z-ro.z)/(MAX_DISTANCE * .8), 0., 1.);

        if (tr.material == MATERIAL_BACK) {
            col = albedo;
        } else {
            col = diffuse * albedo * fade;
        }

        float triangle = triangleMask(uv*(1.-beat/5.));
        float fd = fract(triangle - clamp(sin(iTime/3.), 0., 2.));
        float bc = (1. - step(.2, fd));

        col *= (tr.material == MATERIAL_BACK) ? bc : 1.;
        if (bc == 0.) {
            if (tr.material == MATERIAL_BACK) {
                col = getOthersideBackground(p.xy);
            } else {
                col *= vec3(.8);
            }
        }

        col += ((1. - step(.2, fd)) - (1. - step(.19, fd)))*.3;

    }


    fragColor = vec4(col, 1.);
    // fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2));
}
)"
            },
#endif

            // ---------------------------------------------------------------------------

            {
                "Sierpinski Tetrahedron",  // https://www.shadertoy.com/view/wsVBz1

                R"(
// Raymarching the Sierpinski Tetrahedron: Final
// Created by Anthony Hall for Writ 107T

// Raymarching constants
const float maxDistance = 30.0;
const float epsilon = 0.001;

const float maxShadowDistance = 10.0;
const float shadowEpsilon = 0.005;

// Lighting
const float kAmbient = 0.35;
const float kDiffuse = 1.0 - kAmbient;

const float shadowK = 30.0;

const float aoIncrement = 0.02;
const float aoK = 4.0;

// Camera
vec3 cameraPos = vec3(0.0, 0.5, 4.0);
const float fov = radians(50.0);

// Other scene globals
const vec3 skyColor = vec3(0.5, 0.75, 1.0);
const vec3 toSun = normalize(vec3(-1.0, 3.75, 2.0));

// Number of iterations for the Sierpinski IFS
const int sierpinskiLevel = 5;

// Vertices of the tetrahedron defined by the SDF
const vec3[] vertices = vec3[](
    vec3(1.0, 1.0, 1.0),
    vec3(-1.0, 1.0, -1.0),
    vec3(-1.0, -1.0, 1.0),
    vec3(1.0, -1.0, -1.0));

// Get a 2D rotation matrix
mat2 getRotationMatrix(float angle)
{
	return mat2(cos(angle), sin(angle),
                -sin(angle), cos(angle));
}

// Get a surface color based on a point's location
// Uses a procedural palette from iq
// https://www.shadertoy.com/view/ll2GD3
vec3 getColor(vec3 point)
{
    // Set t such that the floor color will change slowly
    // and the tetrahedron color will change more rapidly
    float t;
    if (point.y < -1.9) {
        t = point.x / 60.0 + 0.2;
    }
    else {
        point /= 2.0;
     	t = point.x * point.x - point.y + point.z * point.z;
    }

    vec3 a = vec3(0.5);
    vec3 b = vec3(0.5);
    vec3 c = vec3(1.0);
    vec3 d = vec3(0.00, 0.10, 0.20);
	vec3 color = a + b*cos( radians(360.0)*(c*t+d) );

    // Lighten the color a bit
    return mix(color, vec3(1.0), 0.3);
}

// Signed distance to a floor plane
float sdFloor(vec3 point, float floorY)
{
	return point.y - floorY;
}

// Signed distance to a tetrahedron within canonical cube
// https://www.shadertoy.com/view/Ws23zt
float sdTetrahedron(vec3 point)
{
    return (max(
	    abs(point.x + point.y) - point.z,
	    abs(point.x - point.y) + point.z
	) - 1.0) / sqrt(3.);
}

// Fold a point across a plane defined by a point and a normal
// The normal should face the side to be reflected
vec3 fold(vec3 point, vec3 pointOnPlane, vec3 planeNormal)
{
    // Center plane on origin for distance calculation
    float distToPlane = dot(point - pointOnPlane, planeNormal);

    // We only want to reflect if the dist is negative
    distToPlane = min(distToPlane, 0.0);
    return point - 2.0 * distToPlane * planeNormal;
}

// Signed distance to Sierpinski tetrahedron at specified level
// Rotates over time or with mouse press
float sdSierpinski(vec3 point, int level)
{
    // If the mouse is not pressed, rotate the tetrahedron over time
    // Otherwise, rotate it based on the mouse position
    if (iMouse.z <= 0.0) {
        float time = iTime / 4.0;
        point.xz = getRotationMatrix(time) * point.xz;
    }
    else {
     	vec2 mouse = (2.0 * iMouse.xy - iResolution.xy) / iResolution.y;

        point.yz = getRotationMatrix(mouse.y) * point.yz;
        point.xz = getRotationMatrix(mouse.x) * point.xz;
    }

    float scale = 1.0;
    for (int i = 0; i < level; i++)
    {
    	// Scale point toward corner vertex, update scale accumulator
        point -= vertices[0];
        point *= 2.0;
        point += vertices[0];

        scale *= 2.0;

        // Fold point across each plane
        for (int i = 1; i <= 3; i++)
        {
            // The plane is defined by:
            // Point on plane: The vertex that we are reflecting across
            // Plane normal: The direction from said vertex to the corner vertex
         	vec3 normal = normalize(vertices[0] - vertices[i]);
            point = fold(point, vertices[i], normal);
        }
    }
    // Now that the space has been distorted by the IFS,
    // just return the distance to a tetrahedron
    // Divide by scale accumulator to correct the distance field
    return sdTetrahedron(point) / scale;
}

// Returns signed distance to the scene
float scene(vec3 point)
{
    // Create a sierpinski tetrahedron and a floor
 	float sierpinskiDist = sdSierpinski(point, sierpinskiLevel);
    float floorDist = sdFloor(point, -2.0);

    return min(sierpinskiDist, floorDist);
}

// Approximates the normal at an intersection by calculating the gradient of the distance function
vec3 estimateNormal(vec3 point) {
	return normalize(vec3(
        scene(vec3(point.x + epsilon, point.y, point.z)) - scene(vec3(point.x - epsilon, point.y, point.z)),
        scene(vec3(point.x, point.y + epsilon, point.z)) - scene(vec3(point.x, point.y - epsilon, point.z)),
        scene(vec3(point.x, point.y, point.z  + epsilon)) - scene(vec3(point.x, point.y, point.z - epsilon))));
}

// Distance field AO
// https://iquilezles.org/www/material/nvscene2008/rwwtt.pdf slide 53
float calcAO(vec3 surfacePoint, vec3 normal)
{
    float t = aoIncrement;
    float distSum = 0.0; // Sum of distance differences

    // Take four distance samples, compare to orthogonal distance
    for (int i = 0; i < 4; i++)
    {
        vec3 point = surfacePoint + t * normal;
     	float dist = scene(point);

        distSum += exp2(-float(i)) * (t - dist);

        t += aoIncrement;
    }
    return 1.0 - aoK * distSum;
}

// Calculates the percentage that a point is illuminated
// https://iquilezles.org/articles/rmshadows
float calcShadow(vec3 surfacePoint)
{
    // Initialize our marching variables
 	vec3 point = surfacePoint;
    float t;
    float illumination = 1.0;

    // Initialize the ray a little bit away from the point
    // We don't want to start close enough to be considered a hit
    for (t = 2.0 * shadowEpsilon; t < maxShadowDistance;)
    {
     	point = surfacePoint + t * toSun;
        float dist = scene(point);

        // The path to the sun is blocked
        if (dist < shadowEpsilon) {
            return 0.0;
        }

        // Get darker if we get closer to the scene than we have been before
        illumination = min(illumination, shadowK * dist/t);
        t += dist;
    }
    return illumination;
}

// Shades a surface at the given point
vec3 shadeSurface(vec3 point) {
    // Calculate the surface normal and color of our point
    vec3 normal = estimateNormal(point);
    vec3 surfaceColor = getColor(point);

    // Ambient
    vec3 color = kAmbient * surfaceColor;

    // Diffuse
	float diffuseIntensity = max(dot(normal, toSun), 0.0);

    // Shadow
    float illumination = calcShadow(point);
    diffuseIntensity *= illumination;
    color += kDiffuse * diffuseIntensity * surfaceColor;

    // AO (only on pyramid)
    if (point.y > -2.0 + epsilon) {
        float occlusion = calcAO(point, normal);
        color *= occlusion;
    }

    return color;
}

// Returns the result color of casting any ray
vec3 castRay(vec3 rayOrigin, vec3 rayDir)
{
    // Initialize our marching variables
    vec3 point = rayOrigin;
    float t;
    vec3 color = skyColor;

    // Repeatedly march the ray forward based on the distance to the scene
    for (t = 0.0; t < maxDistance; point = rayOrigin + t * rayDir)
    {
     	float dist = scene(point);

        // We got a hit
        if (dist <= epsilon) {
            color = shadeSurface(point);
        	break;
        }
        t += dist;
    }
    float totalDist = t / maxDistance;
    return mix(color, skyColor, totalDist * totalDist);
}

mat3 rotateRay(vec3 camera, vec3 dest, vec3 up)
{
    vec3 forward = normalize(dest - camera);
    vec3 right = normalize(cross(forward, up));
    up = cross(right, forward);
    return mat3(right, up, -forward);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalize the coordinates to [-1, 1] in the minimum dimension
    // Use this to calculate the ray direction
    float minDimension = min(iResolution.x, iResolution.y);
    vec2 coord = 2.0 * (fragCoord - iResolution.xy/2.0) / minDimension;
    vec3 rayDir = normalize(vec3(coord * tan(fov/2.0), -1.0));

    // Make the camera point toward the origin
    rayDir = rotateRay(cameraPos, vec3(0), vec3(0, 1, 0)) * rayDir;

    // Cast the ray!
    vec3 color = castRay(cameraPos, rayDir);
    fragColor = vec4(color, 1.0);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Menger Sponge", // https://www.shadertoy.com/view/4sX3Rn

                R"(
// The MIT License
// https://www.youtube.com/c/InigoQuilez
// https://iquilezles.org/
// Copyright © 2013 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// https://iquilezles.org/articles/menger


#if HW_PERFORMANCE==0
#define AA 1
#else
#define AA 2
#endif


float maxcomp(in vec3 p ) { return max(p.x,max(p.y,p.z));}
float sdBox( vec3 p, vec3 b )
{
    vec3 di = abs(p) - b;
    return min(maxcomp(di),length(max(di,0.0)));
}

vec2 iBox( in vec3 ro, in vec3 rd, in vec3 rad )
{
    vec3 m = 1.0/rd;
    vec3 n = m*ro;
    vec3 k = abs(m)*rad;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
	return vec2( max( max( t1.x, t1.y ), t1.z ),
	             min( min( t2.x, t2.y ), t2.z ) );
}

const mat3 ma = mat3( 0.6, 0.0,  0.8,
                      0.0, 1.0,  0.0,
                     -0.8, 0.0,  0.6);
vec4 map( in vec3 p )
{
    float d = sdBox(p,vec3(1.0));
    vec4 res = vec4( d, 1.0, 0.0, 0.0 );

    float ani = smoothstep( -0.2, 0.2, -cos(0.5*iTime) );
	float off = 1.5*sin( 0.01*iTime );

    float s = 1.0;
    for( int m=0; m<4; m++ )
    {
        p = mix( p, ma*(p+off), ani );

        vec3 a = mod( p*s, 2.0 )-1.0;
        s *= 3.0;
        vec3 r = abs(1.0 - 3.0*abs(a));
        float da = max(r.x,r.y);
        float db = max(r.y,r.z);
        float dc = max(r.z,r.x);
        float c = (min(da,min(db,dc))-1.0)/s;

        if( c>d )
        {
          d = c;
          res = vec4( d, min(res.y,0.2*da*db*dc), (1.0+float(m))/4.0, 0.0 );
        }
    }

    return res;
}

vec4 intersect( in vec3 ro, in vec3 rd )
{
    vec2 bb = iBox( ro, rd, vec3(1.05) );
    if( bb.y<bb.x ) return vec4(-1.0);

    float tmin = bb.x;
    float tmax = bb.y;

    float t = tmin;
    vec4 res = vec4(-1.0);
    for( int i=0; i<64; i++ )
    {
        vec4 h = map(ro + rd*t);
		if( h.x<0.002 || t>tmax ) break;
        res = vec4(t,h.yzw);
        t += h.x;
    }
	if( t>tmax ) res=vec4(-1.0);
    return res;
}

float softshadow( in vec3 ro, in vec3 rd, float mint, float k )
{
    vec2 bb = iBox( ro, rd, vec3(1.05) );
    float tmax = bb.y;

    float res = 1.0;
    float t = mint;
    for( int i=0; i<64; i++ )
    {
        float h = map(ro + rd*t).x;
        res = min( res, k*h/t );
        if( res<0.001 ) break;
		t += clamp( h, 0.005, 0.1 );
        if( t>tmax ) break;
    }
    return clamp(res,0.0,1.0);
}

vec3 calcNormal(in vec3 pos)
{
    vec3 eps = vec3(.001,0.0,0.0);
    return normalize(vec3(
    map(pos+eps.xyy).x - map(pos-eps.xyy).x,
    map(pos+eps.yxy).x - map(pos-eps.yxy).x,
    map(pos+eps.yyx).x - map(pos-eps.yyx).x ));
}

vec3 render( in vec3 ro, in vec3 rd )
{
    // background color
    vec3 col = mix( vec3(0.3,0.2,0.1)*0.5, vec3(0.7, 0.9, 1.0), 0.5 + 0.5*rd.y );

    vec4 tmat = intersect(ro,rd);
    if( tmat.x>0.0 )
    {
        vec3  pos = ro + tmat.x*rd;
        vec3  nor = calcNormal(pos);

        vec3 matcol = 0.5 + 0.5*cos(vec3(0.0,1.0,2.0)+2.0*tmat.z);

        float occ = tmat.y;

        const vec3 light = normalize(vec3(1.0,0.9,0.3));
        float dif = dot(nor,light);
        float sha = 1.0;
        if( dif>0.0 ) sha=softshadow( pos, light, 0.01, 64.0 );
        dif = max(dif,0.0);
        vec3  hal = normalize(light-rd);
        float spe = dif*sha*pow(clamp(dot(hal,nor),0.0,1.0),16.0)*(0.04+0.96*pow(clamp(1.0-dot(hal,light),0.0,1.0),5.0));

		float sky = 0.5 + 0.5*nor.y;
        float bac = max(0.4 + 0.6*dot(nor,vec3(-light.x,light.y,-light.z)),0.0);

        vec3 lin  = vec3(0.0);
        lin += 1.00*dif*vec3(1.10,0.85,0.60)*sha;
        lin += 0.50*sky*vec3(0.10,0.20,0.40)*occ;
        lin += 0.10*bac*vec3(1.00,1.00,1.00)*(0.5+0.5*occ);
        lin += 0.25*occ*vec3(0.15,0.17,0.20);
        col = matcol*lin + spe*128.0;
    }

    col = 1.5*col/(1.0+col);
    col = sqrt( col );

    return col;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // camera
    vec3 ro = 1.1*vec3(2.5*sin(0.25*iTime),1.0+1.0*cos(iTime*.13),2.5*cos(0.25*iTime));

#if AA>1
    #define ZERO (min(iFrame,0))
    vec3 col = vec3(0.0);
    for( int m=ZERO; m<AA; m++ )
    for( int n=ZERO; n<AA; n++ )
    {
        // pixel coordinates
        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
        vec2 p = (2.0*(fragCoord+o)-iResolution.xy)/iResolution.y;

        vec3 ww = normalize(vec3(0.0) - ro);
        vec3 uu = normalize(cross( vec3(0.0,1.0,0.0), ww ));
        vec3 vv = normalize(cross(ww,uu));
        vec3 rd = normalize( p.x*uu + p.y*vv + 2.5*ww );

        col += render( ro, rd );
    }
    col /= float(AA*AA);
#else
    vec2 p = (2.0*fragCoord-iResolution.xy)/iResolution.y;
    vec3 ww = normalize(vec3(0.0) - ro);
    vec3 uu = normalize(cross( vec3(0.0,1.0,0.0), ww ));
    vec3 vv = normalize(cross(ww,uu));
    vec3 rd = normalize( p.x*uu + p.y*vv + 2.5*ww );
    vec3 col = render( ro, rd );
#endif

    fragColor = vec4(col,1.0);
}


void mainVR( out vec4 fragColor, in vec2 fragCoord, in vec3 fragRayOri, in vec3 fragRayDir )
{
    float time = iTime*0.25 + 0.01*iMouse.x;
    float anim = 1.1 + 0.5*smoothstep( -0.3, 0.3, cos(0.1*iTime) );

    vec3 col = render( fragRayOri + vec3(0.0,1.0,2.5), fragRayDir );
    fragColor = vec4( col, 1.0 );
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Mandelbrot - distance",  // https://www.shadertoy.com/view/lsX3W4

                R"(
// https://www.shadertoy.com/view/lsX3W4
)"
            },

            // ---------------------------------------------------------------------------

            {
                "mandelbulb_",  // https://www.shadertoy.com/view/MdXSWn

                R"(
// Created by evilryu
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.


// whether turn on the animation
//#define phase_shift_on

float stime, ctime;
 void ry(inout vec3 p, float a){
 	float c,s;vec3 q=p;
  	c = cos(a); s = sin(a);
  	p.x = c * q.x + s * q.z;
  	p.z = -s * q.x + c * q.z;
 }

float pixel_size = 0.0;

/*

z = r*(sin(theta)cos(phi) + i cos(theta) + j sin(theta)sin(phi)

zn+1 = zn^8 +c

z^8 = r^8 * (sin(8*theta)*cos(8*phi) + i cos(8*theta) + j sin(8*theta)*sin(8*theta)

zn+1' = 8 * zn^7 * zn' + 1

*/

vec3 mb(vec3 p) {
	p.xyz = p.xzy;
	vec3 z = p;
	vec3 dz=vec3(0.0);
	float power = 8.0;
	float r, theta, phi;
	float dr = 1.0;

	float t0 = 1.0;
	for(int i = 0; i < 7; ++i) {
		r = length(z);
		if(r > 2.0) continue;
		theta = atan(z.y / z.x);
        #ifdef phase_shift_on
		phi = asin(z.z / r) + iTime*0.1;
        #else
        phi = asin(z.z / r);
        #endif

		dr = pow(r, power - 1.0) * dr * power + 1.0;

		r = pow(r, power);
		theta = theta * power;
		phi = phi * power;

		z = r * vec3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi)) + p;

		t0 = min(t0, r);
	}
	return vec3(0.5 * log(r) * r / dr, t0, 0.0);
}

 vec3 f(vec3 p){
	 ry(p, iTime*0.2);
     return mb(p);
 }


 float softshadow(vec3 ro, vec3 rd, float k ){
     float akuma=1.0,h=0.0;
	 float t = 0.01;
     for(int i=0; i < 50; ++i){
         h=f(ro+rd*t).x;
         if(h<0.001)return 0.02;
         akuma=min(akuma, k*h/t);
 		 t+=clamp(h,0.01,2.0);
     }
     return akuma;
 }

vec3 nor( in vec3 pos )
{
    vec3 eps = vec3(0.001,0.0,0.0);
	return normalize( vec3(
           f(pos+eps.xyy).x - f(pos-eps.xyy).x,
           f(pos+eps.yxy).x - f(pos-eps.yxy).x,
           f(pos+eps.yyx).x - f(pos-eps.yyx).x ) );
}

vec3 intersect( in vec3 ro, in vec3 rd )
{
    float t = 1.0;
    float res_t = 0.0;
    float res_d = 1000.0;
    vec3 c, res_c;
    float max_error = 1000.0;
	float d = 1.0;
    float pd = 100.0;
    float os = 0.0;
    float step = 0.0;
    float error = 1000.0;

    for( int i=0; i<48; i++ )
    {
        if( error < pixel_size*0.5 || t > 20.0 )
        {
        }
        else{  // avoid broken shader on windows

            c = f(ro + rd*t);
            d = c.x;

            if(d > os)
            {
                os = 0.4 * d*d/pd;
                step = d + os;
                pd = d;
            }
            else
            {
                step =-os; os = 0.0; pd = 100.0; d = 1.0;
            }

            error = d / t;

            if(error < max_error)
            {
                max_error = error;
                res_t = t;
                res_c = c;
            }

            t += step;
        }

    }
	if( t>20.0/* || max_error > pixel_size*/ ) res_t=-1.0;
    return vec3(res_t, res_c.y, res_c.z);
}

 void mainImage( out vec4 fragColor, in vec2 fragCoord )
 {
    vec2 q=fragCoord.xy/iResolution.xy;
 	vec2 uv = -1.0 + 2.0*q;
 	uv.x*=iResolution.x/iResolution.y;

    pixel_size = 1.0/(iResolution.x * 3.0);
	// camera
 	stime=0.7+0.3*sin(iTime*0.4);
 	ctime=0.7+0.3*cos(iTime*0.4);

 	vec3 ta=vec3(0.0,0.0,0.0);
	vec3 ro = vec3(0.0, 3.*stime*ctime, 3.*(1.-stime*ctime));

 	vec3 cf = normalize(ta-ro);
    vec3 cs = normalize(cross(cf,vec3(0.0,1.0,0.0)));
    vec3 cu = normalize(cross(cs,cf));
 	vec3 rd = normalize(uv.x*cs + uv.y*cu + 3.0*cf);  // transform from view to world

    vec3 sundir = normalize(vec3(0.1, 0.8, 0.6));
    vec3 sun = vec3(1.64, 1.27, 0.99);
    vec3 skycolor = vec3(0.6, 1.5, 1.0);

	vec3 bg = exp(uv.y-2.0)*vec3(0.4, 1.6, 1.0);

    float halo=clamp(dot(normalize(vec3(-ro.x, -ro.y, -ro.z)), rd), 0.0, 1.0);
    vec3 col=bg+vec3(1.0,0.8,0.4)*pow(halo,17.0);


    float t=0.0;
    vec3 p=ro;

	vec3 res = intersect(ro, rd);
	 if(res.x > 0.0){
		   p = ro + res.x * rd;
           vec3 n=nor(p);
           float shadow = softshadow(p, sundir, 10.0 );

           float dif = max(0.0, dot(n, sundir));
           float sky = 0.6 + 0.4 * max(0.0, dot(n, vec3(0.0, 1.0, 0.0)));
 		   float bac = max(0.3 + 0.7 * dot(vec3(-sundir.x, -1.0, -sundir.z), n), 0.0);
           float spe = max(0.0, pow(clamp(dot(sundir, reflect(rd, n)), 0.0, 1.0), 10.0));

           vec3 lin = 4.5 * sun * dif * shadow;
           lin += 0.8 * bac * sun;
           lin += 0.6 * sky * skycolor*shadow;
           lin += 3.0 * spe * shadow;

		   res.y = pow(clamp(res.y, 0.0, 1.0), 0.55);
		   vec3 tc0 = 0.5 + 0.5 * sin(3.0 + 4.2 * res.y + vec3(0.0, 0.5, 1.0));
           col = lin *vec3(0.9, 0.8, 0.6) *  0.2 * tc0;
 		   col=mix(col,bg, 1.0-exp(-0.001*res.x*res.x));
    }

    // post
    col=pow(clamp(col,0.0,1.0),vec3(0.45));
    col=col*0.6+0.4*col*col*(3.0-2.0*col);  // contrast
    col=mix(col, vec3(dot(col, vec3(0.33))), -0.5);  // satuation
    col*=0.5+0.5*pow(16.0*q.x*q.y*(1.0-q.x)*(1.0-q.y),0.7);  // vigneting
 	fragColor = vec4(col.xyz, smoothstep(0.55, .76, 1.-res.x/5.));
 }
)"
            },

            // ---------------------------------------------------------------------------

            {
                "fractal trees gif",  // https://www.shadertoy.com/view/llXfRr

                R"(
#define MAXDIST 50.

struct Ray {
	vec3 ro;
    vec3 rd;
};

// from netgrind
vec3 hue(vec3 color, float shift) {

    const vec3  kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
    const vec3  kRGBToI     = vec3 (0.596, -0.275, -0.321);
    const vec3  kRGBToQ     = vec3 (0.212, -0.523, 0.311);

    const vec3  kYIQToR   = vec3 (1.0, 0.956, 0.621);
    const vec3  kYIQToG   = vec3 (1.0, -0.272, -0.647);
    const vec3  kYIQToB   = vec3 (1.0, -1.107, 1.704);

    // Convert to YIQ
    float   YPrime  = dot (color, kRGBToYPrime);
    float   I      = dot (color, kRGBToI);
    float   Q      = dot (color, kRGBToQ);

    // Calculate the hue and chroma
    float   hue     = atan (Q, I);
    float   chroma  = sqrt (I * I + Q * Q);

    // Make the user's adjustments
    hue += shift;

    // Convert back to YIQ
    Q = chroma * sin (hue);
    I = chroma * cos (hue);

    // Convert back to RGB
    vec3    yIQ   = vec3 (YPrime, I, Q);
    color.r = dot (yIQ, kYIQToR);
    color.g = dot (yIQ, kYIQToG);
    color.b = dot (yIQ, kYIQToB);

    return color;
}

// ------

// by iq

float opU( float d1, float d2 )
{
    return min(d1,d2);
}

float smin( float a, float b, float k ){
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float length6( vec3 p )
{
	p = p*p*p; p = p*p;
	return pow( p.x + p.y + p.z, 1.0/6.0 );
}

// ------

// from hg_sdf

float fPlane(vec3 p, vec3 n, float distanceFromOrigin) {
	return dot(p, n) + distanceFromOrigin;
}

void pR(inout vec2 p, float a) {
	p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}

// -------


float fractal(vec3 p)
{
    const int iterations = 20;

    float d = iTime*5. - p.z;
   	p=p.yxz;
    pR(p.yz, 1.570795);
    p.x += 6.5;

    p.yz = mod(abs(p.yz)-.0, 20.) - 10.;
    float scale = 1.25;

    p.xy /= (1.+d*d*0.0005);

	float l = 0.;

    for (int i=0; i<iterations; i++) {
		p.xy = abs(p.xy);
		p = p*scale + vec3(-3. + d*0.0095,-1.5,-.5);

		pR(p.xy,0.35-d*0.015);
		pR(p.yz,0.5+d*0.02);

        l =length6(p);
	}
	return l*pow(scale, -float(iterations))-.15;
}

vec2 map(vec3 pos)
{
    float dist = 10.;
    dist = opU(dist, fractal(pos));
    dist = smin(dist, fPlane(pos,vec3(0.0,1.0,0.0),10.), 4.6);
    return vec2(dist, 0.);
}

vec3 vmarch(Ray ray, float dist)
{
    vec3 p = ray.ro;
    vec2 r = vec2(0.);
    vec3 sum = vec3(0);
    vec3 c = hue(vec3(0.,0.,1.),5.5);
    for( int i=0; i<20; i++ )
    {
        r = map(p);
        if (r.x > .01) break;
        p += ray.rd*.015;
        vec3 col = c;
        col.rgb *= smoothstep(.0,0.15,-r.x);
        sum += abs(col)*.5;
    }
    return sum;
}

vec2 march(Ray ray)
{
    const int steps = 50;
    const float prec = 0.001;
    vec2 res = vec2(0.);

    for (int i = 0; i < steps; i++)
    {
        vec2 s = map(ray.ro + ray.rd * res.x);

        if (res.x > MAXDIST || s.x < prec)
        {
        	break;
        }

        res.x += s.x;
        res.y = s.y;

    }

    return res;
}

vec3 calcNormal(vec3 pos)
{
	const vec3 eps = vec3(0.005, 0.0, 0.0);

    return normalize(
        vec3(map(pos + eps).x - map(pos - eps).x,
             map(pos + eps.yxz).x - map(pos - eps.yxz).x,
             map(pos + eps.yzx).x - map(pos - eps.yzx).x )
    );
}

vec4 render(Ray ray)
{
    vec3 col = vec3(0.);
	vec2 res = march(ray);

    if (res.x > MAXDIST)
    {
        return vec4(col, 50.);
    }

    vec3 pos = ray.ro+res.x*ray.rd;
    ray.ro = pos;
   	col = vmarch(ray, res.x);

    col = mix(col, vec3(0.), clamp(res.x/50., 0., 1.));
   	return vec4(col, res.x);
}

mat3 camera(in vec3 ro, in vec3 rd, float rot)
{
	vec3 forward = normalize(rd - ro);
    vec3 worldUp = vec3(sin(rot), cos(rot), 0.0);
    vec3 x = normalize(cross(forward, worldUp));
    vec3 y = normalize(cross(x, forward));
    return mat3(x, y, forward);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;
    uv.y -= uv.x*uv.x*0.15;
    vec3 camPos = vec3(3., -1.5, iTime*5.);
    vec3 camDir = camPos+vec3(-1.25,0.1, 1.);
    mat3 cam = camera(camPos, camDir, 0.);
    vec3 rayDir = cam * normalize( vec3(uv, .8));

    Ray ray;
    ray.ro = camPos;
    ray.rd = rayDir;

    vec4 col = render(ray);

	fragColor = vec4(1.-col.xyz,clamp(1.-col.w/MAXDIST, 0., 1.));
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "fractal pyramid",  // https://www.shadertoy.com/view/tsXBzS

                R"(
vec3 palette(float d){
	return mix(vec3(0.2,0.7,0.9),vec3(1.,0.,1.),d);
}

vec2 rotate(vec2 p,float a){
	float c = cos(a);
    float s = sin(a);
    return p*mat2(c,s,-s,c);
}

float map(vec3 p){
    for( int i = 0; i<8; ++i){
        float t = iTime*0.2;
        p.xz =rotate(p.xz,t);
        p.xy =rotate(p.xy,t*1.89);
        p.xz = abs(p.xz);
        p.xz-=.5;
	}
	return dot(sign(p),p)/5.;
}

vec4 rm (vec3 ro, vec3 rd){
    float t = 0.;
    vec3 col = vec3(0.);
    float d;
    for(float i =0.; i<64.; i++){
		vec3 p = ro + rd*t;
        d = map(p)*.5;
        if(d<0.02){
            break;
        }
        if(d>100.){
        	break;
        }
        //col+=vec3(0.6,0.8,0.8)/(400.*(d));
        col+=palette(length(p)*.1)/(400.*(d));
        t+=d;
    }
    return vec4(col,1./(d*100.));
}
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord-(iResolution.xy/2.))/iResolution.x;
	vec3 ro = vec3(0.,0.,-50.);
    ro.xz = rotate(ro.xz,iTime);
    vec3 cf = normalize(-ro);
    vec3 cs = normalize(cross(cf,vec3(0.,1.,0.)));
    vec3 cu = normalize(cross(cf,cs));

    vec3 uuv = ro+cf*3. + uv.x*cs + uv.y*cu;

    vec3 rd = normalize(uuv-ro);

    vec4 col = rm(ro,rd);


    fragColor = col;
}

/** SHADERDATA
{
	"title": "fractal pyramid",
	"description": "",
	"model": "car"
}
*/
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Star Nest",  // https://www.shadertoy.com/view/XlfGRj

                R"(
// Star Nest by Pablo Roman Andrioli
// License: MIT

#define iterations 17
#define formuparam 0.53

#define volsteps 20
#define stepsize 0.1

#define zoom   0.800
#define tile   0.850
#define speed  0.010

#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.730
#define saturation 0.850


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	//get coords and direction
	vec2 uv=fragCoord.xy/iResolution.xy-.5;
	uv.y*=iResolution.y/iResolution.x;
	vec3 dir=vec3(uv*zoom,1.);
	float time=iTime*speed+.25;

	//mouse rotation
	float a1=.5+iMouse.x/iResolution.x*2.;
	float a2=.8+iMouse.y/iResolution.y*2.;
	mat2 rot1=mat2(cos(a1),sin(a1),-sin(a1),cos(a1));
	mat2 rot2=mat2(cos(a2),sin(a2),-sin(a2),cos(a2));
	dir.xz*=rot1;
	dir.xy*=rot2;
	vec3 from=vec3(1.,.5,0.5);
	from+=vec3(time*2.,time,-2.);
	from.xz*=rot1;
	from.xy*=rot2;

	//volumetric rendering
	float s=0.1,fade=1.;
	vec3 v=vec3(0.);
	for (int r=0; r<volsteps; r++) {
		vec3 p=from+s*dir*.5;
		p = abs(vec3(tile)-mod(p,vec3(tile*2.))); // tiling fold
		float pa,a=pa=0.;
		for (int i=0; i<iterations; i++) {
			p=abs(p)/dot(p,p)-formuparam; // the magic formula
			a+=abs(length(p)-pa); // absolute sum of average change
			pa=length(p);
		}
		float dm=max(0.,darkmatter-a*a*.001); //dark matter
		a*=a*a; // add contrast
		if (r>6) fade*=1.-dm; // dark matter, don't render near
		//v+=vec3(dm,dm*.5,0.);
		v+=fade;
		v+=vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance
		fade*=distfading; // distance fading
		s+=stepsize;
	}
	v=mix(vec3(length(v)),v,saturation); //color adjust
	fragColor = vec4(v*.01,1.);

}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Stormy Torus [527]",  // https://www.shadertoy.com/view/tcccRl

                R"(
/*================================
=          Stormy Torus          =
=         Author: Jaenam         =
================================*/
// Date:    2025-11-24
// License: Creative Commons (CC BY-NC-SA 4.0)

// -10 @OldEclipse
// -12 @FabriceNeyret2
// -2 Me :D
// -9 @bug

void mainImage( out vec4 O, vec2 I )
{
    float i,d,w, t = iTime, m = 1.;
    vec3  p,k,r = iResolution,Z;

    for( O*= i ;
         i++ < 1e2 && abs(p.x) < 6. ;

         d += w = .01 + .07* abs( max( mix( sin( length( ceil(4.*k.z) + k) )
               , sin( length(p) - 1. )
               , smoothstep(5., 5.5, p.y)
               ), sqrt( dot(k,k) +16. -8.*length(k.xy) ) -1.5
                                    ) -i/150. ),
         O += max( 1.3/w * sin( vec4(1,2,3,1) + i*.5 ) , -length(k*k) )
       )

        for(

            k = vec3( (I+I-r.xy)/r.y *d, d - 10.),
            k.xz *= mat2( cos(sin(t/2.)*.785 + vec4(0,33,11,0))),

            k.y < -6.3
              ? k.y = -k.y -9.,
                m = .5 : m,

            p = k*.5, w = .01 ; w < .2 ; w += w )
            p.yz += cos( p.xy*.01 )
                  - abs( dot( sin(.02*p.z +.03*p.y +t+t + .3*p/w ), w+ Z ));

    O = tanh(O*O/1e6)*m;
}


/* Twigl Version

https://x.com/Jaenam97/status/1992945636178575564?s=20

*/

/* Not so golfed version

void mainImage( out vec4 O, vec2 I )
{
    float i,d,w,s,n,t=iTime,m=1.;
    vec3 p,k,r = iResolution;
    mat2 R = mat2(cos(sin(t/2.)*.785 +vec4(0,33,11,0)));

    for(O*=i; i++<1e2; O += max(sin(vec4(1,2,3,1)+i*.5)*1.3/w,-length(k*k))){

        p = vec3((I+I-r.xy)/r.y*d, d-10.);

        if(abs(p.x)>6.) break;

        p.xz *= R;

        if(p.y < -6.3) {
            p.y = -p.y-9.;
            m = .5;
        }

        k=p;

        for(p*=.5,n = .01; n < .2; n += n)
            p.yz += cos(p.xy*.01) - abs(dot(sin(.02*p.z+.03*p.y+2.*t + .3*p/n), p-p+n));

        s = length(k.xy)-4.;
        w = mix(sin(length(ceil(k*4.).z+k)), sin(length(p)-1.), smoothstep(5., 5.5, p.y));

        d += w =.01+.07*abs(max(w,sqrt(s*s+k*k).z-1.5)-i/150.);

    }

    O = tanh(O*O/1e6)*m;
}
*/

)"
            },

            // ---------------------------------------------------------------------------

            {
                "w10",  // https://www.shadertoy.com/view/lllSR2

                R"(

#define PI     3.1415926535897921284
#define REP    25
#define d2r(x) (x * PI / 180.0)
#define WBCOL  (vec3(0.5, 0.7,  1.7))
#define WBCOL2 (vec3(0.15, 0.8, 1.7))
#define ZERO   (min(iFrame,0))

float hash( vec2 p ) {
	float h = dot( p, vec2( 127.1, 311.7 ) );
	return fract( sin( h ) * 458.325421) * 2.0 - 1.0;
}

float noise( vec2 p ) {
	vec2 i = floor( p );
	vec2 f = fract( p );

	f = f * f * ( 3.0 - 2.0 * f );

	return mix(
		mix( hash( i + vec2( 0.0, 0.0 ) ), hash( i + vec2( 1.0, 0.0 ) ), f.x ),
		mix( hash( i + vec2( 0.0, 1.0 ) ), hash( i + vec2( 1.0, 1.0 ) ), f.x ),
		f.y
	);
}

vec2 rot(vec2 p, float a) {
	return vec2(
		p.x * cos(a) - p.y * sin(a),
		p.x * sin(a) + p.y * cos(a));
}

float nac(vec3 p, vec2 F, vec3 o) {
	const float R = 0.0001;
	p += o;
	return length(max(abs(p.xy)-vec2(F),0.0)) - R;
}


float by(vec3 p, float F, vec3 o) {
	const float R = 0.0001;
	p += o;
	return length(max(abs(mod(p.xy, 3.0))-F,0.0)) - R;
}


float recta(vec3 p, vec3 F, vec3 o) {
	const float R = 0.0001;
	p += o;
	return length(max(abs(p)-F,0.0)) - R;
}


float map1(vec3 p, float scale) {
	float G = 0.50;
	float F = 0.50 * scale;
	float t =  nac(p, vec2(F,F), vec3( G,  G, 0.0));
	t = min(t, nac(p, vec2(F,F), vec3( G, -G, 0.0)));
	t = min(t, nac(p, vec2(F,F), vec3(-G,  G, 0.0)));
	t = min(t, nac(p, vec2(F,F), vec3(-G, -G, 0.0)));
	return t;
}

float map2(vec3 p) {
	float t = map1(p, 0.9);
	//t = max(t, recta(p, vec3(1.0, 1.0, 0.02), vec3(0.0, 0.0, 0.0)));
    t = max(t, recta(p, vec3(1.0, 1.0, 0.02), vec3(0.0, 0.0, 0.0)));
	return t;
}


// http://glslsandbox.com/e#26840.0
float gennoise(vec2 p) {
	float d = 0.5;
	mat2 h = mat2( 1.6, 1.2, -1.2, 1.6 );

	float color = 0.0;
	for( int i = 0; i < 2; i++ ) {
		color += d * noise( p * 5.0 + iTime);
		p *= h;
		d /= 2.0;
	}
	return color;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    fragColor = vec4(0.0);
    for(int count = 0 ; count < 2; count++) {
        vec2 uv = -1.0 + 2.0 * ( fragCoord.xy / iResolution.xy );
        uv *= 1.4;
        uv.x += hash(uv.xy + iTime + float(count)) / 512.0;
        uv.y += hash(uv.yx + iTime + float(count)) / 512.0;
        vec3 dir = normalize(vec3(uv * vec2(iResolution.x / iResolution.y, 1.0), 1.0 + sin(iTime) * 0.01));
        dir.xz = rot(dir.xz, d2r(70.0));
        dir.xy = rot(dir.xy, d2r(90.0));
        vec3 pos    = vec3(-0.1 + sin(iTime * 0.3) * 0.1, 2.0 + cos(iTime * 0.4) * 0.1, -3.5);
        vec3  col   = vec3(0.0);
        float t     = 0.0;
        float M     = 1.002;
        float bsh   = 0.01;
        float dens  = 0.0;

        for(int i = ZERO ; i < REP * 24; i++) {
            float temp = map1(pos + dir * t, 0.6);
            if(temp < 0.2) {
                col += WBCOL * 0.005 * dens;
            }
            t += bsh * M;
            bsh *= M;
            dens += 0.025;
        }

        //windows
        t = 0.0;
        float y = 0.0;
        //for(int i = 0 ; i < REP * 50; i++)
        for(int i = ZERO ; i < REP; i++)
        {
            float temp = map2(pos + dir * t);
            if(temp < 0.025) {
                //col += WBCOL2 * 0.005;
                col += WBCOL2 * 0.5;
            }
            t += temp;
            y++;
        }
        col += ((2.0 + uv.x) * WBCOL2) + (y / (25.0 * 50.0));
        col += gennoise(dir.xz) * 0.5;
        col *= 1.0 - uv.y * 0.5;
        col *= vec3(0.05);
        col  = pow(col, vec3(0.717));
        fragColor += vec4(col, 1.0 / (t));
    }
    fragColor /= vec4(2.0);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "Re Fractal land by Kali",  // https://www.shadertoy.com/view/ltyXR1

                R"(
// "Fractal Cartoon" - former "DE edge detection" by Kali

// Cartoon-like effect using eiffies's edge detection found here:
// https://www.shadertoy.com/view/4ss3WB
// I used my own method previously but was too complicated and not compiling everywhere.
// Thanks to the suggestion by WouterVanNifterick.

// There are no lights and no AO, only color by normals and dark edges.

// update: Nyan Cat cameo, thanks to code from mu6k: https://www.shadertoy.com/view/4dXGWH


// The following block is needed for Clubber integration
#ifndef CLUBBER
vec4 iMusic[4];
const float iTransition = 1.0;
#define CLUBBER_R 0.0
#define CLUBBER_G 0.0
#define CLUBBER_B 0.0
#define CLUBBER_A 0.0
#endif
// Clubber end

#define MUSICRAYS 1.2 * (CLUBBER_A)
#define MUSICWAVES CLUBBER_R
#define MUSICMOD1 CLUBBER_G / 4.4
#define MUSICMOD2 CLUBBER_B / 6.6
#define MUSICSUNSIZE length(vec2(CLUBBER_R, CLUBBER_G ))
#define MUSICSUNSPIN length(vec2(CLUBBER_B, CLUBBER_A ))

//#define SHOWONLYEDGES
#define WAVES

#define RAY_STEPS 150

#define BRIGHTNESS 1.2
#define GAMMA 1.4
#define SATURATION .65


#define detail .001
#define t iTime*.5


const vec3 origin=vec3(-1.,.7,0.);
float det=0.0;


// 2D rotation function
mat2 rot(float a) {
	return mat2(cos(a),sin(a),-sin(a),cos(a));
}

// "Amazing Surface" fractal
vec4 formula(vec4 p) {
		p.xz = abs(p.xz + 1.)-abs(p.xz - 1.2 + MUSICMOD1) - p.xz;
		p.y-=.25;
		p.xy *= rot(radians(35.));
        p=p*2./clamp(dot(p.xyz,p.xyz),.2,min(1.05, 0.95 + MUSICMOD2));
	return p;
}

// Distance function
float de(vec3 pos) {
#ifdef WAVES
	pos.y+=sin(pos.z-t*6.+MUSICWAVES)*.15; //waves!
#endif
	float hid=0.;
	vec3 tpos=pos;
	tpos.z=abs(3.-mod(tpos.z,6.) );
	vec4 p=vec4(tpos,1.);
	for (int i=0; i<4; i++) {p=formula(p);}
	float fr=(length(max(vec2(0.),p.yz-1.5))-1.)/p.w;
	float ro=max(abs(pos.x+1.)-.3,pos.y-.35);
		  ro=max(ro,-max(abs(pos.x+1.)-.1,pos.y-.5));
	pos.z=abs(.25 - mod(pos.z - 2. * length(iMusic[2].xz),.5));
		  ro=max(ro,-max(abs(pos.z)-.2,pos.y-.3));
		  ro=max(ro,-max(abs(pos.z)-.01,-pos.y+.32));
	float d=min(fr,ro);
	return d;
}


// Camera path
vec3 path(float ti) {
	ti*=1.5;
	vec3  p=vec3(sin(ti),(1.-sin(ti*2.))*.5,-ti*5.)*.33;
	return p;
}

// Calc normals, and here is edge detection, set to variable "edge"

float edge=0.;
vec3 normal(vec3 p) {
	vec3 e = vec3(0.0,det*5.,0.0);

	float d1=de(p-e.yxx),d2=de(p+e.yxx);
	float d3=de(p-e.xyx),d4=de(p+e.xyx);
	float d5=de(p-e.xxy),d6=de(p+e.xxy);
	float d=de(p);
	edge=abs(d-0.5*(d2+d1))+abs(d-0.5*(d4+d3))+abs(d-0.5*(d6+d5));//edge finder
	edge=min(1.,pow(edge,.55)*15.);
	return normalize(vec3(d1-d2,d3-d4,d5-d6));
}





// Raymarching and 2D graphics

vec3 raymarch(in vec3 from, in vec3 dir)

{
	edge=0.;
	vec3 p, norm;
	float d=100.;
	float totdist=0.;
	for (int i=0; i<RAY_STEPS; i++) {
        if (d>det && totdist<25.0){
			p=from+totdist*dir;
			d=de(p);
			det=detail*exp(.13*totdist);
			totdist+=d;
    	} else {
    		break;
    	}
	}
	vec3 col=vec3(0.);
	p-=(det-d)*dir;
	norm=normal(p);

#ifdef SHOWONLYEDGES
	col=1.-vec3(edge); // show wireframe version
#else
	col=mix(vec3(edge), (1.-abs(norm))*max(0.,1.-edge*.8), iTransition); // set normal as color with dark edges
#endif
	totdist=clamp(totdist,0.,26.);
	dir.y-=.02;
	float sunsize= 7. - MUSICSUNSIZE; // responsive sun size
	float an=atan(dir.x,dir.y)+iTime * 1.5 + MUSICSUNSPIN; // angle for drawing and rotating sun
	float s=pow(clamp(1.0-length(dir.xy)*sunsize-abs(.2-mod(an,.4)),0.,1.),.1); // sun
	float sb=pow(clamp(1.0-length(dir.xy)*(sunsize-.2)-abs(.2-mod(an,.4)),0.,1.),.1); // sun border
	float sg=pow(clamp(1.0-length(dir.xy)*(sunsize - 4.5 - MUSICRAYS )-.5*abs(.2-mod(an,.4)),0.,1.),3.); // sun rays
	float y=mix(.45,1.2,pow(smoothstep(0.,1.,.75-dir.y),2.))*(1.-sb*.5); // gradient sky

	// set up background with sky and sun
	vec3 backg=vec3(0.5,0.,1.)*iTransition*((1.-s)*(1.-sg)*y+(1.-sb)*sg*vec3(1.,.8,0.15)*3.);
		 backg+=min(vec3(1.,.9,.1)*s,vec3(iTransition));
		 backg=max(backg,sg*vec3(1.,.9,.5));

	col=mix(vec3(1.,.9,.3)*iTransition,col,exp(-.004*totdist*totdist));// distant fading to sun color
	if (totdist>25.) col=backg; // hit background
	col=pow(col,vec3(GAMMA))*BRIGHTNESS;
	col=mix(vec3(length(col)),col,SATURATION);
#ifdef SHOWONLYEDGES
	col=1.-vec3(length(col));
#else
	col*=mix(vec3(length(col)), vec3(1.,.9,.85), iTransition);
#endif
	return col;
}

// get camera position
vec3 move(inout vec3 dir) {
	vec3 go=path(t);
	vec3 adv=path(t+.7);
	float hd=de(adv);
	vec3 advec=normalize(adv-go);
	float an=adv.x-go.x; an*=min(1.,abs(adv.z-go.z))*sign(adv.z-go.z)*.7;
	dir.xy*=mat2(cos(an),sin(an),-sin(an),cos(an));
    an=advec.y*1.7;
	dir.yz*=mat2(cos(an),sin(an),-sin(an),cos(an));
	an=atan(advec.x,advec.z);
	dir.xz*=mat2(cos(an),sin(an),-sin(an),cos(an));
	return go;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy*2.-1.;
	vec2 oriuv=uv;
	uv.y*=iResolution.y/iResolution.x;
	vec2 mouse=(iMouse.xy/iResolution.xy-.5)*3.;
	if (iMouse.z<1.) mouse=vec2(0.,-0.05);
	float fov=.9-max(0.,.7-iTime*.3);
	vec3 dir=normalize(vec3(uv*fov,1.));
	vec3 from=origin+move(dir);
	vec3 color=raymarch(from,dir);
	#ifdef BORDER
	color=mix(vec3(0.),color,pow(max(0.,.95-length(oriuv*oriuv*oriuv*vec2(1.05,1.1))),.3));
	#endif
	fragColor = vec4(color,1.);
}
)"
            },

            // ---------------------------------------------------------------------------

            {
                "h e e e l i x",  // https://www.shadertoy.com/view/4sVczV

                R"(

//#define ANOTHER_LEVEL


float guiLead = 0.6;
float guiInnerRatio = 0.4407892623709694;
float guiFocal = 3.;
float guiRotateModel = 0.4560833039600971;
float guiDebug = 0.6749066960348409;
float guiZipOffset = 30.;
float guiZipSize = 60.;
float guiZipSpeed = 3.3;
float guiZoom = 0.1;
float guiModelScale = 7.749066960348409;

mat4 cameraMatrix = mat4(
    -0.7063226699829102,
    0.7052236199378967,
    0.06198469549417496,
    0,
    -0.30620118975639343,
    -0.3832840919494629,
    0.8714323043823242,
    0,
    0.6382971405982971,
    0.5965006947517395,
    0.48660656809806824,
    0,
    0.14653973281383514,
    0.6211488246917725,
    0.13233166933059692,
    1
);

vec3 camPosition = vec3(0.14653973281383514, 0.6211488246917725, 0.13233166933059692);

float time;

#define PI 3.14159265359
#define HALF_PI 1.5707963267948966
#define TAU 6.28318530718
#define PHI 1.618033988749895


// --------------------------------------------------------
// Utils
// --------------------------------------------------------

#define saturate(x) clamp(x, 0., 1.)

// Rotate around a coordinate axis (i.e. in a plane perpendicular to that axis) by angle <a>.
// Read like this: R(p.xz, a) rotates "x towards z".
// This is fast if <a> is a compile-time constant and slower (but still practical) if not.
void pR(inout vec2 p, float a) {
    p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}

// http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
mat3 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat3(
        oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
        oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c
    );
}

float range(float vmin, float vmax, float value) {
  return (value - vmin) / (vmax - vmin);
}

float rangec(float a, float b, float t) {
    return clamp(range(a, b, t), 0., 1.);
}

float vmax(vec2 v) {
    return max(v.x, v.y);
}

float fBox2(vec2 p, vec2 b) {
    vec2 d = abs(p) - b;
    return length(max(d, vec2(0))) + vmax(min(d, vec2(0)));
}

// Repeat space along one axis. Use like this to repeat along the x axis:
// <float cell = pMod1(p.x,5);> - using the return value is optional.
float pMod1(inout float p, float size) {
    float halfsize = size*0.5;
    float c = floor((p + halfsize)/size);
    p = mod(p + halfsize, size) - halfsize;
    return c;
}

vec3 cartToPolar(vec3 p) {
    float x = p.x; // distance from the plane it lies on
    float a = atan(p.y, p.z); // angle around center
    float r = length(p.zy); // distance from center
    return vec3(x, a, r);
}

vec3 polarToCart(vec3 p) {
    return vec3(
        p.x,
        sin(p.y) * p.z,
        cos(p.y) * p.z
    );
}


// --------------------------------------------------------
// Helix
// https://www.shadertoy.com/view/MstcWs
// --------------------------------------------------------

vec2 closestPointOnRepeatedLine(vec2 line, vec2 point){

    // Angle of the line
    float a = atan(line.x, line.y);

    // Rotate space so we can easily repeat along
    // one dimension
    pR(point, -a);

    // Repeat to create parallel lines at the corners
    // of the vec2(lead, radius) polar bounding area
    float repeatSize = sin(a) * line.y;
    float cell = pMod1(point.x, repeatSize);

    // Rotate space back to where it was
    pR(point, a);

    // Closest point on a line
    line = normalize(line);
    float d = dot(point, line);
    vec2 closest = line * d;

    // Part 2 of the repeat, move the line along it's
    // tangent by the repeat cell
    vec2 tangent = vec2(line.y, -line.x);
    closest += cell * repeatSize * tangent;

    return closest;
}

// Closest point on a helix
vec3 closestHelix(vec3 p, float lead, float radius) {

    p = cartToPolar(p);
    p.y *= radius;

    vec2 line = vec2(lead, radius * PI * 2.);
    vec2 closest = closestPointOnRepeatedLine(line, p.xy);

    closest.y /= radius;
    vec3 closestCart = polarToCart(vec3(closest, radius));

    return closestCart;
}

// Cartesian to helix coordinates
void pModHelix(inout vec3 p, float lead, float radius) {
    vec3 closest = closestHelix(p, lead, radius);
    float helixAngle = atan((2. * PI * radius) / lead);
    vec3 normal = normalize(closest - vec3(closest.x,0,0));
    vec3 tangent = vec3(1,0,0) * rotationMatrix(normal, helixAngle);
    float x = (closest.x / lead) * radius * PI * 2.;
    float y = dot(p - closest, cross(tangent, normal));
    float z = dot(p - closest, normal);
    p = vec3(x, y, z);
}

float pModHelixScale(inout vec3 p, float lead, float innerRatio) {
    float radius = mix(.25, .5, innerRatio);
    pModHelix(p, lead, radius);
    float scale = mix(.5, 0., innerRatio);
    p /= scale;
    return 1. / scale;
}

float pModHelixUnwrap(inout vec3 p, float lead, float innerRatio, float t) {
    float radius = mix(.25, .5, innerRatio);
    float width = cos(asin(t));
    float adjust = (1. / width);
    float offset = ((.5 * adjust) - .5) * 7.;

    vec3 pp = p;
    pp.z -= radius;
    pR(pp.xy, PI * -.5);
    pp.x *= -1.;

    p.z += offset;
    radius += offset;
    pModHelix(p, lead, radius);

    p = mix(p, pp, rangec(.8, 1., t));

    float scale = mix(.5, 0., innerRatio);
    p /= scale;
    return 1. / scale;
}


// --------------------------------------------------------
// Modelling
// --------------------------------------------------------

struct Model {
    float dist;
    vec3 albedo;
    int id;
};

float anim(float t, float index) {
    float overlap = .5;
    float steps = 2.;
    float all = mix(steps, 1., overlap);
    float width = 1. / (all - 1.);
    float each = width * (1.- overlap);
    float start = index * each - width * .5;
    float end = start + width;
    return range(start, end, t);
}

float unzip(vec3 p, float t) {
    float size = guiZipSize;
    float speed = guiZipSpeed;

    t *= size * speed;

    if (sign(p.y) != sign(p.x)) {
        float radius = mix(.25, .5, guiInnerRatio);
        float scale = mix(.5, 0., guiInnerRatio);
        float factor = radius / scale * PI * 2.;
        t -= (factor - .5);
    }

    return range(size, 0., abs(p.x) + size - t);
}

void addPipe(inout float d, vec3 p, float scale, float tt) {

    float t = clamp(tt, 0., 1.);

    float boundry = 1.;
    float part;
    float separate = (
        rangec(0., boundry * .01, t) * .3 +
        rangec(boundry * .01, boundry, t) * .7
    );

    float round = rangec(.0, 1., t);

    part = fBox2(p.yz, vec2(mix(guiLead * 2., .5, separate), .5));
    part = mix(part, length(p.yz) - .5, round);
    part /= scale;

    d = mix(d, part, smoothstep(.0, .01, t));
}

void unzipHelixModel(inout float d, inout float scale, inout vec3 p, float lead, float innerRatio, float step, float invert) {
    float offset = guiZipOffset / lead;
    scale *= pModHelixScale(p, lead, innerRatio);
    p.x *= -1.;
    float t1 = unzip(p + vec3(offset,0,0) * invert, anim(time, step));
    addPipe(d, p, scale, t1);
}

Model map(vec3 p) {

    float part, d, t1, t2, t3, t4;
    float lead = guiLead;
    float innerRatio = guiInnerRatio;
    vec2 uv1, uv2, uv3;

    p /= guiModelScale;

    vec3 pp = p;

    d = 1e12;

    float s = mix(.5, 0., innerRatio);

    float scale = 1./pow(1./s, time);

    pR(p.xy, PI * -.5 * time + guiRotateModel * PI * 2.);

    p *= scale;
    p.z += .5;

    scale *= pModHelixUnwrap(p, lead, innerRatio, time);
    p.x *= -1.;
    scale *= pModHelixScale(p, lead, innerRatio);
    p.x *= -1.;

    #ifdef ANOTHER_LEVEL
        scale *= pModHelixScale(p, lead, innerRatio);
        p.x *= -1.;
    #endif

    d = min(d, length(p.yz) - .5);
    d /= scale;

    unzipHelixModel(d, scale, p, lead, innerRatio, -1., 1.);
    unzipHelixModel(d, scale, p, lead, innerRatio, 0., -1.);
    unzipHelixModel(d, scale, p, lead, innerRatio, 1., 1.);

    d *= guiModelScale;

    return Model(d, vec3(0), 1);
}


// --------------------------------------------------------
// Rendering
// --------------------------------------------------------

const float OUTLINE = .003; // Outline thickness
const float OUTLINE_BOUNDRY = .5; // Where to feather the inside/outside
const float MAX_TRACE_DISTANCE = 1.5; // max trace distance
const float INTERSECTION_PRECISION = .001; // precision of the intersection
const int NUM_OF_TRACE_STEPS = 100;
const float FUDGE_FACTOR = 1.; // Default is 1, reduce to fix overshoots

struct CastRay {
    vec3 origin;
    vec3 direction;
};

struct Ray {
    vec3 origin;
    vec3 direction;
    float len;
};

// Faster runtime
vec3 calcNormal(vec3 pos){
    vec3 eps = vec3(.001,0,0);
    vec3 nor = vec3(
        map(pos+eps.xyy).dist - map(pos-eps.xyy).dist,
        map(pos+eps.yxy).dist - map(pos-eps.yxy).dist,
        map(pos+eps.yyx).dist - map(pos-eps.yyx).dist );
    return normalize(nor);
}

// Faster compilation
const int NORMAL_STEPS = 6;
vec3 _calcNormal(vec3 pos){
    vec3 eps = vec3(.001,0,0);
    vec3 nor = vec3(0);
    float invert = 1.;
    for (int i = 0; i < NORMAL_STEPS; i++){
        nor += map(pos + eps * invert).dist * eps * invert;
        eps = eps.zxy;
        invert *= -1.;
    }
    return normalize(nor);
}

// https://www.shadertoy.com/view/lsKcDD
float softshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax )
{
    float res = 1.0;
    float t = mint;
    float ph = 1e10;

    for( int i=0; i<32; i++ )
    {
        float h = map( ro + rd*t ).dist;
        res = min( res, 10.0*h/t );
        t += h;
        if( res<0.0001 || t>tmax ) break;

    }
    return clamp( res, 0.0, 1.0 );
}

// https://www.shadertoy.com/view/Xds3zN
float calcAO( in vec3 pos, in vec3 nor )
{
    float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.01 + 0.12*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).dist;
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
}


// Adapted from https://www.shadertoy.com/view/Xds3zN
vec3 doLighting(vec3 pos, vec3 nor, vec3 rd) {

    vec3 col;
    vec3 up = normalize(vec3(1));

    // lighitng
    float occ = mix(calcAO( pos, nor ), 1., .8);
    vec3  lig = normalize(vec3(0,.2,1));
    float amb = clamp(dot(nor, up) * .5 + .5, 0., 1.);
    float dif = clamp( dot( nor, lig ), 0.0, 1.0 );
    float fre = pow( clamp(1.0+dot(nor,rd),0.0,1.0), 2.0 );
    vec3  hal = normalize( lig-rd );
    float spe = pow(clamp( dot( nor, hal ), 0.0, 1.0 ),16.0);

    vec3 cA = vec3(.7,.3,.9);
    vec3 cB = vec3(.4,.9,.8);
    vec3 cC = vec3(.7,0,.7);

    col = mix(cA, cB, rangec(.0, 1., dot(-rd, nor))); // need better ramp
    col = mix(col, vec3(.8,.5,1), rangec(.5, 1., dif) * .5);
    col += cC * rangec(.5, 1., dif) * .1;

    dif *= softshadow( pos, lig, 0.02, 2.5 ) * .9;

    vec3 lin = vec3(0);
    lin += .5 * dif;
    lin += .1 * spe * dif;
    lin += .2 * fre * occ;
    lin += .5 * amb * occ;
    lin += .4 * occ;
    col = col*lin;

    return col;
}

vec3 background;

void applyFog(inout vec3 color, vec3 pos) {
    float fog = length(camPosition - pos);
    fog = smoothstep(float(MAX_TRACE_DISTANCE) * .36, float(MAX_TRACE_DISTANCE), fog);
    color = mix(color, background, fog);
}

vec3 shadeSurface(vec3 pos, Ray ray) {

    if (ray.len > MAX_TRACE_DISTANCE) {
        return background;
    }

    vec3 normal = calcNormal(pos);

    vec3 color = doLighting(
        pos,
        normal,
        ray.direction
    );

    applyFog(color, pos);

    return color;
}

vec4 shadeOutline(vec3 pos, float t) {
    float alpha = smoothstep(0., OUTLINE_BOUNDRY, t);
    alpha -= smoothstep(OUTLINE_BOUNDRY, 1., t);
    alpha *= .5;
	vec3 color = vec3(0);
    applyFog(color, pos);
    return vec4(color, alpha);
}


// --------------------------------------------------------
// Ray Marching
// --------------------------------------------------------

vec3 raymarch(CastRay castRay){

    float currentDist = INTERSECTION_PRECISION * 2.0;
    float lastDist = currentDist;
    vec3 pos, lastPos = vec3(0);
    vec4 outline = vec4(0);

    Model model;
    Ray ray = Ray(castRay.origin, castRay.direction, 0.);

    for (int i = 0; i < NUM_OF_TRACE_STEPS; i++) {

        lastPos = pos;
        pos = ray.origin + ray.direction * ray.len;

        if (ray.len > MAX_TRACE_DISTANCE) {
            break;
        }

        if (currentDist < INTERSECTION_PRECISION) {
            break;
        }

        if (currentDist > lastDist && currentDist < OUTLINE) {

            float t = lastDist / OUTLINE;

            vec4 newOutline = shadeOutline(pos, t);
            float contribution = 1. - outline.a;
            outline.rgb = mix(outline.rgb, newOutline.rgb, contribution);
            outline.a += newOutline.a * contribution;

            if (t < OUTLINE_BOUNDRY) {
                pos = lastPos;
                break;
			}
        }

        model = map(pos);
        lastDist = currentDist;
        currentDist = model.dist;
        ray.len += currentDist * FUDGE_FACTOR;
    }

    vec3 color = mix(
        shadeSurface(pos, ray),
       	outline.rgb,
        outline.a
	);

    return color;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 p = (-iResolution.xy + 2.0*fragCoord.xy)/iResolution.y;

    vec3 bgA = vec3(.6,.5,.8) * .55;
    vec3 bgB = vec3(.7,.9,1.) * .5;
    background = mix(bgA, bgB, dot(p, normalize(vec2(.2,-.6))) * .5);
    //background = mix(vec3(.4,.3,.5) * .9, vec3(.6), -.2);

    time = iTime;
    time *= .6;
    time += .53;
    time = mod(time, 1.);

    float camDist = length(camPosition);

    mat4 camMat = cameraMatrix;
    float focalLength = guiFocal;
    vec3 rd = normalize(
        (vec4(p, -focalLength, 1) * camMat).xyz
    );

    vec3 color = raymarch(CastRay(camPosition, rd));

    vec2 uv = fragCoord/iResolution.xy;
    float vig = pow(
        16. * uv.x * uv.y * (1. - uv.x) * (1. - uv.y),
        0.075
    );
    color *= vec3(.9, .95, 1.) * vig * 1.1;

    color = mix(color, vec3(pow(length(color * .6), 2.)), .1);
    color *= 1.05;
    color = pow(color, vec3(1.2,1.3,1.2));

    fragColor = vec4(color,1.0);
}

)"
            },

            // ---------------------------------------------------------------------------

            /*
            {
                "vertexshaderart",  // https://www.vertexshaderart.com/art/oJEAooRzirpb8qcPe/

                R"(
/////////////////////////////////////////////////////////////////////
/// https://github.com/glslify/glsl-inverse/blob/master/index.glsl //
/////////////////////////////////////////////////////////////////////

mat3 inverse(mat3 m) {
  float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2];
  float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2];
  float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2];

  float b01 = a22 * a11 - a12 * a21;
  float b11 = -a22 * a10 + a12 * a20;
  float b21 = a21 * a10 - a11 * a20;

  float det = a00 * b01 + a01 * b11 + a02 * b21;

  return mat3(b01, (-a22 * a01 + a02 * a21), (a12 * a01 - a02 * a11),
              b11, (a22 * a00 - a02 * a20), (-a12 * a00 + a02 * a10),
              b21, (-a21 * a00 + a01 * a20), (a11 * a00 - a01 * a10)) / det;
}

//////////////////////////////////////////////
//// ShaderDough from @tdhooper in
//// https://www.shadertoy.com/view/4tc3WB
//////////////////////////////////////////////
// Disable to see more colour variety
#define SEAMLESS_LOOP
//#define COLOUR_CYCLE
#define PI 3.14159265359
#define PHI (1.618033988749895)
float t;
#define saturate(x) clamp(x, 0., 1.)
// --------------------------------------------------------
// http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
// --------------------------------------------------------
mat3 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat3(
        oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
        oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c
    );
}
// --------------------------------------------------------
// http://math.stackexchange.com/a/897677
// --------------------------------------------------------
mat3 orientMatrix(vec3 A, vec3 B) {
    mat3 Fi = mat3(
        A,
        (B - dot(A, B) * A) / length(B - dot(A, B) * A),
        cross(B, A)
    );
    mat3 G = mat3(
        dot(A, B),              -length(cross(A, B)),   0,
        length(cross(A, B)),    dot(A, B),              0,
        0,                      0,                      1
    );
    return Fi * G * inverse(Fi);
}
// --------------------------------------------------------
// HG_SDF
// https://www.shadertoy.com/view/Xs3GRB
// --------------------------------------------------------
#define GDFVector3 normalize(vec3(1, 1, 1 ))
#define GDFVector3b normalize(vec3(-1, -1, -1 ))
#define GDFVector4 normalize(vec3(-1, 1, 1))
#define GDFVector4b normalize(vec3(-1, -1, 1))
#define GDFVector5 normalize(vec3(1, -1, 1))
#define GDFVector5b normalize(vec3(1, -1, -1))
#define GDFVector6 normalize(vec3(1, 1, -1))
#define GDFVector6b normalize(vec3(-1, 1, -1))
#define GDFVector7 normalize(vec3(0, 1, PHI+1.))
#define GDFVector7b normalize(vec3(0, 1, -PHI-1.))
#define GDFVector8 normalize(vec3(0, -1, PHI+1.))
#define GDFVector8b normalize(vec3(0, -1, -PHI-1.))
#define GDFVector9 normalize(vec3(PHI+1., 0, 1))
#define GDFVector9b normalize(vec3(PHI+1., 0, -1))
#define GDFVector10 normalize(vec3(-PHI-1., 0, 1))
#define GDFVector10b normalize(vec3(-PHI-1., 0, -1))
#define GDFVector11 normalize(vec3(1, PHI+1., 0))
#define GDFVector11b normalize(vec3(1, -PHI-1., 0))
#define GDFVector12 normalize(vec3(-1, PHI+1., 0))
#define GDFVector12b normalize(vec3(-1, -PHI-1., 0))
#define GDFVector13 normalize(vec3(0, PHI, 1))
#define GDFVector13b normalize(vec3(0, PHI, -1))
#define GDFVector14 normalize(vec3(0, -PHI, 1))
#define GDFVector14b normalize(vec3(0, -PHI, -1))
#define GDFVector15 normalize(vec3(1, 0, PHI))
#define GDFVector15b normalize(vec3(1, 0, -PHI))
#define GDFVector16 normalize(vec3(-1, 0, PHI))
#define GDFVector16b normalize(vec3(-1, 0, -PHI))
#define GDFVector17 normalize(vec3(PHI, 1, 0))
#define GDFVector17b normalize(vec3(PHI, -1, 0))
#define GDFVector18 normalize(vec3(-PHI, 1, 0))
#define GDFVector18b normalize(vec3(-PHI, -1, 0))
#define fGDFBegin float d = 0.;
// Version with variable exponent.
// This is slow and does not produce correct distances, but allows for bulging of objects.
#define fGDFExp(v) d += pow(abs(dot(p, v)), e);
// Version with without exponent, creates objects with sharp edges and flat faces
#define fGDF(v) d = max(d, abs(dot(p, v)));
#define fGDFExpEnd return pow(d, 1./e) - r;
#define fGDFEnd return d - r;
// Primitives follow:
float fDodecahedron(vec3 p, float r) {
    fGDFBegin
    fGDF(GDFVector13) fGDF(GDFVector14) fGDF(GDFVector15) fGDF(GDFVector16)
    fGDF(GDFVector17) fGDF(GDFVector18)
    fGDFEnd
}
float fIcosahedron(vec3 p, float r) {
    fGDFBegin
    fGDF(GDFVector3) fGDF(GDFVector4) fGDF(GDFVector5) fGDF(GDFVector6)
    fGDF(GDFVector7) fGDF(GDFVector8) fGDF(GDFVector9) fGDF(GDFVector10)
    fGDF(GDFVector11) fGDF(GDFVector12)
    fGDFEnd
}
float vmax(vec3 v) {
    return max(max(v.x, v.y), v.z);
}
float sgn(float x) {
	return (x<0.)?-1.:1.;
}
// Plane with normal n (n is normalized) at some distance from the origin
float fPlane(vec3 p, vec3 n, float distanceFromOrigin) {
    return dot(p, n) + distanceFromOrigin;
}

// Box: correct distance to corners
float fBox(vec3 p, vec3 b) {
	vec3 d = abs(p) - b;
	return length(max(d, vec3(0))) + vmax(min(d, vec3(0)));
}
// Distance to line segment between <a> and <b>, used for fCapsule() version 2below
float fLineSegment(vec3 p, vec3 a, vec3 b) {
	vec3 ab = b - a;
	float t = saturate(dot(p - a, ab) / dot(ab, ab));
	return length((ab*t + a) - p);
}
// Capsule version 2: between two end points <a> and <b> with radius r
float fCapsule(vec3 p, vec3 a, vec3 b, float r) {
	return fLineSegment(p, a, b) - r;
}
// Rotate around a coordinate axis (i.e. in a plane perpendicular to that axis) by angle <a>.
// Read like this: R(p.xz, a) rotates "x towards z".
// This is fast if <a> is a compile-time constant and slower (but still practical) if not.
void pR(inout vec2 p, float a) {
    p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}
// Reflect space at a plane
float pReflect(inout vec3 p, vec3 planeNormal, float offset) {
    float t = dot(p, planeNormal)+offset;
    if (t < 0.) {
        p = p - (2.*t)*planeNormal;
    }
    return sign(t);
}
// Repeat around the origin by a fixed angle.
// For easier use, num of repetitions is use to specify the angle.
float pModPolar(inout vec2 p, float repetitions) {
	float angle = 2.*PI/repetitions;
	float a = atan(p.y, p.x) + angle/2.;
	float r = length(p);
	float c = floor(a/angle);
	a = mod(a,angle) - angle/2.;
	p = vec2(cos(a), sin(a))*r;
	// For an odd number of repetitions, fix cell index of the cell in -x direction
	// (cell index would be e.g. -5 and 5 in the two halves of the cell):
	if (abs(c) >= (repetitions/2.)) c = abs(c);
	return c;
}
// Repeat around an axis
void pModPolar(inout vec3 p, vec3 axis, float repetitions, float offset) {
    vec3 z = vec3(0,0,1);
	mat3 m = orientMatrix(axis, z);
    p *= inverse(m);
    pR(p.xy, offset);
    pModPolar(p.xy, repetitions);
    pR(p.xy, -offset);
    p *= m;
}
// --------------------------------------------------------
// knighty
// https://www.shadertoy.com/view/MsKGzw
// --------------------------------------------------------
int Type=5;
vec3 nc;
vec3 pbc;
vec3 pca;
void initIcosahedron() {//setup folding planes and vertex
    float cospin=cos(PI/float(Type)), scospin=sqrt(0.75-cospin*cospin);
    nc=vec3(-0.5,-cospin,scospin);//3rd folding plane. The two others are xz and yz planes
	pbc=vec3(scospin,0.,0.5);//No normalization in order to have 'barycentric' coordinates work evenly
	pca=vec3(0.,scospin,cospin);
	pbc=normalize(pbc);	pca=normalize(pca);//for slightly better DE. In reality it's not necesary to apply normalization :)

}
void pModIcosahedron(inout vec3 p) {
    p = abs(p);
    pReflect(p, nc, 0.);
    p.xy = abs(p.xy);
    pReflect(p, nc, 0.);
    p.xy = abs(p.xy);
    pReflect(p, nc, 0.);
}
float indexSgn(float s) {
	return s / 2. + 0.5;
}
bool boolSgn(float s) {
	return bool(s / 2. + 0.5);
}
float pModIcosahedronIndexed(inout vec3 p, int subdivisions) {
	float x = indexSgn(sgn(p.x));
	float y = indexSgn(sgn(p.y));
	float z = indexSgn(sgn(p.z));
    p = abs(p);
	pReflect(p, nc, 0.);

	float xai = sgn(p.x);
	float yai = sgn(p.y);
    p.xy = abs(p.xy);
	float sideBB = pReflect(p, nc, 0.);

	float ybi = sgn(p.y);
	float xbi = sgn(p.x);
    p.xy = abs(p.xy);
	pReflect(p, nc, 0.);

    float idx = 0.;

    float faceGroupAi = indexSgn(ybi * yai * -1.);
    float faceGroupBi = indexSgn(yai);
    float faceGroupCi = clamp((xai - ybi -1.), 0., 1.);
    float faceGroupDi = clamp(1. - faceGroupAi - faceGroupBi - faceGroupCi, 0., 1.);

    idx += faceGroupAi * (x + (2. * y) + (4. * z));
    idx += faceGroupBi * (8. + y + (2. * z));
    # ifndef SEAMLESS_LOOP
    	idx += faceGroupCi * (12. + x + (2. * z));
    # endif
    idx += faceGroupDi * (12. + x + (2. * y));

	return idx;
}
// --------------------------------------------------------
// IQ
// https://www.shadertoy.com/view/ll2GD3
// --------------------------------------------------------
vec3 pal( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d ) {
    return a + b*cos( 6.28318*(c*t+d) );
}

vec3 spectrum(float n) {
    return pal( n, vec3(0.5,0.5,0.5),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0),vec3(0.0,0.33,0.67) );
}
// --------------------------------------------------------
// tdhooper
// https://www.shadertoy.com/view/Mtc3RX
// --------------------------------------------------------
vec3 vMin(vec3 p, vec3 a, vec3 b, vec3 c) {
    float la = length(p - a);
    float lb = length(p - b);
    float lc = length(p - c);
    if (la < lb) {
        if (la < lc) {
            return a;
        } else {
            return c;
        }
    } else {
        if (lb < lc) {
            return b;
        } else {
            return c;
        }
    }
}
vec3 icosahedronVertex(vec3 p) {
    if (p.z > 0.) {
        if (p.x > 0.) {
            if (p.y > 0.) {
                return vMin(p, GDFVector13, GDFVector15, GDFVector17);
            } else {
                return vMin(p, GDFVector14, GDFVector15, GDFVector17b);
            }
        } else {
            if (p.y > 0.) {
                return vMin(p, GDFVector13, GDFVector16, GDFVector18);
            } else {
                return vMin(p, GDFVector14, GDFVector16, GDFVector18b);
            }
        }
    } else {
        if (p.x > 0.) {
            if (p.y > 0.) {
                return vMin(p, GDFVector13b, GDFVector15b, GDFVector17);
            } else {
                return vMin(p, GDFVector14b, GDFVector15b, GDFVector17b);
            }
        } else {
            if (p.y > 0.) {
                return vMin(p, GDFVector13b, GDFVector16b, GDFVector18);
            } else {
                return vMin(p, GDFVector14b, GDFVector16b, GDFVector18b);
            }
        }
    }
}
vec4 icosahedronAxisDistance(vec3 p) {
    vec3 iv = icosahedronVertex(p);
    vec3 originalIv = iv;

    vec3 pn = normalize(p);
    pModIcosahedron(pn);
    pModIcosahedron(iv);

    float boundryDist = dot(pn, vec3(1, 0, 0));
    float boundryMax = dot(iv, vec3(1, 0, 0));
    boundryDist /= boundryMax;

    float roundDist = length(iv - pn);
    float roundMax = length(iv - vec3(0, 0, 1.));
    roundDist /= roundMax;
    roundDist = -roundDist + 1.;

    float blend = 1. - boundryDist;
	blend = pow(blend, 6.);

    float dist = mix(roundDist, boundryDist, blend);

    return vec4(originalIv, dist);
}
void pTwistIcosahedron(inout vec3 p, float amount) {
    vec4 a = icosahedronAxisDistance(p);
    vec3 axis = a.xyz;
    float dist = a.a;
    mat3 m = rotationMatrix(axis, dist * amount);
    p *= m;
}
struct Model {
    float dist;
    vec3 colour;
    float id;
};
Model fInflatedIcosahedron(vec3 p, vec3 axis) {
    float d = 1000.;

    # ifdef SEAMLESS_LOOP
    	// Radially repeat along the rotation axis, so the
    	// colours repeat more frequently and we can use
    	// less frames for a seamless loop
    	pModPolar(p, axis, 3., PI/2.);
	# endif

    // Slightly inflated icosahedron
    float idx = pModIcosahedronIndexed(p, 0);
    d = min(d, dot(p, pca) - .9);
    d = mix(d, length(p) - .9, .5);

    // Colour each icosahedron face differently
    # ifdef SEAMLESS_LOOP
    	if (idx == 3.) {
    		idx = 2.;
    	}
    	idx /= 10.;
   	# else
    	idx /= 20.;
    # endif
    # ifdef COLOUR_CYCLE
    	idx = mod(idx + t*1.75, 1.);
    # endif
    vec3 colour = floor(spectrum(idx) * 6.) / 6. ;

    d *= .6;
	return Model(d, colour, 1.);
}
void pTwistIcosahedron(inout vec3 p, vec3 center, float amount) {
    p += center;
    pTwistIcosahedron(p, 5.5);
    p -= center;
}
Model model(vec3 p) {
    float rate = PI/6.;
    vec3 axis = pca;

    vec3 twistCenter = vec3(0);
    twistCenter.x = cos(t * rate * -3.) * .3;
	twistCenter.y = sin(t * rate * -3.) * .3;

	mat3 m = rotationMatrix(
        reflect(axis, vec3(0,1,0)),
        t * -rate
   	);
    p *= m;
    twistCenter *= m;

    pTwistIcosahedron(p, twistCenter, 5.5);

	return fInflatedIcosahedron(p, axis);
}
// The MINIMIZED version of https://www.shadertoy.com/view/Xl2XWt
const float MAX_TRACE_DISTANCE = 30.0;           // max trace distance
const float INTERSECTION_PRECISION = 0.001;        // precision of the intersection
const int NUM_OF_TRACE_STEPS = 100;
vec2 opU( vec2 d1, vec2 d2 ){
    return (d1.x<d2.x) ? d1 : d2;
}
Model map( vec3 p )
{
    return model(p*2.);
}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

//////////////////////////////////////////////
//https://www.vertexshaderart.com/art/DSH7PskktA2rGgZ6F
//////////////////////////////////////////////

vec3 meshSqhere(in float id)
{
    float split = floor(sqrt(floor(vertexCount/6.0)));
	split = floor(split/2.0);
	float d = split * 2.0;
    float n = floor(id / 6.0);
    vec2 q = vec2(mod(n,d), mod(floor(n/d),d));
    vec2 a = q+0.5-split;
    float s = sign(a.x*a.y);
    float c = abs(3.0 - mod(id, 6.0));
    vec2 uv = vec2(mod(c, 2.0), abs(step(0.0, s)-floor(c / 2.0)));
    uv = (uv+q)/split -1.0;
    if ( uv.x > abs(uv.y)) uv.y -= (uv.x - abs(uv.y))*s;
    if (-uv.x > abs(uv.y)) uv.y -= (uv.x + abs(uv.y))*s;
    if ( uv.y > abs(uv.x)) uv.x -= (uv.y - abs(uv.x))*s;
    if (-uv.y > abs(uv.x)) uv.x -= (uv.y + abs(uv.x))*s;
    return normalize(vec3(uv , 0.8*(1.0-pow(max(abs(uv.x),abs(uv.y)),2.0)) *s));
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

vec3 getPoint(float vId)
{
	vec3 p = meshSqhere(vertexId);

	float d = 0.;
	vec3 rd = normalize(p);
	vec3 ro = rd * -3.;
	for (int i=0;i<5;i++)
	{
		d += map(ro + rd * d).dist;
	}

	return ro + rd * d;
}

vec3 getNormal( vec3 p, float prec )
{
    vec2 e = vec2( prec, 0. );
    vec3 n = vec3(
        map(p+e.xyy).dist - map(p-e.xyy).dist,
        map(p+e.yxy).dist - map(p-e.yxy).dist,
        map(p+e.yyx).dist - map(p-e.yyx).dist );
    return normalize(n);
}

void main()
{
	initIcosahedron();
    t = time * 0.8;
  	//t = 0.;

    vec3 p = getPoint(vertexId);

  	vec3 ro = vec3(0,0,-3.);
    float d = length(ro-p);

  	gl_PointSize = 3.;//8.-d;

	vec3 rd = vec3(0,0,-1.);
	vec3 ld = normalize(vec3(1.,0,-1.));
	vec3 n = getNormal(p, 0.0001);
	float sd = map(p + n).dist;

	float diff = max(dot(n, ld), 0.);
    float spec = pow(max(dot( reflect(-ld, n), rd), 0.), 2.);
	vec3 col = map(p).colour * 0.8 + diff * 0.2 + spec * 0.8;
  	col /= sd;

  	float screenZ = -0.;
	float eyeZ = -4.5;
	p.xy *= (eyeZ - screenZ) / (p.z - eyeZ);
	p.x /= resolution.x / resolution.y;

	gl_Position = vec4(p, 1);

  	//v_color = vec4(0.);
    //if (p.z < 0.)
	 	v_color = vec4(clamp(col,0.,1.), 1);
}
)"
            },
            */

            // ---------------------------------------------------------------------------

            {
                "New_Shader",

                DEFAULT_FRAGMENT_SHADER_CODE
            }

            // ---------------------------------------------------------------------------

            /* vvvvvvvvvv copy this to add next shader (begin at semicolon): vvvvvvvvvvvvv
            ,

            // ---------------------------------------------------------------------------

            {
                "Name",

                R"(Code)"
            }
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

        }; // end of 'ShaderPreset presets[]'

        // constructs | initializes a new juce::Array from a C-array
        return juce::Array<ShaderPreset>(presets, numElementsInArray(presets));
    } // end getPresets()

    // ===========================================================================

private:

    static constexpr const char* DEFAULT_FRAGMENT_SHADER_CODE = R"(
void main()
{
    vec4 colour1 = vec4 (1.0, 0.0, 0.0, 1.0);
    gl_FragColor = pixelAlpha * colour1;
}
)";

    static constexpr const char* DEFAULT_VERTEX_SHADER_CODE = R"(
varying vec2 vUv;

void main() {
    vUv = uv;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
)";

    // ===========================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaderPresets)

}; // end of class
