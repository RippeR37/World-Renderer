#version 330 core

const float inverseAspectRatio = 3.0/4.0;

layout(location = 0) in vec2 vPos;

out vec2 vTexCoords;

uniform vec2 mapCoords;
uniform sampler2D dataTexture;

void main() {
    gl_Position.xyz = getSpherePosition(vPos);
    gl_Position.w   = 1.0; 

    vTexCoords = vPos;
}
