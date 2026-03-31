#pragma once

#include <memory>

#include "WindowManager.hpp"
#include "Scene.hpp"
#include "AppStateManager.hpp"

namespace snd3D {
    class App {

        friend class Callbacks; // Needs access to the window manager

        public:
            App();
            void run();

        private:
            AppStateManager stateManager;
            std::unique_ptr<WindowManager> windowManager;
            std::unique_ptr<Scene> scene;
    };
}