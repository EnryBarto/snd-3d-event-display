#include "AppStateManager.hpp"

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
}
