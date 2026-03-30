#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/mat4x4.hpp>
#include <assimp/scene.h>

#include "Mesh.hpp"

namespace snd3D {
    class Node {
        public:
            Node(const aiScene* scene, aiNode* node, std::vector<std::shared_ptr<Mesh>>& meshes);

        private:
            std::string name;
            std::vector<std::unique_ptr<Node>> childrenNode;
            std::vector<std::shared_ptr<Mesh>> meshes;
            glm::mat4 modelMatrix;
            bool active = true;
    };
}
