#include "scene/Camera.hpp"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include "core/Constants.hpp"

using namespace glm;

namespace snd3D {
    Camera::Camera(vec3 position, vec3 target) {
        this->startPosition = vec3(position);
        this->startTarget = vec3(target);
        this->startUpVector = vec3(0, 1, 0);
        this->reset();
    }

    const mat4& Camera::getViewMatrix() {
        return this->viewMatrix;
    }

    const vec3& Camera::getPosition() {
        return this->position;
    }

    const glm::vec3& Camera::getTarget() {
        return this->target;
    }

    void Camera::rotateTrackball(vec3 origin, vec3 destination) {
        vec3 rotationAxis = glm::cross(origin, destination);
        if (glm::length(rotationAxis) == 0.0f) return;

        float angle = glm::degrees(acos(glm::clamp(glm::dot(origin, destination), -1.0f, 1.0f)));

        // Build the camera vectors
        vec3 viewDirection = glm::normalize(this->position - this->target);
        vec3 rightVector = glm::normalize(glm::cross(viewDirection, this->upVector));
        vec3 currentUpVector = glm::normalize(glm::cross(rightVector, viewDirection));

        // Map the local trackball axis to world space
        vec3 worldAxis = -rotationAxis.x * rightVector + rotationAxis.y * currentUpVector + rotationAxis.z * viewDirection;

        // Rotate the camera around its target using the computed world-space axis
        this->rotateAroundAxis(worldAxis, angle);
    }

    void Camera::moveParallel(float deltaX, float deltaY) {
        vec3 direction = normalize(this->target - this->position);
        vec3 right = normalize(cross(direction, this->upVector));
        vec3 up = normalize(cross(right, direction));

        this->position += up * deltaY + right * deltaX;
        this->target += up * deltaY + right * deltaX;
        this->recomputeMatrix();
    }

    void Camera::movePerpendicular(float deltaX, float deltaY) {
        vec3 direction = normalize(this->target - this->position);
        vec3 right = normalize(cross(direction, this->upVector));

        this->position += direction * deltaY + right * deltaX;
        this->target += direction * deltaY + right * deltaX;
        this->recomputeMatrix();
    }

    void Camera::rotateAroundAxis(vec3 axis, float angle) {
        if (glm::length(axis) == 0.0f) return; // Nothing to do

        // Relative vector from target to camera
        vec3 viewDirection = this->position - this->target;

        // Rotate the relative vector around the normalized axis for the given angle
        axis = normalize(axis);
        vec3 rotated = vec3(glm::rotate(mat4(1.0f), radians(-angle), axis) * vec4(viewDirection, 0.0f));

        // Try the rotation and compute the resulting angle
        vec3 candidateViewDir = glm::normalize(rotated);
        float candidateDotProduct = glm::clamp(glm::dot(candidateViewDir, this->upVector), -1.0f, 1.0f);
        float candidateAngle = glm::degrees(acos(candidateDotProduct));

        // Abort rotation to avoid flipping the camera
        if (candidateAngle <= 1.0f || candidateAngle >= 179.0f) {
            return;
        }

        // New absolute position
        this->position = this->target + rotated;
        this->recomputeMatrix();
    }

    void Camera::rotateByAngles(float deltaAngleX, float deltaAngleY) {
        vec3 viewDirection = position - target;

        // Compute and add horizontal rotation (around the up vector)
        mat4 rotX = glm::rotate(mat4(1.0f), glm::radians(deltaAngleX), glm::normalize(this->upVector));
        viewDirection = vec3(rotX * vec4(viewDirection, 1.0f));

        // Compute vertical rotation around the camera's right axis
        vec3 viewDirNorm = glm::normalize(viewDirection);
        vec3 rightVector = glm::normalize(glm::cross(viewDirNorm, this->upVector));

        // Current angle between view direction and up vector
        float dotProduct = glm::clamp(glm::dot(viewDirNorm, this->upVector), -1.0f, 1.0f);
        float currentAngle = glm::degrees(acos(dotProduct));

        // Try the vertical rotation and compute the resulting angle
        mat4 rotY = glm::rotate(mat4(1.0f), glm::radians(deltaAngleY), rightVector);
        vec3 candidate = vec3(rotY * vec4(viewDirection, 1.0f));
        float candidateDotProduct = glm::clamp(glm::dot(glm::normalize(candidate), this->upVector), -1.0f, 1.0f);
        float candidateAngle = glm::degrees(acos(candidateDotProduct));

        // If the angle doesn't flip the camera, use it
        if (candidateAngle > 1.0f && candidateAngle < 179.0f) {
            viewDirection = candidate;
        }

        // Apply the rotation
        this->position = target + viewDirection;
        this->recomputeMatrix();
    }

    void Camera::zoom(float offset) {
        vec3 direction = target - position;
        float distance = length(direction);
        float value = offset * distance * constants::factors::ZOOM; // Make zoom speed proportional to the distance from the target

        // Don't exceed target
        if ((distance - value) < constants::limits::ZOOM_DISTANCE_MIN) return;

        // Move
        this->position += normalize(direction) * value;
        this->recomputeMatrix();
    }

    bool Camera::isChanged() {
        bool tmp = this->changed;
        this->changed = false;
        return tmp;
    }

    void Camera::reset() {
        this->position = this->startPosition;
        this->target = this->startTarget;
        this->upVector = this->startUpVector;
        this->recomputeMatrix();
    }
    void Camera::recomputeMatrix() {
        this->viewMatrix = lookAt(this->position, this->target, this->upVector);
        this->changed = true;
    }
}
