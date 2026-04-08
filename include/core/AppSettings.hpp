#pragma once

#include "core/Constants.hpp"

namespace snd3D {
    class AppSettings {
        public:
            bool isCameraPivotActive();
            void toggleCameraPivot();
            bool isSceneInspectorActive();
            void toggleSceneInspector();

        private:
            bool cameraPivotActive = constants::defaults::SHOW_PIVOT;
            bool sceneInspectorActive = true;
    };
}
