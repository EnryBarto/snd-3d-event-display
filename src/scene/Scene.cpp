#include "scene/Scene.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "core/Constants.hpp"

namespace snd3D {

    Scene::Scene(WindowManager& winMan, AppStateManager& stateMan, AppSettings& appSettings) : windowManager(winMan), stateManager(stateMan), settings(appSettings) {
        this->camera = std::make_unique<Camera>(glm::vec3(400.0f), glm::vec3(0.0f, 0.0f, 554.0f));
        this->projection = std::make_unique<Projection>(this->windowManager.getAspectRatio(), 80.0f);
        this->shader = std::make_shared<snd3D::Shader>("Flat", "flat.vert", "flat.frag");
        this->pivot = std::unique_ptr<Object>(this->objectFactory.getSphere());
        this->pivot->setShader(this->shader);
    }

    void Scene::update() {
        if (this->windowManager.isFramebufferChanged()) this->projection->changeAspectRatio(this->windowManager.getAspectRatio());

        // Calculation are made here beacuse in the callbacks they would be execute too many times, slowing down the reactivity
        switch (this->stateManager.getCurrentState()) {
            case AppState::GEOMETRY_LOAD:
                try {
                    this->detector = std::unique_ptr<Object>(this->objectFactory.getFromFile(this->stateManager.getDetectorPath()));
                    this->detector->setShader(this->shader);
                    this->stateManager.geometryLoaded();
                } catch (...) {
                    this->stateManager.errorLoadingGeometry();
                }
                break;

            case AppState::MOVING_PAN: {
                float deltaX = this->windowManager.lastMousePosition[0] - this->windowManager.currentMousePosition[0];
                float deltaY = this->windowManager.currentMousePosition[1] - this->windowManager.lastMousePosition[1];

                this->camera->moveParallel(deltaX, deltaY);
                // Update the last mouse position
                this->windowManager.lastMousePosition[0] = this->windowManager.currentMousePosition[0];
                this->windowManager.lastMousePosition[1] = this->windowManager.currentMousePosition[1];
            } break;

            case AppState::MOVING_TRACKBALL: {
                // Get the two positions on the unit sphere
                glm::vec3 destination = this->cursorToUnitSphere(this->windowManager.currentMousePosition[0], this->windowManager.currentMousePosition[1]);
                glm::vec3 origin = this->cursorToUnitSphere(this->windowManager.lastMousePosition[0], this->windowManager.lastMousePosition[1]);

                // Calculate the vector joining the two points
                glm::vec3 difference = destination - origin;

                if (difference != glm::vec3(0)) {
                    this->camera->rotateTrackball(origin, destination);
                    // Update the last mouse position
                    this->windowManager.lastMousePosition[0] = this->windowManager.currentMousePosition[0];
                    this->windowManager.lastMousePosition[1] = this->windowManager.currentMousePosition[1];
                }
            } break;
        }

        if (this->settings.isCameraPivotActive()) { // Calculations are performed only if the pivot is active
            if (this->camera->isChanged()) {
                glm::mat4 matrix = glm::translate(glm::mat4(1.0f), this->camera->getTarget());
                matrix = glm::scale(matrix, glm::vec3(constants::sizes::PIVOT));
                this->pivot->updateModelMatrix(matrix);
            }
        }

        if (glfwGetKey(this->windowManager.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)  camera->rotateByAngles(-constants::factors::ROTATION_SPEED, 0);
        if (glfwGetKey(this->windowManager.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) camera->rotateByAngles(constants::factors::ROTATION_SPEED, 0);
        if (glfwGetKey(this->windowManager.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)  camera->rotateByAngles(0, constants::factors::ROTATION_SPEED);
        if (glfwGetKey(this->windowManager.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) camera->rotateByAngles(0, -constants::factors::ROTATION_SPEED);
    }

    void Scene::render() {
        switch (this->stateManager.getCurrentState()) {
            case AppState::TRACKBALL:
            case AppState::MOVING_TRACKBALL:
            case AppState::PAN:
            case AppState::MOVING_PAN:
                if (this->settings.isCameraPivotActive()) this->pivot->render(camera->getViewMatrix(), projection->getProjectionMatrix(), camera->getPosition(), false);
            case AppState::EXPORT_IMAGE:
                this->detector->render(camera->getViewMatrix(), projection->getProjectionMatrix(), camera->getPosition(), false);
                break;
        }
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
