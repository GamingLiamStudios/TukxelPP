#include "client.h"

#include <iostream>

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
        return;
    }
    glfwMakeContextCurrent(window);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    isAlive = true;

    // Initalize Window
    glViewport(0, 0, 800, 600);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });
    glfwSetKeyCallback(window, &Client::processInput);

    shader = Shader("./res/vertex.vert", "./res/fragment.frag");
    if (!shader.success) isAlive = false;
}

Client::~Client() {
    // Destroy all GLFW stuff
    glfwTerminate();
}

void Client::render() {
    // Check if window has been scheduled for closure
    isAlive &= !glfwWindowShouldClose(window);

    // Clear Window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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