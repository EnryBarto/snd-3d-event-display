#pragma once

#include <string>
#include <memory>

#include <assimp/scene.h>

#include "Material.hpp"

namespace snd3D {
    class Mesh {
        public:
            Mesh(aiMesh* mesh);
            void setMaterial(const std::shared_ptr<Material>& material);

        private:
            std::string name;
            std::shared_ptr<Material> material;
            bool active = true;
    };
}
