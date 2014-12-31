#version 330 core

const float inverseAspectRatio = 3.0/4.0;

layout(location = 0) in vec4 vPos;

uniform vec2 mapCoords;
uniform sampler2D dataTexture;
uniform mat4 MVP;

void main() {
    vec4 pos = vec4(vPos.xyz, 1.0);

    gl_Position = MVP * pos;
}
