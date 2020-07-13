#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NULL 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void update(GLFWwindow* window);
void render(GLFWwindow* window);
int init();
int loadShader(const char* location, unsigned int& shaderDest, GLenum type);