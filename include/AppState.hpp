#pragma once

namespace snd3D {
    enum class AppState {
        TRACKBALL,
        MOVING_TRACKBALL,
        CLOSED
    };

    inline const char* appStateToString(AppState state) {
            switch (state) {
            case AppState::TRACKBALL:       return "Trackball";
            case AppState::MOVING_TRACKBALL:return "Trackball moving";
            case AppState::CLOSED:          return "Closing";
            default:                        return "Unknown";
        }
    }
}