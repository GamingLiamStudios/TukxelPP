#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include "mesh.h"

class Voxel {
   private:
    std::shared_ptr<Mesh> mesh;
    std::vector<uint32_t> lightLevel;
    glm::vec3 pos;
    uint32_t VAO;

   public:
    Voxel(std::shared_ptr<Mesh> mesh, glm::vec3 pos, glm::vec3 lightSrc,
          uint32_t lightLevel);

    void updateLightLevel(glm::vec3 lightSrc, uint32_t lightLevel);

    void render();
};