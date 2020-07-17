#define WIREFRAME 0
#define FPS_CAP_ENABLED 0
#define FPS_CAP 240
#define VSYNC 0
#define FULLSCREEN 0

#include <Tukxel++.hpp>

#include <iostream>
#include <chrono>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

Camera camera;
glm::mat4 model, view, projection;
unsigned int VBO, VAO, EBO, texture;
unsigned int modelLoc, viewLoc;

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
    std::cout << "Created GLFW window" << std::endl;

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

int bindTexture(unsigned int& ID, const char* location) {
    //Init Texture
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
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    if (!(width && (!(width & (width - 1)))) || !(height && (!(height & (height - 1))))) {
        std::cout << "Texture at \"" << location << "\" is not power of 2" << std::endl;
        return -1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return 0;
}

int init(Shader &shader) {
    int error = 0;

    //Init OpenGL & STB
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(VSYNC);
#if WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    stbi_set_flip_vertically_on_load(true);

    //Load Triangles
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Create Shader
    shader = Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");

    //Bind Textures
    error |= bindTexture(texture, "res/pog.jpg");

    //Create Matricies
    model = view = projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = camera.GetLookAt();
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    //Set Uniform Values
    shader.use();
    shader.setInt("texture1", 0);
    shader.setMat4("projection", projection);

    //Set Uniform Value Pointers
    modelLoc = glGetUniformLocation(shader.ID, "model");
    viewLoc = glGetUniformLocation(shader.ID, "view");

    return error;
}

void dispose() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void update(GLFWwindow* window, float dt) {
    //Process Input
    processInput(window);
    camera.HandleInput(window, dt);

    //Update shit
    model = glm::rotate(model, glm::radians(50.0f) * dt, glm::vec3(0.5f, 1.0f, 0.0f));
    view = camera.GetLookAt();
}

void render(GLFWwindow* window, Shader shader) {
    //Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Enable Shader
    shader.use();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    //Draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Set Screen
    glfwSwapBuffers(window);
    glfwPollEvents();
}