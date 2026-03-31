#include "Callbacks.hpp"

#include "App.hpp"

using namespace glm;

namespace snd3D {
    Callbacks::Callbacks(App& app) : app(app) {
    }

    /* ---------- STATIC FUNCTIONS ----------*/

    void Callbacks::keyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->keyAction(key, scancode, action, mods);
    }

    void Callbacks::cursorPosition(GLFWwindow* window, double currentMousePosX, double currentMousePosY) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->cursorPosition(currentMousePosX, currentMousePosY);
    }

    void Callbacks::mouseButton(GLFWwindow * window, int button, int action, int mods) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->mouseButton(button, action, mods);
    }

    void Callbacks::framebufferSize(GLFWwindow* window, int newWidth, int newHeight) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->framebufferSize(newWidth, newHeight);
    }

    void Callbacks::scroll(GLFWwindow* window, double xOffset, double yOffset) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->scroll(xOffset, yOffset);
    }

    /* ---------- INSTANCE METHODS ----------*/

    void Callbacks::keyAction(int key, int scancode, int action, int mods) {
        if (action == GLFW_RELEASE) return;

        switch (key) {
            case GLFW_KEY_F11:
                this->app.windowManager->toggleFullScreen();
                break;
        }
    }

    void Callbacks::cursorPosition(double currentMousePosX, double currentMousePosY) {

        switch (this->app.stateManager.getCurrentState()) {

            case AppState::MOVING_TRACKBALL: {
                // Get the two positions on the unit sphere
                vec3 destination = this->cursorToUnitSphere((int)currentMousePosX, (int)currentMousePosY);
                vec3 origin = this->cursorToUnitSphere(lastMousePosX, lastMousePosY);

                // Calculate the vector joining the two points
                vec3 difference = destination - origin;

                if (difference != vec3(0)) {
                    // Aproximate the rotation angle with ||destination - origin||
                    float angle = glm::length(difference) * 10;

                    // The rotation axis is perpendicular to the origin and destination vector, so the cross product is used
                    vec3 rotationAxis = glm::cross(origin, destination);

                    // Rotate the camera and undo the operation if there was a collision
                    this->app.scene->camera->rotateAroundCameraTarget(rotationAxis, angle);
                }

                this->lastMousePosX = (int)currentMousePosX;
                this->lastMousePosY = (int)currentMousePosY;
            } break;

            default:
                break;
        }
    }

    void Callbacks::mouseButton(int button, int action, int mods) {
        // Retrieve mouse position
        double xPos, yPos;
        glfwGetCursorPos(this->app.windowManager->getWindow(), &xPos, &yPos);

        switch (this->app.stateManager.getCurrentState()) {
            case AppState::TRACKBALL:
                if (action == GLFW_PRESS) {
                    this->lastMousePosX = (int)xPos;
                    this->lastMousePosY = (int)yPos;
                    this->app.stateManager.toggleMovingTrackball();
                }
                break;
            case AppState::MOVING_TRACKBALL:
                if (action == GLFW_RELEASE) {
                    this->app.stateManager.toggleMovingTrackball();
                }
                break;
        }
    }

    void Callbacks::framebufferSize(int newWidth, int newHeight) {
        this->app.windowManager->frameBufferChanged();
    }

    void Callbacks::scroll(double xOffset, double yOffset) {
        this->app.scene->camera->zoom(yOffset);
    }

    // Mapping the mouse click to the projected point on the hemisphere with center the origin and radius
    vec3 Callbacks::cursorToUnitSphere(int x, int y) {

        int width, height;
        glfwGetWindowSize(this->app.windowManager->getWindow(), &width, &height);

        // Map to [-1;1]
        vec3 point;

        point.x = (2.0f * x - width) / width;
        point.y = (height - 2.0f * y) / height;

        float tmp = glm::dot(vec2(point), vec2(point)); // Square of the distance of the projected point from the center in the XY plane (radius^2)
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
