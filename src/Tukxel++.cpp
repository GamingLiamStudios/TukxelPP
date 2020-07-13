#include "Tukxel++.h"

#include <string>
#include <fstream>
#include <streambuf>
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
unsigned int vertexShader, fragmentShader, shaderProgram;

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
            render(window);
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

int loadShader(const char* location, unsigned int& shaderDest, GLenum type) {
    unsigned int shader = glCreateShader(type);
    std::ifstream file(location, std::ios::in);
    if (!file) {
        std::cout << "Unable to open File" << std::endl;
        return -1;
    }
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    const char* st = content.c_str();
    glShaderSource(shader, 1, &st, NULL);
    glCompileShader(shader);
    file.close();
    content.erase(0, content.length() - 1);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
        return -1;
    }
    shaderDest = shader;
    return 0;
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


    //Load Vertex Shader
    int ret = loadShader("shaders/VertexShader.txt", vertexShader, GL_VERTEX_SHADER);
    if (ret != 0) {
        std::cout << "Vertex Shader Failed to load" << std::endl;
        return -1;
    }

    //Load Fragment Shader
    ret = loadShader("shaders/FragmentShader.txt", fragmentShader, GL_FRAGMENT_SHADER);
    if (ret != 0) {
        std::cout << "Fragment Shader Failed to load" << std::endl;
        return -1;
    }
    
    //Create Shader Program and Attach Vertex & Fragment Shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
            infoLog << std::endl;
        return -1;
    }

    //Delete Vertex & Fragment Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
}

void update(GLFWwindow* window) {
    processInput(window);
}

void render(GLFWwindow* window) {
    //Clear Screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Render
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Set Screen
    glfwSwapBuffers(window);
    glfwPollEvents();
}