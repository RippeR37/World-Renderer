#version 330 core

const float inverseAspectRatio = 3.0/4.0;

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 vTex;

out vec2 vTexCoords;

uniform float zoomLevel;
uniform vec2 mapOffset;
uniform vec2 mapCoords;

void main() {
    float oryginalPosition = mapCoords.x + vPos.x;
    float movedPosition = oryginalPosition * cos(radians(mapCoords.y + vPos.y));

    gl_Position = vec4(vPos + mapOffset, 0.0, 1.0);

    gl_Position.x -= oryginalPosition - movedPosition;
    
    gl_Position.xy *= zoomLevel * inverseAspectRatio;



    //gl_Position.x *= cos(radians(mapCoords.y + vPos.y));

    vTexCoords = vTex;
}
