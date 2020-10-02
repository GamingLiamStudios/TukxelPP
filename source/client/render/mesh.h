#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
};

class Mesh {
   private:
    std::vector<Vertex> verticies;
    std::vector<int> indicies;
    uint32_t buffers[2];  // VBO, EBO

   public:
    uint32_t VAO;

    Mesh(std::vector<Vertex> verticies, std::vector<int> indicies)
        : verticies(verticies),
          indicies(indicies) {  // Setup Mesh for rendering
        // Gen buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(2, &buffers);
        glBindVertexArray(VAO);

        // Place Verticies into VBO buffer
        glBindBuffer(GL_VERTEX_ARRAY, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(),
                     verticies.data(), GL_STATIC_DRAW);

        // Place Indicies into EBO buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicies.size(),
                     indicies.data(), GL_STATIC_DRAW);

        // Tell Shaders what is accessable
        void *index = 0;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              index);  // pos
        index += 3 * sizeof(float);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                              index);  // tex
        index += 2 * sizeof(float);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // Clean-up
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(2, &buffers);
    }

    void render() {
        glBindVertexArray(mesh->VAO);

        // Draw Triangles
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    }
};