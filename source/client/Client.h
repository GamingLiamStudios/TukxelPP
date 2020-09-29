#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Client {
   private:
    GLFWwindow *window;

   public:
    Client();
    ~Client();

    void Render();
    void Tick();

    bool isAlive;
};