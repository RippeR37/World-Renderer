#version 330 core

in vec4 vColorSmooth;
out vec4 color;

void main() {
    color = vColorSmooth;
}