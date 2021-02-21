#version 400
layout (location = 0) in vec3 aPos;
// layout (location = 1) in ivec4 aNormal; // is actually an INT_10_10_10_2
// layout (location = 2) in uvec2 aTexCoord;

// out uvec2 nTexCoord;

// Something to do with Voxel Lighting in the future
// attribute lowp uint lightLevel;
// varying float brightness;

void main() 
{
    // vec3 normal = clamp(aNormal.xyz * 0.001957, -1.0, 1.0); // Magic numbers!
    // nTexCoord = aTexCoord;

    gl_Position = vec4(aPos, 1.0);
    // brightness = 1.0f / (16u - lightLevel);
}