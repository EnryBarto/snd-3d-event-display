#pragma once

#include <string>

#include <assimp/material.h>
#include <glm/glm.hpp>

namespace snd3D {
    class Material {
        public:
            Material(aiMaterial* material);

        private:
            std::string name;
            float alpha;
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shininess;
    };
}
