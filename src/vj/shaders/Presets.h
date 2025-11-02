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

            {
                "State of the art",

                R"(
// Created by David Gallardo - xjorma/2020
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0

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
