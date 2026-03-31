#pragma once

#include <memory>
#include <vector>
#include <string>

#include <assimp/types.h>
#include <glm/fwd.hpp>

#include "Node.hpp"
#include "Shader.hpp"

namespace snd3D {
    class Object {
        public:
            Object(const aiScene* scene);
            void setShader(const std::shared_ptr<Shader>& shader);
            void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& camPos, bool showAnchor);

        private:
            std::unique_ptr<Node> rootNode;
            glm::mat4 modelMatrix;
            bool active = true;
    };
}
