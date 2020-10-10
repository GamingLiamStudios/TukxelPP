#pragma once

#include <stdint.h>

#include <string>

class Shader
{
private:
    uint32_t program;

public:
    int success;

    Shader() = default;
    Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void Use();
};