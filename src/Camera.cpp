#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Constants.hpp"

using namespace glm;

namespace snd3D {
    Camera::Camera(vec3 position, vec3 target) {
        this->position = vec3(position);
        this->target = vec3(target);
        this->upVector = vec3(0, 1, 0);
        this->viewMatrix = lookAt(this->position, this->target, this->upVector);
    }

    const mat4& Camera::getViewMatrix() {
        return this->viewMatrix;
    }

    const vec3& Camera::getPosition() {
        return this->position;
    }

    void Camera::rotateAroundCameraTarget(glm::vec3 axis, float angle) {
        if (glm::length(axis) == 0.0f) return; // Nothing to do

        // Relative vector from target to camera
        vec3 rel = this->position - this->target;

        // Rotate the relative vector around the normalized axis for the given angle
        axis = normalize(axis);
        vec3 rotated = vec3(glm::rotate(glm::mat4(1.0f), radians(-angle), axis) * vec4(rel, 0.0f));

        // New absolute position
        this->position = this->target + rotated;

        this->viewMatrix = lookAt(this->position, this->target, this->upVector);
    }

    void Camera::zoom(float offset) {
        vec3 direction = target - position;
        float distance = length(direction);

        // Don't exceed target
        if (offset > 0 && distance < constants::limits::ZOOM_DISTANCE_MIN) return;

        // Move
        this->position += normalize(direction) * offset * (distance * constants::ZOOM_FACTOR);
        this->viewMatrix = lookAt(this->position, this->target, this->upVector);
    }
}