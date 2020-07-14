#include "Tukxel++.h"

#include <iostream>
#include <chrono>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float vertices[] = {
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f // top left
};
unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};


unsigned int VBO, VAO, EBO;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    std::cout << "Initalized GLFW" << std::endl;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tukxel++", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    std::cout << "Created GLFW window" << std::endl;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "Initalized GLAD" << std::endl;

    if (init() != 0) {
        std::cin.get();
        return -1;
    }
    Shader shader("shaders/VertexShader.txt", "shaders/FragmentShader.txt");
    std::cout << "Initalized" << std::endl;
    long long lastTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double ammountOfTicks = 20.0;
    double ns = 1000000000.0 / ammountOfTicks;
    double delta = 0;
    long long timer = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    int frames = 0;
    while (!glfwWindowShouldClose(window)) {
        long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta += (now - lastTime) / ns;
        lastTime = now;
        while (delta >= 1) {
            update(window);
            delta--;
        }
        if (!glfwWindowShouldClose(window))
            render(window, shader);
        frames++;
        if (std::chrono::high_resolution_clock::now().time_since_epoch().count() - timer > 1000000000) {
            timer += 1000000000;
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
        }
    }

    glfwTerminate();
    std::cout << "Terminated GLFW" << std::endl;
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int init() {
    //Load Triangles
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Init Texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return 0;
}

void update(GLFWwindow* window) {
    processInput(window);
}

void render(GLFWwindow* window, Shader shader) {
    //Clear Screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Render
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Set Screen
    glfwSwapBuffers(window);
    glfwPollEvents();
}