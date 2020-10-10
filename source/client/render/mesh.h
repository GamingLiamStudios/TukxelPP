#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include "util/array.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
};

class Mesh
{
private:
    std::vector<Vertex>    verticies;
    std::vector<glm::vec2> textureCoords;
    std::vector<int>       indicies;

    uint32_t buffers[3];    // VBOs & EBOs

public:
    uint32_t VAO;

    Mesh(std::vector<Vertex> verticies, std::vector<int> indicies)
        : verticies(verticies), indicies(indicies)
    {    // Setup Mesh for rendering
        // Gen buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(3, buffers);
        glBindVertexArray(VAO);

        {    // Vertex VBO
            // Place Verticies into VBO buffer
            glBindBuffer(GL_VERTEX_ARRAY, buffers[0]);
            glBufferData(
              GL_ARRAY_BUFFER,
              sizeof(Vertex) * verticies.size(),
              verticies.data(),
              GL_STATIC_DRAW);

            // Tell Shaders what data is stored in a Vertex
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  0);    // pos
            glVertexAttribPointer(
              1,
              3,
              GL_FLOAT,
              GL_FALSE,
              sizeof(Vertex),
              (void *) (3 * sizeof(float)));    // normal
        }

        {    // Texture Coordinate VBO
            // Place Texture Coordinates into a VBO
            glBindBuffer(GL_VERTEX_ARRAY, buffers[1]);
            glBufferData(
              GL_ARRAY_BUFFER,
              sizeof(glm::vec2) * textureCoords.size(),
              textureCoords.data(),
              GL_STATIC_DRAW);

            // Tell Shaders what data is stored in a Texture Coordinate
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
                                  0);    // texCoord
        }

        // Place Indicies into EBO buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
        glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          sizeof(int) * indicies.size(),
          indicies.data(),
          GL_STATIC_DRAW);

        // Enable Vertex Attribute Arrays
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(3, buffers);
    }

    void render()
    {
        glBindVertexArray(VAO);

        // Draw Triangles
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    }

    size_t pointsInMesh() { return indicies.size(); }
};