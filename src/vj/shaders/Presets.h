//
// Created by thorsten on 30.10.2025.
//
#pragma once

#include <JuceHeader.h>
#include "../ShaderEditor.h"

class ShaderPresets {
public:

    struct ShaderPreset {
        const char *name;
        const char *fragmentShader;
    };

    static juce::Array<ShaderPreset> getPresets() {
#define SHADER_2DDEMO_HEADER \
    "/*  This demo shows the use of the OpenGLGraphicsContextCustomShader,\n" \
    "    which allows a 2D area to be filled using a GL shader program.\n" \
    "\n" \
    "    Edit the shader program below and it will be \n" \
    "    recompiled in real-time!\n" \
    "*/\n\n"

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
                "ShaderToy Tutorial",

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
                "Raymarching Tutorial",

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
                "Boing Ball (320x200)",

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
                "Amiga Boing Ball Demo",

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
            /*
            {
                "State of the art",

                // L:\WORKSPACES\AUDIO_WS\Projects\VJi\src\vj\shaders/Presets.h(538):
                // error C2026: Zeichenfolge zu lang, Zeichen am Ende wurden entfernt
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
                "New_Shader",

                DEFAULT_FRAGMENT_SHADER_CODE
            }

            // ---------------------------------------------------------------------------

            /* copy this to add next shader (begin at semicolon): vvvvvvvvvvvvvvvvvvvvvvvv
            ,

            // ---------------------------------------------------------------------------

            {
                "Name",

                R"(Code)"
            }
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

        }; // end presets[]

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

}; // end of class
