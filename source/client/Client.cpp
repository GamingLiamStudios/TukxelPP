#include "client.h"

#include <fstream>
#include <iostream>
#include <vector>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

Client::Client()
{
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
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    {    // Set Window Icon
        std::ifstream fs;
        fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fs.open("./res/logo.ico", std::ios::in | std::ios::binary);

        fs.seekg(6, std::ios::beg);    // seeks to first image entry

        // Extract useful data from header
        fs.seekg(8, std::ios::cur);
        uint32_t length, offset;    // Assumes host is Little Endian
        fs.read((char *) &length, 4);
        fs.read((char *) &offset, 4);

        // Read Stream from start of PNG header to buffer
        fs.seekg(offset, std::ios::beg);
        std::vector<uint8_t> buffer;
        buffer.resize(length);
        fs.read((char *) buffer.data(), length);
        fs.close();

        // Read PNG
        int       nrChannels;
        GLFWimage image;
        image.pixels = stbi_load_from_memory(
          buffer.data(),
          buffer.size(),
          &image.width,
          &image.height,
          &nrChannels,
          0);
        if (!image.pixels)
        {
            std::cerr << "Failed to load texture" << std::endl;
            return;
        }

        glfwSetWindowIcon(window, 1, &image);
        stbi_image_free(image.pixels);
    }

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    isAlive = true;

    // Initalize Window
    glViewport(0, 0, 800, 600);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    glfwSetKeyCallback(window, &Client::processInput);

    // Initalize for Rendering
    stbi_set_flip_vertically_on_load(true);
    shader = Shader("./res/vertex.vert", "./res/fragment.frag");
    if (!shader.success) isAlive = false;
}

Client::~Client()
{
    // Destroy all remaining GLFW stuff
    glfwTerminate();
}

void Client::render()
{
    // Check if window has been scheduled for closure
    isAlive &= !glfwWindowShouldClose(window);

    // Clear Window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render

    // Display changes
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Client::processInput(GLFWwindow *window, int key, int, int action, int)
{
    if (action == GLFW_REPEAT) return;
    auto usr_ptr = (Client *) glfwGetWindowUserPointer(window);

    switch (key)
    {
    case GLFW_KEY_ESCAPE: usr_ptr->isAlive = false; break;
    }
}