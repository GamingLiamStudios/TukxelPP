#include "Tukxel++.h"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIREFRAME 0
#define FPS_CAP_ENABLED 0
#define FPS_CAP 240
#define VSYNC 0
#define TICK_COUNT 20
#define FULLSCREEN 0

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};


unsigned int VBO, VAO, EBO, texture;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    std::cout << "Initalized GLFW" << std::endl;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
#if FULLSCREEN
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Tukxel++", glfwGetPrimaryMonitor(), NULL);
#else
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tukxel++", NULL, NULL);
    glfwSetWindowPos(window, mode->width / 2 - SCR_WIDTH / 2, mode->height / 2 - SCR_HEIGHT / 2);
#endif
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

    glfwSwapInterval(VSYNC);
#if WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    stbi_set_flip_vertically_on_load(true);

    if (init() != 0) {
        dispose();
        glfwTerminate();
        std::cin.get();
        return -1;
    }
    Shader shader("res/shaders/VertexShader.txt", "res/shaders/FragmentShader.txt");
    std::cout << "Initalized" << std::endl;
    long long lastTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double ns = 1000000000.0 / TICK_COUNT;
#if FPS_CAP_ENABLED
    double fns = 1000000000.0 / FPS_CAP;
    double fdelta = 0;
#elif VSYNC
    double fns = 1000000000.0 / mode->refreshRate;
    double fdelta = 0;
#endif
    double delta = 0;
    long long timer = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    int frames = 0;
    while (!glfwWindowShouldClose(window)) {
        long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta += (now - lastTime) / ns;
        while (delta >= 1) {
            update(window);
            delta--;
        }
#if FPS_CAP_ENABLED || VSYNC
        fdelta += (now - lastTime) / fns;
        if (!glfwWindowShouldClose(window) && fdelta >= 1) {
            render(window, shader);
            fdelta--;
            frames++;
        }
#else
        if (!glfwWindowShouldClose(window))
            render(window, shader);
        frames++;
#endif
        lastTime = now;
        if (std::chrono::high_resolution_clock::now().time_since_epoch().count() - timer > 1000000000) {
            timer += 1000000000;
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
        }
    }

    dispose();
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
    glfwSwapInterval(VSYNC);
}

int bindTexture(unsigned int& ID, GLenum bound, const char* location) {
    //Init Texture
    glActiveTexture(bound);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load Texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(location, &width, &height,
        &nrChannels, 0);
    if (!(width && (!(width & (width - 1)))) || !(height && (!(height & (height - 1))))) {
        std::cout << "Texture at \"" << location << "\" is not power of 2" << std::endl;
        return -1;
    }
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    stbi_image_free(data);
    return 0;
}

int init() {
    int error = 0;
    //Load Triangles
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Bind Textures
    error |= bindTexture(texture, GL_TEXTURE0, "res/pog.jpg");

    return error;
}

void dispose() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void update(GLFWwindow* window) {
    //Update shit
}

void render(GLFWwindow* window, Shader shader) {
    //Process Input
    processInput(window);

    //Clear Screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Make Transform
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    //Apply Transform
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    
    //Draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Set Screen
    glfwSwapBuffers(window);
    glfwPollEvents();
}