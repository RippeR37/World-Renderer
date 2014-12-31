#version 330 core

in vec2 vTexCoords;

out vec4 color;

uniform sampler2D dataTexture;

///////////////////////////////

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
    float height = texture(dataTexture, vTexCoords).r * 32767.0;

    color = getHeightColor(height);
}