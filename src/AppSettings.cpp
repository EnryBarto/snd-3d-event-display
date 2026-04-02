#include "AppSettings.hpp"

namespace snd3D {
    bool AppSettings::isCameraPivotActive() {
        return this->cameraPivotActive;
    }

    void AppSettings::toggleCameraPivot() {
        this->cameraPivotActive = !this->cameraPivotActive;
    }
}