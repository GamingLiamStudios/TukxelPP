#pragma once
#ifndef OBJECTH
#define OBJECTH

#include <vector>
#include "Mesh.hpp"
#include "Util.hpp"

struct Texture {
public:
    unsigned int id;
    const char* type;
    const char* path;

    Texture(const char* type, const char* path) {
        this->path = path;
        this->type = type;

        //Init Texture
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        //Load Texture
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height,
            &nrChannels, 0);

        //Check for Texture Loading Errors
        if (!data) {
            std::cout << "Failed to load texture" << std::endl;
            return;
        }
        if (!(width && (!(width & (width - 1)))) || !(height && (!(height & (height - 1))))) {
            std::cout << "Texture at \"" << path << "\" is not power of 2" << std::endl;
            return;
        }

        //Set Texture Params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //Clean-up
        stbi_image_free(data);
    }
};

struct Object {
public:
    Mesh* mesh;
    Texture* texture;
    glm::vec3 wsCoord;

    Object(Mesh* mesh, Texture* texture, glm::vec3 wsCoord) {
        this->mesh = mesh;
        this->texture = texture;
        this->wsCoord = wsCoord;
    }

    Object(Mesh* mesh, const char* texture, glm::vec3 wsCoord) {
        this->mesh = mesh;
        this->texture = addressOfTemporary(Texture("texture", texture));
        this->wsCoord = wsCoord;
    }

    void Translate(glm::vec3 t) {
        wsCoord += t;
    }

    void Draw(Shader& shader) {
        shader.use();
        glUniform1i(glGetUniformLocation(shader.ID, "texture"), 0);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glBindVertexArray(mesh->VAO);
        glDrawElements(GL_TRIANGLES, mesh->length, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
    }

    void Dispose() {
        mesh->Dispose();
        glDeleteTextures(1, &texture->id);
    }
};

#endif