#version 330 core

const float inverseAspectRatio = 3.0/4.0;

layout(location = 0) in vec2 vPos;

uniform float zoomLevel;
uniform vec2 mapOffset;

void main() {
    gl_Position = vec4(vPos + mapOffset, 0.0, 1.0);

    gl_Position.xy *= zoomLevel * inverseAspectRatio;
}
