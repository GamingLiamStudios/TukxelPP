#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Client {
   public:
    Client();
    ~Client();

    void render();
    void tick();

    bool isAlive;

   private:
    GLFWwindow *window;

    static void processInput(GLFWwindow* window, int key, int, int action, int);
};