#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <glad/glad.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>
#endif

struct Texture
{
public:
    std::shared_ptr<unsigned> id;

    Texture(std::string path)
    {
        id = std::make_shared<unsigned>(0);
        glGenTextures(1, id.get());
        glBindTexture(GL_TEXTURE_2D, *id);

        // Set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load Texture from Disk
        int            width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (!data)    // Error Handling
        {
            std::cerr << "ERROR::TEXTURE::LOAD\n";
            return;
        }
        // TODO: Offline Mipmap Generation. Prehaps a 'First Time Setup' thing.
        glTexImage2D(
          GL_TEXTURE_2D,
          0,
          (nrChannels > 3) ? GL_RGBA : GL_RGB,
          width,
          height,
          0,
          (nrChannels > 3) ? GL_RGBA : GL_RGB,
          GL_UNSIGNED_BYTE,
          data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Clean-up
        stbi_image_free(data);
    }

    ~Texture()
    {
        if (id.unique()) glDeleteTextures(1, id.get());
    }
};
