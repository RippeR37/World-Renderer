#version 330 core

layout(location = 0) in vec2 vPos;

out vec4 vColor;

uniform mat4 MVP;
uniform vec2 mapCoords;
uniform sampler2D dataTexture;

const float EARTH_RADIUS = 6371.0f; // in meters, mean
const float HEIGHT_FACTOR = 2.0f;

vec4 getSphereCoords(vec2 sectorOffset, float height) {
    vec2 angles = mapCoords + sectorOffset;

    float phi   = radians(angles.x);
    float theta = radians(angles.y);
    float radius = EARTH_RADIUS + height;

    return vec4(
        radius * cos(theta) * cos(phi),
        radius * cos(theta) * sin(phi),
        radius * sin(theta),
        1.0f
    );
}

vec4 getHeightColor(float ht) {
    vec4 result;

    if      (ht < 0  )   result = vec4(0.0,                0.0,               1.0, 1.0);
    else if (ht < 500)   result = vec4(0.0,                ht / 500.0,        0.0, 1.0);
    else if (ht < 1000)  result = vec4(ht / 500.0 - 1.0,   1.0,               0.0, 1.0);
    else if (ht < 2000)  result = vec4(1.0,                2.0 - ht / 1000.0, 0.0, 1.0);
    else                 result = vec4(1.0,                1.0,               1.0, 1.0);

    return result;
}

void main() {
    float height = texture(dataTexture, vec2(vPos.x, 1.0 - vPos.y)).r * 32767.0;
    vec4 finalSpherePos = getSphereCoords(vPos, height * 0.001f * HEIGHT_FACTOR);

    vColor = getHeightColor(height);

    gl_Position = MVP * finalSpherePos;
}
