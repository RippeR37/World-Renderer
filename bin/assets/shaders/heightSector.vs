#version 330 core

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;

out vec4 vColorSmooth;

vec2 uWindow = vec2(800.0, 600.0);

vec2 translateToPixels(vec2 xy, vec2 windowSize) {
    return ((xy * 2.0) / windowSize) - vec2(1.0);
}

void main() {
    gl_Position = vPos * vec4(1.0/800.0, 1.0/600.0, 1.0, 1.0) - vec4(1, 1, 0.0, 0.0);


    vColorSmooth = vColor;
}
