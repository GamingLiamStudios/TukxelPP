#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

struct Texture
{
public:
    unsigned texture;

    Texture(std::string path)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load Texture from Disk
        int            width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 3);
        if (!data)    // Error Handling
        {
            std::cerr << "ERROR::TEXTURE::LOAD\n";
            return;
        }
        // TODO: Offline Mipmap Generation
        glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_GREEN + nrChannels,    // Makes GL_RGB if Channels 3, GL_RGBA if 4
          width,
          height,
          0,
          GL_GREEN + nrChannels,
          GL_UNSIGNED_BYTE,
          data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Clean-up
        stbi_image_free(data);
    }
};