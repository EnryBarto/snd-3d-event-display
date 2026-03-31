#pragma once

#include <string>
#include <memory>

#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "Material.hpp"
#include "GpuMesh.hpp"
#include "Shader.hpp"

namespace snd3D {
    class Mesh {
        public:
            Mesh(aiMesh* mesh, glm::vec4 baseColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
            void setMaterial(const std::shared_ptr<Material>& material);
            void setShader(const std::shared_ptr<Shader>& shader);
            void render(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& camPos, bool showAnchor);

        private:
            std::string name;
            std::shared_ptr<Material> material;
            std::unique_ptr<GpuMesh> gpuMesh;
            bool active = true;
    };
}
