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
            auto mesh = std::make_shared<Mesh>(scene->mMeshes[i]);
            mesh->setMaterial(materials[scene->mMeshes[i]->mMaterialIndex]);
            meshes.push_back(mesh);
        }

        // Recursively start creating nodes
        this->rootNode = std::make_unique<Node>(scene, scene->mRootNode, meshes);
    }
}
