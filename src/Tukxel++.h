#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void update(GLFWwindow* window);
void render(GLFWwindow* window, Shader shader);
int init();