#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/fwd.hpp>
#include <assimp/scene.h>

#include "Mesh.hpp"
#include "Shader.hpp"

namespace snd3D {
    class Node {
        public:
            Node(const aiScene* scene, aiNode* node, std::vector<std::shared_ptr<Mesh>>& meshes);
            void setShader(const std::shared_ptr<Shader>& shader);
            void updateGlobalModelMatrix(const glm::mat4& parentModelMatrix);
            void render(const glm::mat4& parentModelMatrix, bool showAnchor);
            void render(bool showAnchor); // Use the buffered model matrix

        private:
            std::string name;
            std::vector<std::unique_ptr<Node>> childrenNode;
            std::vector<std::shared_ptr<Mesh>> meshes;
            glm::mat4 localModelMatrix;
            glm::mat4 globalModelMatrix;
            bool active = true;
    };
}
