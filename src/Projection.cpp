#include "Projection.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Constants.hpp"

namespace snd3D {

    Projection::Projection(float aspectRatio, float fov) {
        this->nearPlane = constants::limits::PROJ_NEARPLANE;
        this->farPlane = constants::limits::PROJ_FARPLANE;
        this->aspectRatio = aspectRatio;
        this->changeFov(fov);
    }

    void Projection::changeAspectRatio(float newAspectRatio) {
        this->aspectRatio = newAspectRatio;
        this->computeProjectionMatrix();
    }

    void Projection::changeFov(float newFov) {
        this->fovY = glm::clamp(newFov, constants::limits::PROJ_FOVY_MIN, constants::limits::PROJ_FOVY_MAX);
        this->computeProjectionMatrix();
    }

    const glm::mat4& Projection::getProjectionMatrix() {
        return this->matrix;
    }

    void Projection::computeProjectionMatrix() {
        this->matrix = glm::perspective(glm::radians(this->fovY), this->aspectRatio, this->nearPlane, this->farPlane);
    }
}