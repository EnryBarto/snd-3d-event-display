#include "state/AppStateManager.hpp"

#include <iostream>

namespace snd3D {
    void AppStateManager::update() {
        if (this->currentState != this->nextState) {
            this->currentState = this->nextState;
        }
    }

    AppState AppStateManager::getCurrentState() {
        return this->currentState;
    }

    void AppStateManager::close() {
        this->nextState = AppState::CLOSED;
    }

    void AppStateManager::toggleMovingTrackball() {
        switch (this->currentState) {
            case AppState::TRACKBALL:
                this->nextState = AppState::MOVING_TRACKBALL;
                break;
            case AppState::MOVING_TRACKBALL:
                this->nextState = AppState::TRACKBALL;
                break;
            default:
                std::cerr << "ERROR! Toggle moving trackball not allowed in state: " << appStateToString(this->currentState) << std::endl;
                break;
        }
    }

    void AppStateManager::shiftPressed() {
        switch (this->currentState) {
            case AppState::TRACKBALL:
                this->nextState = AppState::PAN;
                break;

            case AppState::MOVING_TRACKBALL:
                this->nextState = AppState::MOVING_PAN;
                break;

            default:
                break;
        }
    }

    void AppStateManager::shiftReleased() {
        switch (this->currentState) {
            case AppState::PAN:
                this->nextState = AppState::TRACKBALL;
                break;

            case AppState::MOVING_PAN:
                this->nextState = AppState::MOVING_TRACKBALL;
                break;

            default:
                break;
        }
    }

    void AppStateManager::toggleMovingPan() {
        switch (this->currentState) {
            case AppState::PAN:
                this->nextState = AppState::MOVING_PAN;
                break;
            case AppState::MOVING_PAN:
                this->nextState = AppState::PAN;
                break;
            default:
                std::cerr << "ERROR! Toggle moving pan not allowed in state: " << appStateToString(this->currentState) << std::endl;
                break;
        }
    }
    void AppStateManager::toggleImageExport() {
        switch (this->currentState) {
            case AppState::TRACKBALL:
                this->nextState = AppState::EXPORT_IMAGE;
                break;

            case AppState::EXPORT_IMAGE:
                this->nextState = AppState::TRACKBALL;
                break;

            default:
                break;
        }
    }
}
