#pragma once
#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "texture.h"
#include "util/types.h"

#include <vector>
#include <cstddef>

struct Vertex
{
    glm::vec3 pos;
    /* union
    {
        struct
        {
            u8 w : 2;
            u16 z : 10;
            u16 y : 10;
            u16 x : 10;
        } v;
        u32 p;
    } normal; // normalized*/
    glm::u16vec2 texCoord;    // also normalized
};

class Mesh
{
private:
    std::vector<Vertex>   verticies;
    std::vector<unsigned> indicies;
    Texture               texture;

    unsigned buffers[2];    // VBO & EBO

public:
    unsigned VAO;

    Mesh(std::vector<Vertex> verticies, std::vector<unsigned> indicies, Texture texture)
        : verticies(verticies), indicies(indicies), texture(texture)
    {    // Setup Mesh for rendering
        // Gen buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(2, buffers);
        glBindVertexArray(VAO);

        // Vertex VBO
        // Place Verticies into VBO buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(
          GL_ARRAY_BUFFER,
          sizeof(Vertex) * verticies.size(),
          verticies.data(),
          GL_STATIC_DRAW);

        // Tell Shaders what data is stored in a Vertex
        glVertexAttribPointer(
          0,
          3,
          GL_FLOAT,
          GL_FALSE,
          sizeof(Vertex),
          (void *) offsetof(Vertex, pos));    // pos

        /*
        glVertexAttribPointer(
         1,
         4,
         GL_INT_2_10_10_10_REV,
         GL_FALSE,
         sizeof(Vertex),
         (void *) offsetof(Vertex, normal));    // normal
        */
        glVertexAttribPointer(
          1,
          2,
          GL_UNSIGNED_SHORT,
          GL_TRUE,
          sizeof(Vertex),
          (void *) offsetof(Vertex, texCoord));    // texCoord

        // Place Indicies into EBO buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          sizeof(unsigned) * indicies.size(),
          indicies.data(),
          GL_STATIC_DRAW);

        // Enable Vertex Attribute Arrays
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        // glEnableVertexAttribArray(2);

        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(2, buffers);
    }

    void render()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *texture.id);

        glBindVertexArray(VAO);

        // Draw Triangles
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    }

    inline size_t pointsInMesh() { return indicies.size(); }
};
