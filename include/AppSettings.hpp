#pragma once

#include "Constants.hpp"

namespace snd3D {
    class AppSettings {
        public:
            bool isCameraPivotActive();
            void toggleCameraPivot();

        private:
            bool cameraPivotActive = constants::default::SHOW_PIVOT;
    };
}