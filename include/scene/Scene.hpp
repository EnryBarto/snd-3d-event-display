#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <string>

#include "scene/Camera.hpp"
#include "scene/Object.hpp"
#include "rendering/Projection.hpp"
#include "core/AppSettings.hpp"
#include "core/WindowManager.hpp"
#include "state/AppStateManager.hpp"
#include "scene/ObjectFactory.hpp"

namespace snd3D {
    class Scene {

        // Must be able to access the camera
        friend class Callbacks;
        friend class Gui;

        public:
            Scene(WindowManager& winMan, AppStateManager& stateMan, AppSettings& appSettings);
            void update();
            void render();

        private:
            std::unique_ptr<Camera> camera;
            std::unique_ptr<Projection> projection;
            std::unique_ptr<Object> detector;
            std::unique_ptr<Object> pivot;
            std::shared_ptr<Shader> flat;
            std::shared_ptr<Shader> transparent;

            ObjectFactory objectFactory;

            // Owned by App, keep reference to spped up access
            AppSettings& settings;
            WindowManager& windowManager;
            AppStateManager& stateManager;

            glm::vec3 cursorToUnitSphere(int x, int y);
    };
}
