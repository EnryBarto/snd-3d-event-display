#pragma once

#include <string>
#include <memory>

#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "Material.hpp"
#include "GpuMesh.hpp"

namespace snd3D {
    class Mesh {
        public:
            Mesh(aiMesh* mesh, glm::vec4 baseColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
            void setMaterial(const std::shared_ptr<Material>& material);

        private:
            std::string name;
            std::shared_ptr<Material> material;
            std::unique_ptr<GpuMesh> gpuMesh;
            bool active = true;
    };
}
