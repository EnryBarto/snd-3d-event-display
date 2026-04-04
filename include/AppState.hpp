#pragma once

namespace snd3D {
    enum class AppState {
        TRACKBALL,
        MOVING_TRACKBALL,
        PAN,
        MOVING_PAN,
        EXPORT_IMAGE,
        CLOSED
    };

    inline const char* appStateToString(AppState state) {
            switch (state) {
            case AppState::TRACKBALL:       return "Trackball";
            case AppState::MOVING_TRACKBALL:return "Trackball moving";
            case AppState::PAN:             return "Pan";
            case AppState::MOVING_PAN:      return "Pan moving";
            case AppState::EXPORT_IMAGE:    return "Export image";
            case AppState::CLOSED:          return "Closing";
            default:                        return "Unknown";
        }
    }
}