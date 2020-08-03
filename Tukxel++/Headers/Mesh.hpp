#pragma once
#ifndef MESH
#define MESH

#include <string>
#include <algorithm>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Mesh {
public:
    Vertex* vertices;
    unsigned int* indicies;
    unsigned int length;
	unsigned int VAO;

private:
    unsigned int VBO, EBO;

public:

    Mesh() {}

    Mesh(Vertex* vertices, int length) {
        this->vertices = vertices;
        this->length = length;
        indicies = new unsigned int[length];
        for (int i = 0; i < length; i++)
            indicies[i] = i;

        SetupMesh();
    }

    Mesh(Vertex* vertices, int length, unsigned int indicies[]) {
        this->vertices = vertices;
        this->indicies = indicies;
        this->length = length;

        SetupMesh();
    }

    void Dispose() {
        glBindVertexArray(VAO);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

private:

    void SetupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, length * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};

#endif