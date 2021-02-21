#pragma once

#include "util/types.h"

#include <string>
#include <memory>

class Shader
{
private:
    std::shared_ptr<unsigned> program;

public:
    int success;

    Shader() = default;
    Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void Use();
};