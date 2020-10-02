#include "voxel.h"

#include <glad/glad.h>

Voxel::Voxel(std::shared_ptr<Mesh> mesh, glm::vec3 pos, glm::vec3 lightSrc,
             uint32_t lightLevel)
    : mesh(mesh), pos(pos) {
    this->lightLevel.resize(mesh->verticies.size());

    updateLightLevel(lightLevel);
}

void Voxel::updateLightLevel(glm::vec3 lightSrc, uint32_t lightLevel) {
    for (auto ll : this->lightLevel) ll = lightLevel;
}

void Voxel::render() { mesh->render(); }
