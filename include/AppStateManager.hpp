#pragma once

#include "AppState.hpp"

namespace snd3D {
    class AppStateManager {
        public:
            void update();
            AppState getCurrentState();

            void close();
            void toggleMovingTrackball();

        private:
            AppState currentState = AppState::TRACKBALL;
            AppState nextState = AppState::TRACKBALL;
    };
}