#version 330 core
out vec4 FragColor;

varying float brightness;

void main() {
    float light = max(brightness, 0.07f);
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f) * light;
} 