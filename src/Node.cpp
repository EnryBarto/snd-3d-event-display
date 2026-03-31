#include "Node.hpp"

namespace snd3D {

    Node::Node(const aiScene* scene, aiNode* node, std::vector<std::shared_ptr<Mesh>>& meshes) {

        aiMatrix4x4 matrix = node->mTransformation;

        this->localModelMatrix = glm::mat4(
            matrix.a1, matrix.b1, matrix.c1, matrix.d1,
            matrix.a2, matrix.b2, matrix.c2, matrix.d2,
            matrix.a3, matrix.b3, matrix.c3, matrix.d3,
            matrix.a4, matrix.b4, matrix.c4, matrix.d4
        );

        this->name = std::string(node->mName.C_Str());

        // Get the reference to all the meshes of the node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            this->meshes.push_back(meshes[node->mMeshes[i]]);
        }

        // Create children nodes
        this->childrenNode.reserve(node->mNumChildren);
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            this->childrenNode.push_back(std::make_unique<Node>(scene, node->mChildren[i], meshes));
        }
    }

    void Node::setShader(const std::shared_ptr<Shader>& shader) {
        for (auto& node : this->childrenNode) {
            node->setShader(shader);
        }

        for (auto& mesh : this->meshes) {
            mesh->setShader(shader);
        }
    }

    void Node::render(const glm::mat4& parentModelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& camPos, bool showAnchor) {
        glm::mat4 modelMatrix = parentModelMatrix * this->localModelMatrix;

        for (auto& node : this->childrenNode) {
            node->render(modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
        }

        for (auto& mesh : this->meshes) {
            mesh->render(modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
        }
    }
}
