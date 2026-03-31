#include "Scene.hpp"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace snd3D {

    Scene::Scene(WindowManager& winMan, AppStateManager& stateMan) : windowManager(winMan), stateManager(stateMan) {
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
        if (this->stateManager.getCurrentState() == AppState::MOVING_TRACKBALL) {
            // Get the two positions on the unit sphere
            glm::vec3 destination = this->cursorToUnitSphere(this->windowManager.currentMousePosition[0], this->windowManager.currentMousePosition[1]);
            glm::vec3 origin = this->cursorToUnitSphere(this->windowManager.lastMousePosition[0], this->windowManager.lastMousePosition[1]);

            // Calculate the vector joining the two points
            glm::vec3 difference = destination - origin;

            if (difference != glm::vec3(0)) {
                // Aproximate the rotation angle with ||destination - origin||
                float angle = glm::length(difference) * 20;

                // The rotation axis is perpendicular to the origin and destination vector, so the cross product is used
                glm::vec3 rotationAxis = glm::cross(origin, destination);

                // Rotate the camera
                this->camera->rotateAroundCameraTarget(rotationAxis, angle);
                
                this->windowManager.lastMousePosition[0] = this->windowManager.currentMousePosition[0];
                this->windowManager.lastMousePosition[1] = this->windowManager.currentMousePosition[1];
            }
        }
    }

    void Scene::render() {
        this->obj->render(camera->getViewMatrix(), projection->getProjectionMatrix(), camera->getPosition(), false);
    }

    glm::vec3 Scene::cursorToUnitSphere(int x, int y) {

        int width = (int)this->windowManager.getCurrentResolution().x;
        int height = (int)this->windowManager.getCurrentResolution().y;

        // Map to [-1;1]
        glm::vec3 point;

        point.x = (2.0f * x - width) / width;
        point.y = (height - 2.0f * y) / height;

        float tmp = glm::dot(glm::vec2(point), glm::vec2(point)); // Square of the distance of the projected point from the center in the XY plane (radius^2)
        float delta = 1.0f - tmp; // Amount missing from r^2 to reach 1

        if (delta > 0.0f) {
            point.z = sqrt(delta);
        }
        else {
            // The click is outside the semisphere: there's no z that makes  x^2 + y^2 + z^2 = 1
            point.z = 0;
        }

        return normalize(point);
    }
}
