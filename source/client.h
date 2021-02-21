#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "engine/shader.h"
#include "engine/mesh.h"

#include <memory>

class Client
{
public:
    Client();
    ~Client();

    void render();
    // void tick();

    bool isAlive;

private:
    GLFWwindow *window;
    Shader      shader;

    std::vector<std::shared_ptr<Mesh>> meshes;

    void        init();
    static void processInput(GLFWwindow *window, int key, int, int action, int);
};