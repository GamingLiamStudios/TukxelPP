#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "render/shader.h"

class Client
{
public:
    Client();
    ~Client();

    void render();
    //void tick();

    bool isAlive;

private:
    GLFWwindow *window;
    Shader      shader;

    static void processInput(GLFWwindow *window, int key, int, int action, int);
};