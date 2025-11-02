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
                "Print Text in Shaders",

                R"(
/*   ### How to use this shader ? ###

   = Setup =
   0. Copy the content of the Common Tab inside your shader
   1. Make sure the FONT_TEXTURE #define is set to the iChannel
      containing the alphabet texture

   = Declare String =
   2. Use makeStr to declare a new string (needs to be done outside any function)
   3. Write your text using _ before each char, and __ for spaces
   4. Finish your string with the _end keyword

       makeStr(printAnother) _A _n _o _t _h _e _r __ _E _x _a _m _p _l _e    _end

   = Print String =
   5. Call the new function by passing it your uvs. It returns a grayscale value.

       finalCol += printAnother(uv);

   Note that by default a character has a height of 1 (which is full height if
   the coordinates are normalized). You are responsible for scaling/offsetting
   the uvs to control the text placement before calling the function.


   ### Characters available ###

   uppercase: _A _B _C ...
   lowercase: _a _b _c ...
   digits   : _0 _1 _2 ...
   special  : _EXC _QUOT ... (see Common)


   ### Javascript string generator helper ###

   To make things even easier, I've made a tiny javascript helper function that you
   can use to convert strings to the right _F _o _r _m _a _t !
   (I've written it in the comments of this shader)


   ### Special functions ###

   _dig(i)       : write a specific digit [i ranges between 0-9]
   _dec(i, prec) : write a floating point number [prec: number of decimals to print]
   _ch(i)        : Write an uppercase character [i ranges between 0-25]

   To use these special functions, you need to pass additional parameters into makeStr:

   "makeStr1i" allows you to pass 1 int parameter named "i" :

   makeStr1i(test) _dig(i) _end
   test(uv, 5);

   "makeStr1f" allows you to pass 1 float parameter named "i":

   makeStr1f(test) _dec(i, 3) _end
   test(uv, 5.);

   You can also create your own makeStr with any parameter type! (see below)


   ### Help me optimize it! ###

   The _dec() function is only for debug purposes, I've never used it in a published shader.
   It's *very* intensive and can have rounding issues (ie 21.999 when the float is 22.),
   however it's done with a pretty naive approach so if you can come up with a better one
   I'd be glad! The function is defined at the very end of this tab.
*/

/// SETTINGS ///

// Set to the iChannel containing the alphabet texture
#define FONT_TEXTURE iChannel0

// Horizontal character spacing (default: 0.5)
#define CHAR_SPACING 0.44


/// STRING CREATION ///

// Create a basic string
#define makeStr(func_name) float func_name(vec2 u) { _print

// Create a string with an int parameter
#define makeStr1i(func_name) float func_name(vec2 u, int i) { _print

// Create a string with a float parameter
#define makeStr1f(func_name) float func_name(vec2 u, float i) { _print

// Create a string with two floats parameter
#define makeStr2f(func_name) float func_name(vec2 u, float i, float j) { _print

// ... Or create your own strings with any parameters
#define makeStrXX(func_name) float func_name(vec2 u, ...) { _print

// Terminate a string
#define _end    ); return d; }


/// SPECIAL FUNCTIONS ///

// Dynamic uppercase character
// i: [0-25]
#define _ch(i)  _ 65+int(i)

// Dynamic digit
// i: [0-9]
#define _dig(i) _ 48+int(i)

// Floating point debug
// x:   value to print
// dec: number of decimal places to print
#define _dec(x, dec) ); d += _decimal(FONT_TEXTURE, u, x, dec); (0


/// SPECIAL CHARACTERS ///

// Space
#define __    ); u.x -= CHAR_SPACING; (0

#define _EXC  _ 33 // " ! "
#define _DBQ  _ 34 // " " "
#define _NUM  _ 35 // " # "
#define _DOL  _ 36 // " $ "
#define _PER  _ 37 // " % "
#define _AMP  _ 38 // " & "
#define _QUOT _ 39 // " ' "
#define _LPR  _ 40 // " ( "
#define _RPR  _ 41 // " ) "
#define _MUL  _ 42 // " * "
#define _ADD  _ 43 // " + "
#define _COM  _ 44 // " , "
#define _SUB  _ 45 // " - "
#define _DOT  _ 46 // " . "
#define _DIV  _ 47 // " / "
#define _COL  _ 58 // " : "
#define _SEM  _ 59 // " ; "
#define _LES  _ 60 // " < "
#define _EQU  _ 61 // " = "
#define _GRE  _ 62 // " > "
#define _QUE  _ 63 // " ? "
#define _AT   _ 64 // " @ "
#define _LBR  _ 91 // " [ "
#define _ANTI _ 92 // " \ "
#define _RBR  _ 93 // " ] "
#define _UND  _ 95 // " _ "


/// CHARACTER DEFINITIONS ///

// Uppercase letters (65-90)
#define _A _ 65
#define _B _ 66
#define _C _ 67
#define _D _ 68
#define _E _ 69
#define _F _ 70
#define _G _ 71
#define _H _ 72
#define _I _ 73
#define _J _ 74
#define _K _ 75
#define _L _ 76
#define _M _ 77
#define _N _ 78
#define _O _ 79
#define _P _ 80
#define _Q _ 81
#define _R _ 82
#define _S _ 83
#define _T _ 84
#define _U _ 85
#define _V _ 86
#define _W _ 87
#define _X _ 88
#define _Y _ 89
#define _Z _ 90

