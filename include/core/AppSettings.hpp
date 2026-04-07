#pragma once

#include "core/Constants.hpp"

namespace snd3D {
    class AppSettings {
        public:
            bool isCameraPivotActive();
            void toggleCameraPivot();

        private:
            bool cameraPivotActive = constants::defaults::SHOW_PIVOT;
    };
}
