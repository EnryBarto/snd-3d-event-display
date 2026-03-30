#include "Object.hpp"

namespace snd3D {

    Object::Object(const aiScene* scene) {
        this->modelMatrix = glm::mat4(1);

        // Load all materials
        std::vector<std::shared_ptr<Material>> materials;
        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            materials.push_back(std::make_shared<Material>(scene->mMaterials[i]));
        }

        // Load all meshes, also setting their materials
        std::vector<std::shared_ptr<Mesh>> meshes;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiColor4D baseColor(0.6f, 0.6f, 0.6f, 1.0f); // Default color
            scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_BASE_COLOR, baseColor);
            auto mesh = std::make_shared<Mesh>(scene->mMeshes[i], glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));
            mesh->setMaterial(materials[scene->mMeshes[i]->mMaterialIndex]);
            meshes.push_back(mesh);
        }

        // Recursively start creating nodes
        this->rootNode = std::make_unique<Node>(scene, scene->mRootNode, meshes);
    }
}
