#version 400
// in uvec2 nTexCoord;

out vec4 FragColor;

// varying float brightness; // Something to do with Voxel Lighting in the future

void main() {
    // Some texture related calls
    // float mipmapLevel = textureQueryLod(texture, textureCoord).x;
    // ivec2 textureLOD_size = textureSize(texture, mipmapLevel);
    // vec2 texCoord = nTexCoord / textureLOD_size;

    // float light = max(brightness, 0.07f);
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 