#include "core/AppSettings.hpp"

namespace snd3D {
    bool AppSettings::isCameraPivotActive() {
        return this->cameraPivotActive;
    }

    void AppSettings::toggleCameraPivot() {
        this->cameraPivotActive = !this->cameraPivotActive;
    }

    bool AppSettings::isSceneInspectorActive() {
        return this->sceneInspectorActive;
    }

    void AppSettings::toggleSceneInspector() {
        this->sceneInspectorActive = !this->sceneInspectorActive;
    }
}
