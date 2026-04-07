#include "core/Callbacks.hpp"

#include "core/App.hpp"
#include "core/Constants.hpp"

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

    void Callbacks::close(GLFWwindow* window) {
        Callbacks* callbackInstance = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
        if (callbackInstance) callbackInstance->close();
    }

    /* ---------- INSTANCE METHODS ----------*/

    void Callbacks::keyAction(int key, int scancode, int action, int mods) {
        if (action != GLFW_PRESS && (key != GLFW_KEY_LEFT_SHIFT && key != GLFW_KEY_RIGHT_SHIFT)) return;

        if (mods & GLFW_MOD_CONTROL) { // CTRL pressed
            switch (key) {
                case GLFW_KEY_KP_ADD:
                case GLFW_KEY_EQUAL:
                    this->app.guiManager->changeFontSize(constants::factors::GUI_FONT_RESIZE);
                    break;

                case GLFW_KEY_KP_SUBTRACT:
                case GLFW_KEY_MINUS:
                    this->app.guiManager->changeFontSize(1 / constants::factors::GUI_FONT_RESIZE);
                    break;

                case GLFW_KEY_S:
                    this->app.stateManager.toggleImageExport();
                    break;
            }
        }
        else if (mods == 0) { // No control keys are pressed
            switch (key) {
                case GLFW_KEY_F11:
                    this->app.windowManager->toggleFullScreen();
                    break;

                case GLFW_KEY_P:
                    this->app.settings.toggleCameraPivot();
                    break;

                case GLFW_KEY_R:
                    this->app.scene->camera->reset();
                    break;

                case GLFW_KEY_V:
                    this->app.windowManager->toggleVsync();
                    break;
            }
        }

        switch (key) { // Actions to be performed regardless of which control keys are pressed
            case GLFW_KEY_LEFT_SHIFT:
            case GLFW_KEY_RIGHT_SHIFT:
                if (action == GLFW_PRESS) this->app.stateManager.shiftPressed();
                else if (action == GLFW_RELEASE) this->app.stateManager.shiftReleased();
                break;
        }
    }

    void Callbacks::cursorPosition(double currentMousePosX, double currentMousePosY) {
        if (this->app.guiManager->isPointerOverGui()) return;

        switch (this->app.stateManager.getCurrentState()) {
            case AppState::MOVING_TRACKBALL:
            case AppState::MOVING_PAN:
                this->app.windowManager->currentMousePosition[0] = (int)currentMousePosX;
                this->app.windowManager->currentMousePosition[1] = (int)currentMousePosY;
            break;

            default:
                break;
        }
    }

    void Callbacks::mouseButton(int button, int action, int mods) {
        if (this->app.guiManager->isPointerOverGui() && action != GLFW_RELEASE) return; // Don't start new actions if the pointer is over the gui

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

            case AppState::PAN:
                if (action == GLFW_PRESS) {
                    this->app.windowManager->lastMousePosition[0] = (int)xPos;
                    this->app.windowManager->lastMousePosition[1] = (int)yPos;
                    this->app.windowManager->currentMousePosition[0] = (int)xPos;
                    this->app.windowManager->currentMousePosition[1] = (int)yPos;
                    this->app.stateManager.toggleMovingPan();
                }
                break;

            case AppState::MOVING_PAN:
                if (action == GLFW_RELEASE) {
                    this->app.stateManager.toggleMovingPan();
                }
                break;
        }
    }

    void Callbacks::framebufferSize(int newWidth, int newHeight) {
        this->app.windowManager->frameBufferChanged();
    }

    void Callbacks::scroll(double xOffset, double yOffset) {
        if (this->app.guiManager->isPointerOverGui()) return;

        switch (this->app.stateManager.getCurrentState()) {
            case AppState::PAN:
            case AppState::MOVING_PAN:
                this->app.scene->camera->movePerpendicular(xOffset * constants::factors::PERPENDICULAR_PAN, yOffset * constants::factors::PERPENDICULAR_PAN);
                break;

            default:
                this->app.scene->camera->zoom(yOffset);
                break;
        }
    }

    void Callbacks::close() {
        this->app.stateManager.close();
    }
}
