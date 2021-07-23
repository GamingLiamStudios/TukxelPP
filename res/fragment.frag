#version 400
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture;

// varying float brightness; // Something to do with Voxel Lighting in the future

void main() 
{
    // float light = max(brightness, 0.07f);
    FragColor = texture(texture, texCoord);
} 