// Lowercase letters (97-122)
#define _a _ 97
#define _b _ 98
#define _c _ 99
#define _d _ 100
#define _e _ 101
#define _f _ 102
#define _g _ 103
#define _h _ 104
#define _i _ 105
#define _j _ 106
#define _k _ 107
#define _l _ 108
#define _m _ 109
#define _n _ 110
#define _o _ 111
#define _p _ 112
#define _q _ 113
#define _r _ 114
#define _s _ 115
#define _t _ 116
#define _u _ 117
#define _v _ 118
#define _w _ 119
#define _x _ 120
#define _y _ 121
#define _z _ 122

// Digits (48-57)
#define _0 _ 48
#define _1 _ 49
#define _2 _ 50
#define _3 _ 51
#define _4 _ 52
#define _5 _ 53
#define _6 _ 54
#define _7 _ 55
#define _8 _ 56
#define _9 _ 57


/// Internal functions ///

// Start
#define _print  float d = 0.; (u.x += CHAR_SPACING

// Update
#define _       ); u.x -= CHAR_SPACING; d += _char(FONT_TEXTURE, u,

// Print character
float _char(sampler2D s, vec2 u, int id) {
    vec2 p = vec2(id%16, 15. - floor(float(id)/16.));
         p = (u + p) / 16.;
         u = step(abs(u-.5), vec2(.5));
    return texture(s, p).r * u.x * u.y;
}

// Floating point debug
float _decimal(sampler2D FONT_TEXTURE, inout vec2 u, float n, int decimals) {
    float d = 0., N = 1.; // d is the final color, N the number of digits before the decimal

    if (n < 0.) {  // If the number is negative
        n *= -1.;  // Make it positive
        (0 _SUB ); // Print a minus sign
    }

    // Calculate the number of digits before the decimal point
    for (float x = n; x >= 10.; x /= 10.) N++;

    // Print the digits before the decimal point
    for (float i = 0.; i < N; i++) {
        float magnitude = pow(10., N-i-1.);
        float leftDigit = floor(n / magnitude);
        n -= leftDigit * magnitude;

        (0 _dig(leftDigit) );
    }

    (0 _DOT ); // Print a dot

    // Print the digits after the decimal point
    for (int i = 0; i < decimals; i++) {
        float firstDecimal = floor((n - floor(n)) * 10.);
        n *= 10.;

        (0 _dig(firstDecimal) );
    }

    return d;
}

/*
   [ A new version is available that greatly improves performance! ]

         ==>   https://www.shadertoy.com/view/43t3WX   <==


   It can be hard manipulate the definition and drawing of strings in shaders, it often
   relies on arrays of numbers that are tidious to update manually and are pretty
   obfuscated compared to the original text.

   This shader tries to provide an easier framework for string manipulation where you
   can simply declare a string like this:

       makeStr(printHello) _H _e _l _l _o  __  _w _o _r _l _d    _end

   And directly use it in any function (More info in the "Common" tab):

       finalCol += printHello(uv);
*/

// String declarations
makeStr(printStr1)      _E _a _s _y __ _w _a _y __ _t _o __ _p _r _i _n _t __ _t _e _x _t __  _i _n __ _S _h _a _d _e _r _s _EXC _end
makeStr(printNum)       _P _r _i _n _t __ _S _t _a _t _i _c __ _D _i _g _i _t _s __ _2 _0 _2 _3                                  _end
makeStr1i(printDynNum)  _A _n _d __ _D _y _n _a _m _i _c __ _D _i _g _i _t _s __ _dig(i)                                         _end
makeStr1f(printDecNum)  _D _e _c _i _m _a _l __ _N _u _m _b _e _r _s __ _T _o _o __ _dec(i, 3)                                   _end
makeStr2f(printDynChar) _S _u _p _p _o _r _t _s __ _D _y _n _a _m _i _c __ _C _h _a _r _a _c _t _e _r _s __ _ch(i) __ _ch(j)     _end
makeStr(printSpecial)   _A _n _d __ _e _v _e _n __ _S _p _e _c _i _a _l __ _C _h _a _r _s __ _EXC _NUM _MUL _DIV _AT _UND        _end

makeStr(printLong)      _W _o _r _k _s __ _f _o _r __ _a _l _l __ _t _e _x _t __ _s _i _z _e _s
                        _COM __ _e _v _e _n __ _t _h _e __ _l _o _n _g _e _r __ _o _n _e _s __
                        _i _f __ _y _o _u __ _s _c _a _l _e __ _t _h _e __ _u _v _s _EXC                                         _end

// Color declarations
#define RED     vec3( 1,.3,.4)
#define GREEN   vec3(.2, 1,.4)
#define BLUE    vec3(.2,.8, 1)
#define RAINBOW abs(cos(uv.x + vec3(5,6,1)))

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    // Normalized uv coordinates
    vec2 uv = fragCoord / iResolution.y;

    // Final color
    vec3 col = vec3(0);

    // Font Size (higher values = smaller font)
    const float font_size = 9.;

    uv *= font_size;        // Scale font with font_size
    uv.y -= font_size - 1.; // Start drawing from the top


    col += RED * printStr1(uv);                       // "Easy way to print text in shaders"
    uv.y += 2.; // Move the cursor down

    col += GREEN * printNum(uv);                      // "Static Digits"
    uv.y++;

    col += GREEN/.6 * printDynNum(uv, int(iTime)%10); // "Dynamic Digits"
    uv.y++;

    col += GREEN/.4 * printDecNum(uv, iTime);         // "Decimal Numbers"
    uv.y+=2.;

    col += BLUE * printDynChar(uv, mod(iTime, 26.), mod(iTime*2., 26.)); // "Dynamic Characters"
    uv.y++;

    col += RAINBOW  * printSpecial(uv);                // "Special Characters"
    uv.y+=.7;

    uv *= 2.; // Multiply uv by 2 to make it smaller

    col += printLong(uv);                              // "Works for all text sizes..."

    fragColor = vec4(col, 1.);
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
