﻿#define WIREFRAME 0
#define FPS_CAP_ENABLED 0
#define FPS_CAP 240
#define VSYNC 1
#define FULLSCREEN 0

#include <Tukxel++.hpp>

#include <iostream>
#include <chrono>
#include <map>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float cubeverts[] = {
    // positions // normals // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

Camera camera;
glm::mat4 model, view, projection;
std::map<std::string, Mesh> models;
std::vector<Object> objects;
unsigned int modelLoc, viewLoc, viewPosLoc;

bool firstMouse;
float lastX, lastY;

int main(void) {
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
    glfwSetCursorPosCallback(window, mouse_callback);
    std::cout << "Created GLFW window" << std::endl;
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "Initalized GLAD" << std::endl;

    Shader shader;
    if (init(shader) != 0) {
        dispose();
        glfwTerminate();
        std::cin.get();
        return -1;
    }
    firstMouse = true;
    std::cout << "Initalized" << std::endl;
    long long lastTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double delta = 0.0f;
#if FPS_CAP_ENABLED
    double fns = 1000000000.0 / FPS_CAP;
    double fdelta = 0.0f;
#elif VSYNC
    double fns = 1000000000.0 / mode->refreshRate;
    double fdelta = 0.0f;
#endif
    long long timer = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    int frames = 0;
    while (!glfwWindowShouldClose(window)) {
        long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta = (now - lastTime) / 1000000000.0;
        update(window, delta);
#if FPS_CAP_ENABLED
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 1.0f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.HandleMouseInput(xoffset, yoffset);
}

int init(Shader &shader) {
    int error = 0;

    //Init Libraries
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(VSYNC);
#if WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    stbi_set_flip_vertically_on_load(true);

    //Create Shader
    shader = Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");

    if (!shader.success)
        return shader.success;

    //Load Models
    models = std::map<std::string, Mesh>{
        {"cube", Mesh((Vertex*)&cubeverts[0], sizeof(cubeverts) / sizeof(Vertex))} //Cube
    };

    //Load Objects
    objects = std::vector<Object>();
    Texture tex("texture", "res/pog.jpg");
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(1.0, 0.0, 0.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(1.0, 1.0, 0.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(0.0, 1.0, 0.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(0.0, 0.0, 0.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(1.0, 0.0, 1.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(1.0, 1.0, 1.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(0.0, 1.0, 1.0)));
    objects.push_back(Object(&models.find("cube")->second, &tex, glm::vec3(0.0, 0.0, 1.0)));

    //Create Matricies
    model = view = projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = camera.GetViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    //Set Uniform Values
    shader.use();
    shader.setInt("texture", 0);
    shader.setMat4("projection", projection);
    shader.setVec3("lightPos", 1.0f, 3.0f, 1.0f);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    //Set Uniform Value Pointers
    modelLoc = glGetUniformLocation(shader.ID, "model");
    viewLoc = glGetUniformLocation(shader.ID, "view");
    viewPosLoc = glGetUniformLocation(shader.ID, "viewPos");

    return error;
}

void dispose() {
    for (int i = 0; i < objects.size(); i++)
        objects[i].Dispose();
}

void update(GLFWwindow* window, float dt) {
    //Process Input
    processInput(window);
    camera.HandleKeyboardInput(window, 2.5f * dt);

    //Update shit
    for (int i = 0; i < objects.size(); i++)
        objects[i].Translate(glm::vec3(1.0 * dt, 0.0, 0.0));
    view = camera.GetViewMatrix();
}

void render(GLFWwindow* window, Shader &shader) {
    //Clear Screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Enable Shader
    shader.use();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(viewPosLoc, 1, GL_FALSE, glm::value_ptr(camera.Position));

    //Draw
    for (int i = 0; i < objects.size(); i++) {
        model = glm::translate(model, objects[i].wsCoord);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        objects[i].Draw(shader);
        model = glm::mat4(1.0f);
    }

    //Set Screen
    glfwSwapBuffers(window);
    glfwPollEvents();
}