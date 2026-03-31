#include "Scene.hpp"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace snd3D {

    Scene::Scene(WindowManager& winMan) : windowManager(winMan) {
        this->camera = std::make_unique<Camera>(glm::vec3(400.0f), glm::vec3(0.0f, 0.0f, 554.0f));
        this->projection = std::make_unique<Projection>(this->windowManager.getAspectRatio(), 80.0f);

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile("assets/geometries/SND.gltf",
            aiProcess_Triangulate |
            aiProcess_GenNormals |
            aiProcess_JoinIdenticalVertices |
            aiProcess_ImproveCacheLocality
        );

        if (!scene) {
            std::cerr << "Error loading file: " << importer.GetErrorString() << std::endl;
        }

        // Debug object
        this->obj = std::make_unique<Object>(scene);
        std::shared_ptr<snd3D::Shader> flat = std::make_shared<snd3D::Shader>("Flat", "flat.vert", "flat.frag");
        obj->setShader(flat);
    }

    void Scene::update() {
        if (this->windowManager.isFramebufferChanged()) this->projection->changeAspectRatio(this->windowManager.getAspectRatio());
    }

    void Scene::render() {
        this->obj->render(camera->getViewMatrix(), projection->getProjectionMatrix(), camera->getPosition(), false);
    }
}