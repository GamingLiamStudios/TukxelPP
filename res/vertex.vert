#version 400
layout (location = 0) in vec3 aPos;
// layout (location = 1) in ivec4 aNormal; // is actually an INT_10_10_10_2
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

// Something to do with Voxel Lighting in the future
// attribute lowp uint lightLevel;
// varying float brightness;

void main() 
{
    // vec3 normal = clamp(aNormal.xyz * 0.001957, -1.0, 1.0); // Magic numbers!
    texCoord = vec2(aTexCoord.x, aTexCoord.y);

    gl_Position = vec4(aPos, 1.0);
    // brightness = 1.0f / (16u - lightLevel);
}