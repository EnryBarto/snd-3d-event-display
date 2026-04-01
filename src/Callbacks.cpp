#include "Callbacks.hpp"

#include "App.hpp"

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

            case GLFW_KEY_R:
                this->app.scene->camera->reset();
                break;

            case GLFW_KEY_V:
                this->app.windowManager->toggleVsync();
                break;
        }
    }

    void Callbacks::cursorPosition(double currentMousePosX, double currentMousePosY) {
        switch (this->app.stateManager.getCurrentState()) {
            case AppState::MOVING_TRACKBALL: {
                this->app.windowManager->currentMousePosition[0] = (int)currentMousePosX;
                this->app.windowManager->currentMousePosition[1] = (int)currentMousePosY;
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
                    this->app.windowManager->lastMousePosition[0] = (int)xPos;
                    this->app.windowManager->lastMousePosition[1] = (int)yPos;
                    this->app.windowManager->currentMousePosition[0] = (int)xPos;
                    this->app.windowManager->currentMousePosition[1] = (int)yPos;
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
}
