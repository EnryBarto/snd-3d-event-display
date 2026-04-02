#pragma once

#include <memory>

#include "AppStateManager.hpp"
#include "WindowManager.hpp"
#include "AppSettings.hpp"
#include "Scene.hpp"
#include "Gui.hpp"

namespace snd3D {
    class App {

        // They need access to WindowManager and Scene
        friend class Callbacks;
        friend class Gui;

        public:
            App();
            void run();

        private:
            AppSettings settings;
            AppStateManager stateManager;
            std::unique_ptr<Gui> guiManager;
            std::unique_ptr<WindowManager> windowManager;
            std::unique_ptr<Scene> scene;
    };
}