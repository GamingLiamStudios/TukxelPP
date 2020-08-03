#pragma once
#ifndef OBJECTH
#define OBJECTH

#include <vector>
#include "Mesh.hpp"

struct Texture {
    unsigned int id;
    const char* type;
    const char* path;
};

struct Object {
public:
    Mesh mesh;
    Texture texture;

    Object(Mesh mesh, Texture texture) {
        this->mesh = mesh;
        this->texture = texture;
    }

    Object(Mesh mesh, const char* texture) {
        this->texture = Texture();
        this->texture.path = texture;
        this->texture.type = "texture";
        bindTexture(this->texture.id, this->texture.path);
    }

    void Draw(Shader& shader) {
        shader.use();
        glUniform1i(glGetUniformLocation(shader.ID, "texture"), 0);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.length, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
    }

    void Dispose() {
        mesh.Dispose();
        glDeleteTextures(1, &texture.id);
    }

private:
    int bindTexture(unsigned int& ID, const char* location) {
        //Init Texture
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return 0;
    }
};

#endif