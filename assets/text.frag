#version 450 core
#extension GL_EXT_texture_array : enable

in vec3 fColour;
flat in int glyphIndex;
in vec2 texCoords;
out vec4 frag_colour;

uniform sampler2DArray tex;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2DArray(tex, vec3(texCoords, glyphIndex)).r);
    frag_colour = vec4(fColour, 1.0) * sampled;
}