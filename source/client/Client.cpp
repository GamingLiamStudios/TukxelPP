#include "client.h"

#include <functional>
#include <iostream>

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

Client::Client() {
    // Initalize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create Window
    window = glfwCreateWindow(800, 600, "Tukxel++", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        isAlive = false;
        return;
    }
    glfwMakeContextCurrent(window);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        isAlive = false;
        return;
    }

    // Initalize Window
    glViewport(0, 0, 800, 600);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });
    glfwSetKeyCallback(window, &Client::processInput);
}

Client::~Client() {
    // Destroy all GLFW stuff
    glfwTerminate();
}

void Client::render() {
    // Check if window has been scheduled for closure
    isAlive &= !glfwWindowShouldClose(window);

    // Display changes
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Client::processInput(GLFWwindow* window, int key, int, int action, int) {
    if (action == GLFW_REPEAT) return;
    auto usr_ptr = (Client*)glfwGetWindowUserPointer(window);

    switch (key) {
        case GLFW_KEY_ESCAPE:
            usr_ptr->isAlive = false;
            break;
    }
}