#pragma once

#include <memory>
#include <vector>
#include <string>

#include <assimp/types.h>
#include <glm/mat4x4.hpp>

#include "Node.hpp"

namespace snd3D {
    class Object {
        public:
            Object(const aiScene* scene);

        private:
            std::unique_ptr<Node> rootNode;
            glm::mat4 modelMatrix;
            bool active = true;
    };
}
