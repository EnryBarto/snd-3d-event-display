#pragma once

#include <memory>
#include <string>

#include <assimp/scene.h>
#include <glm/fwd.hpp>

#include "scene/Node.hpp"
#include "rendering/Shader.hpp"

namespace snd3D {
    class Object {
        public:
            Object(const aiScene* scene);
            Object(Node* rootNode);
            void setShader(const std::shared_ptr<Shader>& shader);
            void updateModelMatrix(const glm::mat4& modelMatrix);
            void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& camPos, bool showAnchor);

        private:
            std::unique_ptr<Node> rootNode;
            std::shared_ptr<Shader> shader;
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            bool active = true;
    };
}
