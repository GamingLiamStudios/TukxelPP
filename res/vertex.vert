#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aNormal;
layout (location = 2) in vec2 texCoord;
attribute uint lightLevel;

varying float brightness;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    brightness = 1.0f / (16u - lightLevel);
}