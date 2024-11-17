#version 450 core
layout (location = 0) in vec4 in_vertex;
layout (location = 1) in vec2 in_pos;
layout (location = 2) in vec3 in_colour;
layout (location = 3) in int in_glyph_index;

out vec3 fColour;
flat out int glyphIndex;
out vec2 texCoords;

uniform mat4 viewProjection;

void main() {
    mat4 model;
	model[0][0] = 1;
	model[1][1] = 1;
	model[2][2] = 1;
	model[3] = vec4(in_pos, 0.0, 1.0);

    gl_Position = viewProjection * model * vec4(in_vertex.xy, 0.0, 1.0);
    fColour = in_colour;
    glyphIndex = in_glyph_index;
    texCoords = in_vertex.zw;
}