#version 150

uniform float time;
uniform vec2 resolution;
uniform float amp;
uniform float size;
uniform sampler2D spectrum1;

in VertexData
{
    vec4 v_position;
    vec3 v_normal;
    vec2 v_texcoord;
} inData;

out vec4 fragColor;

float spectrumValue(float value)
{
    float x = mod(value, 16.) * (1./16.);
    float y = value/16. * (1./16.);
    return texture(spectrum1, vec2(x, y)).r;
}

void main(void)
{
    vec2 uv = -1. + 2. * inData.v_texcoord;
    float v = amp * spectrumValue(1. + abs(uv.x) * size);
    float col = float(v >= abs(uv.y));

    fragColor = vec4(vec3(col), 1.);
}
