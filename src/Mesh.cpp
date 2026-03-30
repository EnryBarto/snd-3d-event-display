#include "Mesh.hpp"

namespace snd3D {
    Mesh::Mesh(aiMesh* mesh) {
        this->name = std::string(mesh->mName.C_Str());

        if (this->name.empty()) {
            this->name = "Unnamed_Mesh";
        }
    }

    void Mesh::setMaterial(const std::shared_ptr<Material>& material) {
        this->material = material;
    }
}
